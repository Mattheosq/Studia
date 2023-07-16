#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <err.h>
#include <stdbool.h>


#define FIFO "fifo"			//sciezka do pliku fifo(obluguje asynchroniczne przekazywanie informacji)
#define PIDS "lista_pidow.txt"	//sciezka do pliku lista_pidow.txt

struct mymsgbuf { // struktura dla kolejki komunikatow
	long    mtype;
	char	jeden_wiersz[256];
	int 	size;
} msg, buf;

/* unia dla semafora */
union semun {
    int val;						// wartosc dla SETVAL
    struct semid_ds *buf;			// bufor dla IPC_STAT, IPC_SET
    unsigned short int *array;		// tablica dla GETALL, SETALL
    struct seminfo *__buf;			// bufor dla IPC_INFO
};

union semun ctl;			// unia do kontroli semafora

int stop = 0;	//Zmienna do wstrzymywania dzialania programu
FILE *dane;     //Wskaznik na plik z danymi
pid_t pid[4];	//PIDy procesow
int fifo;		//Deskryptor pliku FIFO
int qid;        //Id kolejki komunikatow
int idbuf2_3;  	//Pamiec wspoldzielona procesu 2 i procesu 3
char *buf2_3;  	//Wskaznik na pamiec wspoldzielona procesu 2 i procesu 3
int semid1;     //Semafor 1
int semid2;     //Semafor 2
key_t key; 		//Klucz pamieci wspoldzielonej

/* Funkcje dla kolejki komunikatow*/
//--------------------------------------------
int send_message(struct mymsgbuf *qbuf){
	int result, length;

	/* lenght jest rozmiarem struktury minus sizeof(mtype) */
	length = sizeof(struct mymsgbuf) - sizeof(long);

	if((result = msgsnd(qid, qbuf, length, 0)) == -1)
          return(-1);

	return(result);
}

int read_message(long type, struct mymsgbuf *qbuf){
	int  result, length;

    /* lenght jest rozmiarem struktury minus sizeof(mtype) */
	length = sizeof(struct mymsgbuf) - sizeof(long);

	if((result = msgrcv(qid, qbuf, length, type,  0)) == -1)
		return(-1);

	return(result);
}
//-------------------------------------------------

//obsluga sygnalu SIGUSR1 procesu macierzystego
void handle_main(int sig) {
	//wczytanie sygnalu od procesu 2
	if(read(fifo, &sig, sizeof(sig)) == -1)
		fprintf(stderr, "Blad wczytywania wiadomosci z FIFO!\n");
	int i;
	//wpisanie sygnalu do kolejki FIFO (3 razy, po razie dla kazdego procesu)
	for(i=0; i<3; i++)
		if(write(fifo, &sig, sizeof(sig)) == -1)
			fprintf(stderr, "Blad wpisywania do FIFO!\n");
	//powiadomienie procesu 1 o mozliwosci odczytania kolejki fifo
	kill(pid[1], SIGUSR1);
}

//odczytywanie i obsluga otrzymanych sygnalow z kolejki FIFO
void handle_sig(int sig) {
	int wiadomosc;
	//odczytanie sygnalu
	if(read(fifo, &wiadomosc, sizeof(wiadomosc)) == -1)
		fprintf(stderr, "Blad wczytywania wiadomosci z FIFO!\n");
	//powiadomienie kolejnego procesu
	if(getpid() == pid[1])
		kill(pid[2], SIGUSR1);
	else if(getpid() == pid[2])
		kill(pid[3], SIGUSR1);
	else if(getpid() == pid[3]) {
		if(wiadomosc == SIGTSTP)
			printf("Zatrzymano przekazywanie danych\n");
		else if(wiadomosc == SIGCONT)
			printf("Wznowiono przekazywanie danych\n");
	}
	//obsluga sygnalow
	if(wiadomosc == SIGTERM) {
		if(getpid()==pid[1])
			fclose(dane);
		exit(0);
	}
	else if(wiadomosc == SIGTSTP)
		stop=1;
	else if(wiadomosc == SIGCONT)
		stop=0;
}

