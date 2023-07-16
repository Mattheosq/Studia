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

void Delete_nieparzysty(Node** ptr2head){

    Node* prev = *ptr2head;
    Node* cur= prev->next;

    while(cur != nullptr){
        if(cur->value%2 == 1){

            prev->next = cur->next;
            Node* temp = cur;
            cur = cur->next;
            delete temp;
            continue;
        }
        
        prev = cur;
        cur = cur->next;
    
    }
    if((*ptr2head)->value%2 == 1){
        Node* temp = *ptr2head;
        *ptr2head = (*ptr2head)->next;
        delete temp;
    }

}

double Srednia(Node* head){

    int suma = 0;
    while(head!=nullptr){
        suma+= head->value;
        head = head->next;
    }
    return (double)suma/10.0;
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
    srand(time(NULL));
    for(int i=0; i<100; i++)
    {
        int random = rand()%zakres+1;
        Insert_back_in_order(&head,i+1);
    }
    Print(head);
    std::cout << "Srednia: " << Srednia(head) << std::endl;
    Delete_nieparzysty(&head);
    Print(head);
    std::cout << "Srednia: " << Srednia(head) << std::endl;


 
    
    return 0;
}