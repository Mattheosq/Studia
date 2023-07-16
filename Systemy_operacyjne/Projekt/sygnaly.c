#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

void wczytaj_pidy(int *pid, int *pid1, int *pid2, int *pid3) {
	FILE *pid_plik = fopen ("lista_pidow.txt", "r");
	if (!pid_plik){
		printf("Nie ma aktywnych procesow\n");
		return;
	}
	fscanf(pid_plik, "%d", pid);
	fscanf(pid_plik, "%d", pid1);
	fscanf(pid_plik, "%d", pid2);
	fscanf(pid_plik, "%d", pid3);
	fclose(pid_plik);
}

void zakoncz(int pid, int pid1, int pid2, int pid3) {
	int opcja;
	printf("Do ktorego procesu wyslac sygnal?\n");
	printf("1. Proces 1., PID: %d\n", pid1);
	printf("2. Proces 2., PID: %d\n", pid2);
	printf("3. Proces 3., PID: %d\n", pid3);
	printf("4. Proces macierzysty, PID: %d\n", pid);
	printf("Wybor: ");
	scanf("%d", &opcja);
	switch(opcja) {
		case 1:
			kill(pid1, SIGTERM);
			break;
		case 2:
			kill(pid2, SIGTERM);
			break;
		case 3:
			kill(pid3, SIGTERM);
			break;
		case 4:
			kill(pid, SIGTERM);
			break;
	}
}

void wstrzymaj(int pid, int pid1, int pid2, int pid3) {
	int opcja;
	printf("Do ktorego procesu wyslac sygnal?\n");
	printf("1. Proces 1., PID: %d\n", pid1);
	printf("2. Proces 2., PID: %d\n", pid2);
	printf("3. Proces 3., PID: %d\n", pid3);
	printf("4. Proces macierzysty, PID: %d\n", pid);
	printf("Wybor: ");
	scanf("%d", &opcja);
	switch(opcja) {
		case 1:
			kill(pid1, SIGTSTP);
			break;
		case 2:
			kill(pid2, SIGTSTP);
			break;
		case 3:
			kill(pid3, SIGTSTP);
			break;
		case 4:
			kill(pid, SIGTSTP);
			break;
	}
}

void wznow(int pid, int pid1, int pid2, int pid3) {
	int opcja;
	printf("Do ktorego procesu wyslac sygnal?\n");
	printf("1. Proces 1., PID: %d\n", pid1);
	printf("2. Proces 2., PID: %d\n", pid2);
	printf("3. Proces 3., PID: %d\n", pid3);
	printf("4. Proces macierzysty, PID: %d\n", pid);
	printf("Wybor: ");
	scanf("%d", &opcja);
	switch(opcja) {
		case 1:
			kill(pid1, SIGCONT);
			break;
		case 2:
			kill(pid2, SIGCONT);
			break;
		case 3:
			kill(pid3, SIGCONT);
			break;
		case 4:
			kill(pid, SIGCONT);
			break;
	}
}

int main() {
	int pid = 0, pid1 = 0, pid2 = 0, pid3 = 0;
	int opcja = -1;
	while(opcja != 0){
		printf("\n1. Wczytaj numery PID\n");
		printf("2. Sygnal SIGTERM\n");
		printf("3. Sygnal SIGTSTP\n");
		printf("4. Sygnal SIGCONT\n");
		printf("0. Wyjdz\n");
		printf("Opcja: ");
		scanf("%d", &opcja);
		switch(opcja) {
			case 1:
				wczytaj_pidy(&pid, &pid1, &pid2, &pid3);
				printf("\nPPID: %d\nPID 1: %d\nPID 2: %d\nPID 3: %d", pid, pid1, pid2, pid3);
				break;
			case 2:
				zakoncz(pid, pid1, pid2, pid3);
				break;
			case 3:
				wstrzymaj(pid, pid1, pid2, pid3);
				break;
			case 4:
				wznow(pid, pid1, pid2, pid3);
				break;
		}
	}
	return 0;
}