//oblsluga otrzymanych sygnalow przez procesy 1,2 i 3
void handle_p123(int sig) {
	//wpisanie otrzymanego sygnalu do kolejki FIFO
	if(write(fifo, &sig, sizeof(sig)) == -1)
		fprintf(stderr, "Blad wpisywania do FIFO!\n");
	//powiadomienie procesu macierzystego
	kill(pid[0], SIGUSR1);
}

//inicjalizacja zasobow
int zasoby() {

	key_t  msgkey = ftok(".", 'm'); // klucz kolejki komunikatow
	/* otwieramy/tworzymy kolejkę */
	if((qid = msgget(msgkey, IPC_CREAT | 0666 )) == -1)
		return -1;

	key = ftok(".", 'r'); // klucz pamieci wspoldzielonej
	if(key == -1){
       errx(1, "Blad tworzenia klucza!");
       return -1;
	}
	//----------------------------------------------------------
	key_t key1 = ftok(".", 'A'); // klucz pierwszego semafora
	if(key1 == -1){
       errx(1, "Blad tworzenia klucza!");
       return -1;
    }
    if((semid1 = semget(key1, 1, IPC_CREAT | 0666)) == -1){ // tworzenie ID pierwszego semafora, semget(klucz, liczba semaforow, flagi/parametry)
        errx(2, "Blad tworzenia semafora!");
        return -1;
    }
    //----------------------------------------------------------
	key_t key2 = ftok(".", 'B'); // klucz drugiego semafora
	if(key2 == -1){
       errx(1, "Blad tworzenia klucza!");
       return -1;
	}
	if((semid2 = semget(key2, 1, IPC_CREAT | 0666))  == -1){ // ID drugiego semafora
        errx(2, "Blad tworzenia semafora!");
        return -1;
	}
	//----------------------------------------------------------
	
	//---------------------------------------------------------
    if(mkfifo(FIFO, 0666) == -1) // tworzenie kolejki
		if(errno != EEXIST)
			return -1;
	if((fifo = open(FIFO, O_RDWR)) == -1){ // otwieranie kolejki
        fprintf(stderr, "Blad przy otwieraniu kolejki");
        return -1;
	}
	//----------------------------------------------------------
	/* ustawianie wartosci poczatkowych semaforow */
	ctl.val = 0; // oba semafory beda opuszczone
	if(semctl(semid1, 0, SETVAL, ctl) == -1){
        errx(3, "Blad ustawiania semafora!");
        return -1;
	}
    if(semctl(semid2, 0, SETVAL, ctl) == -1){
        errx(3, "Blad ustawiania semafora!");
        return -1;
	}
	return 0;
}

//zwalnianie pamieci
int sprzatanie() {
	int ret = 0;
    if(shmdt(buf2_3) == -1) {
        printf("Blad odlaczenia sie od pamieci dzielonej: %s\n", strerror(errno));
        ret = -1;
    }
    if(shmctl(idbuf2_3, IPC_RMID, NULL) == -1) {
        printf("Blad usuwania segmentu pamieci dzielonej: %s\n", strerror(errno));
        ret = -1;
    }
    if(semctl(semid1, 0, IPC_RMID, ctl) == -1) {
        printf("Blad usuwania semafora 1: %s\n", strerror(errno));
        ret = -1;
    }
    if(semctl(semid2, 0, IPC_RMID, ctl) == -1) {
        printf("Blad usuwania semafora 2: %s\n", strerror(errno));
        ret = -1;
    }
    if(close(fifo) == -1) {
        printf("Blad zamykania FIFO: %s\n", strerror(errno));
        ret = -1;
    }
    if(unlink(FIFO) == -1) {
        printf("Blad odlaczenia sie od FIFO: %s\n", strerror(errno));
        ret = -1;
    }
    if(msgctl(qid, IPC_RMID, 0) == -1) {
        printf("Blad usuwania kolejki komunikatow: %s\n", strerror(errno));
        ret = -1;
    }
    return ret;
}


