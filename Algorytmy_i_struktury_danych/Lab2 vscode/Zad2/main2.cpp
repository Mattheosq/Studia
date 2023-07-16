#include <iostream>

struct Node{
    int value;
    Node* next;

};

void Insert_back_in_order(Node** ptr2head,int data){
    Node* new_ptr = new Node();
    new_ptr->value = data;
    new_ptr->next = nullptr;
    Node* temp = *ptr2head;

    if(*ptr2head==0 || data < (*ptr2head)->value){
        new_ptr->next = *ptr2head;
        *ptr2head = new_ptr;
    }
    else{
        while(temp->next!=nullptr && data > temp->next->value)
            temp = temp->next;
        new_ptr->next = temp->next;
        temp->next = new_ptr;
    }
    

}

void Print(Node* head){

    std::cout << "Lista: " << std::endl;
    while(head!=nullptr){
        std::cout << head->value << std::endl;
        head = head->next;
    }
    std::cout << std::endl;
}

int main(){

    Node* head = nullptr;
    int zakres = 1000;
    int koniec_przedzialu;
    srand(time(NULL));
    std::cout << "Podaj koniec przedzialu n: " << std::endl;
    std::cin >> koniec_przedzialu;
    for(int i=0; i<koniec_przedzialu; i++)
    {
        int random = rand()%zakres+1;
        if(random == 1){
            while(random == 1){
                random = rand()%zakres+1;
            }
        }
        Insert_back_in_order(&head,random);
    }
    Print(head);
  


 
    
    return 0;
}