//tworzenie maskek
void maskuj(int x) {
	sigset_t mask;
	sigfillset(&mask);
	if(x == 0) {
		signal(SIGUSR1, handle_main);
		signal(SIGTERM, handle_p123);
		signal(SIGTSTP, handle_p123);
		signal(SIGCONT, handle_p123);

		sigdelset(&mask, SIGUSR1);
		sigdelset(&mask, SIGTERM);
		sigdelset(&mask, SIGTSTP);
		sigdelset(&mask, SIGCONT);
		sigprocmask(SIG_SETMASK, &mask, NULL);
	}
	else if(x == 1){
		signal(SIGUSR1, handle_sig);
		//signal(SIGUSR2, handle_msgqueue);// signal by wznowic kolejke komunikatow
		signal(SIGTERM, handle_p123);
		signal(SIGTSTP, handle_p123);
		signal(SIGCONT, handle_p123);

		sigdelset(&mask, SIGUSR1);
		//sigdelset(&mask, SIGUSR2);
		sigdelset(&mask, SIGTERM);
		sigdelset(&mask, SIGTSTP);
		sigdelset(&mask, SIGCONT);
		sigprocmask(SIG_SETMASK, &mask, NULL);
	}
    else {
		signal(SIGUSR1, handle_sig);
		signal(SIGTERM, handle_p123);
		signal(SIGTSTP, handle_p123);
		signal(SIGCONT, handle_p123);

		sigdelset(&mask, SIGUSR1);
		sigdelset(&mask, SIGTERM);
		sigdelset(&mask, SIGTSTP);
		sigdelset(&mask, SIGCONT);
		sigprocmask(SIG_SETMASK, &mask, NULL);
		
	}
}

//zwiekszenie wartosci semafora
void semunlock(int semid) { // sem_signal
	struct sembuf sem;

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);
}

//zmniejszenie wartosci semafora (blokowanie)
void semlock(int semid) { // sem_wait
	struct sembuf sem;

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);
}

//-----------------------------------------------------------------

//Kod procesu1
int proces1() {
	FILE *pidy = fopen(PIDS, "r");
	while(pidy == NULL)
		pidy = fopen(PIDS, "r");
	while(pid[0] == 0 || pid[1] == 0 || pid[2] == 0 || pid[3] == 0)
		fscanf(pidy, "%d %d %d %d", &pid[0], &pid[1], &pid[2], &pid[3]);
	fclose(pidy);
	
	printf("Proces 1[%d]: Wybierz opcje\n", pid[1]);
	printf("1.Wczytywanie danych z klawiatury\n");
	printf("2.Wczytywanie danych z pliku\n");
	int opcja;
	fflush(stdin);
	scanf("%d", &opcja);
	//fflush(stdout);
	int i = 1;
	
	//while(stop == 1);
	printf("Proces 1[%d]: Wybrano opcje %d\n", pid[1], opcja);
	char* data = NULL;
	int data_size = 0;
	
	if(opcja == 1){
        //POJEDYNCZE wczytanie z terminalu
        //char wiersz[256];
        data = (char*)calloc(sizeof(char)*256, 1);
        data_size = 256;
        printf("Proces 1[%d]: Podaj tekst: \n",pid[1]);
        fflush(stdin);
        int k = scanf("%s", data);
        data_size = strlen(data);     
	}
	else if(opcja == 2){
        //wczytywanie z pliku
        printf("Proces 1[%d]: Wczytywanie z pliku...\n",pid[1]);
        
        FILE* dane_ptr = fopen("dane.txt", "rb");
       		
		fseek(dane_ptr, 0, SEEK_END);
		data_size = ftell(dane_ptr)+1; // proces 1 pozyskuje rozmiar pliku
		fseek(dane_ptr, 0, SEEK_SET);
			
		data = (char*)calloc(data_size, 1);
		fread(data, sizeof(char), data_size-1, dane_ptr);
		fclose(dane_ptr);
			    
	}
	
	int chunk_size = 256;
	// allign up
	int size = data_size + chunk_size - data_size%chunk_size;
	data = (char*)realloc(data, size); // TODO
	
	printf("Proces 1[%d]: Wysylanie danych kolejka komunikatow...\n",pid[1]);
	for(int i = 0; i < size/chunk_size;i++){
		msg.mtype = 1;
		msg.size = (i == size/chunk_size - 1) ? (data_size%chunk_size) : chunk_size;
		if(msg.size == 0) // edge case
			msg.size = chunk_size;
		memcpy(msg.jeden_wiersz, data + i * chunk_size, chunk_size);
		if((send_message(&msg)) == -1) { // wysylanie
		    perror("Blad wysylania w kolejce komunikatow");
		    kill(pid[2], SIGTERM);
        }
	}
	msg.size = 0;
	if((send_message(&msg)) == -1) { // wysylanie
		    perror("Blad wysylania w kolejce komunikatow");
		    kill(pid[2], SIGTERM);
    }
    
    return 0;
	
}

//Kod procesu2
int proces2() {
	FILE *pidy = fopen(PIDS, "r");
	while(pidy == NULL)
		pidy = fopen(PIDS, "r");
	while(pid[0] == 0 || pid[1] == 0 || pid[2] == 0 || pid[3] == 0)
		fscanf(pidy, "%d %d %d %d", &pid[0], &pid[1], &pid[2], &pid[3]);
	fclose(pidy);
	char* array = NULL; // string skladajacy sie ze wszystkich znakow
	int array_size = 0; // wskazuje miejsca do ktorych dolaczane beda stringi(wiersze) do tablicy array laczacej to w jednego stringa
	printf("Proces 2[%d]: Odczytywanie danych z kolejki komunikatow...\n",pid[2]);
	while(true){
		
		while(stop == 1);
        buf.mtype   = 1;
      
        if(read_message(buf.mtype, &buf) == -1){ // odbieranie wiadomosci
        	continue;
        }
        
        if(buf.size == 0)
        	break;
        // zapelnianie wiadomosciami tablicy przechowujacej cale dane z pliku
		array = (char*)realloc(array,array_size+buf.size);
		memcpy(array + array_size, buf.jeden_wiersz, buf.size);
		array_size+=buf.size;
	}
	
	
	// tworzenie pamieci wspoldzielonej
	if((idbuf2_3 = shmget(key, (2*array_size+1)*sizeof(char), IPC_CREAT | 0666)) < 0){ // ID segmentu pamieci dzielonej
        errx(2, "Blad tworzenia segmentu pamieci dzielonej!");
        return -1;
	}
    if((buf2_3 = (char *)shmat(idbuf2_3, NULL, 0)) == (char *) - 1){ // przydzielenie pamieci dzielonej do naszej przestrzeni danych
        errx(3, "Blad przylaczania pamieci dzielonej!");
        return -1;
	}
	
	while(stop == 1);
	char* hex_str = (char*)calloc(sizeof(char)*(2*array_size+1),1); // tablica na przekonwertowane dane
		
    int i;
    for (i = 0; i < array_size; i++) {
       sprintf(hex_str + 2*i, "%02x", array[i]);
    }
    hex_str[2*i] = '\0';
    printf("Proces 2[%d]: Konwertowanie danych...\n",pid[2]);
	printf("Proces 2[%d]: Przekazywanie danych do pamieci wspoldzielonej...\n",pid[2]);
    memcpy(buf2_3, hex_str, strlen(hex_str)+1); // zapelniamy buf2_3 danymi
    //printf("%s\n", hex_str);
    //printf("Size: %d\n", size);
    free(array);
    free(hex_str);

	semunlock(semid1); //podniesienie semafora - odblokowanie procesu 3
    semlock(semid2);// czekamy az skonczy dzialanie proces 3
    
    return 0;
       
}

//Kod procesu3
int proces3() {
	FILE *pidy = fopen(PIDS, "r");
	while(pidy == NULL)
		pidy = fopen(PIDS, "r");
	while(pid[0] == 0 || pid[1] == 0 || pid[2] == 0 || pid[3] == 0)
		fscanf(pidy, "%d %d %d %d", &pid[0], &pid[1], &pid[2], &pid[3]);
	fclose(pidy);
	
	while(stop == 1);
	semlock(semid1); // czekamy az skonczy dzialanie proces 2
	// odczyt pamieci wspoldzielonej
	if((idbuf2_3 = shmget(key, 0, 0666)) < 0){ // ID segmentu tej samej pamieci dzielonej z procesu 1
        errx(2, "Blad tworzenia segmentu pamieci dzielonej!");
        return -1;
	}
    if((buf2_3 = (char *)shmat(idbuf2_3, NULL, 0)) == (char *) - 1){ // przydzielenie pamieci dzielonej do naszej przestrzeni danych
        errx(3, "Blad przylaczania pamieci dzielonej!");
        return -1;
	}
	printf("Proces 3[%d]: Odczyt danych z pamieci wspoldzielonej...\n",pid[3]);
	int size = strlen(buf2_3);
	int i;
	for(i = 0; i < size; i++){
		printf("%c", buf2_3[i]);
		if(i % 15 == 14)
			printf("\n");
	}
	printf("\n");

	semunlock(semid2); //podniesienie semafora - odblokowanie procesu 2
	
	return 0;
	
}

int main(int argc, char *argv[]) {
	if(zasoby() == -1)
		exit(-1);
	maskuj(0);
	pid[0]=getpid();
	//tworzenie procesow potomnych
	if((pid[1] = fork()) == 0) {
		maskuj(1);
		return proces1();
	}
	else if((pid[2] = fork()) == 0) {
		maskuj(2);
		return proces2();
	}
	else if((pid[3] = fork()) == 0) {
		maskuj(3);
		return proces3();
	}
	FILE *pidy = fopen(PIDS, "w");
	if(pidy == NULL) {
		sprzatanie();
		fprintf(stderr, "Nie mozna otworzyc pliku z PID'ami!\n");
		exit(-1);
	}
	//wpisanie PID'ow do pliku
	fprintf(pidy, "%d %d %d %d", pid[0], pid[1], pid[2], pid[3]);
	fclose(pidy);
	//oczekiwanie na smierc potomkow
	
	/*waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);
	waitpid(pid[3], NULL, 0);*/
	
	int status;
	int all_terminated = 0;
	while(!all_terminated) {
		for(int i=1;i<=3;i++){
		    int wait_pid = waitpid(pid[i], &status, 0);
		    if(wait_pid == -1) {
		        if(errno == EINTR) continue;
		        else break;
		    }
		    if(WIFEXITED(status)){
		        printf("Child %d terminated with status: %d\n", pid[i], WEXITSTATUS(status));
		    }
		    else if(WIFSIGNALED(status)){
		        printf("Child %d terminated by signal: %d\n", pid[i], WTERMSIG(status));
		    }
		}
		all_terminated = 1;
		for(int i=1;i<=3;i++){
		    if(kill(pid[i],0)==0) {
		        all_terminated = 0;
		        break;
		    }
		}
	}

	
	if(sprzatanie() == 0)
		printf("Zakonczono dzialanie programu!\n");
	//execlp("ipcs", "ipcs", NULL);
	return 0;
}
