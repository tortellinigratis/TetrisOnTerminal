#include <iostream>
#include <fstream>
#include <cstring>
#include "ncrss.cpp"

using namespace std;


struct pos{
    string username;
    int points;
    pos *next;
};

typedef pos* p_pos;

p_pos head_insert(p_pos head, string user, int p){
    p_pos tmp = new pos;
    // REVIEW ask pelato if using string is fine
    tmp->username = user;
    tmp->points = p;
    tmp->next = head;
    return tmp;
}

void add_score(string username, string score){
    ofstream writescore;
    writescore.open("scores.txt", ios::app);

    if(!writescore.is_open())
        cout << "Errore nell' apertura del file";

    writescore<<endl<<username<<endl<<score;
    writescore.close();
}

void override_file(p_pos head){
    ofstream write;
    write.open("scores.txt");

    if(!write.is_open())
        cout << "Errore nell' apertura del file";

    p_pos tmp = head;
    while(tmp != NULL){
        write<<tmp->username<<endl<<tmp->points<<endl;
        tmp = tmp->next;
    }

}//per ora non serve

p_pos delete_tail(p_pos head){
    p_pos tmp = head;
    while (tmp->next->next != NULL)
        tmp = tmp->next;
    delete tmp->next;
    tmp->next = NULL;
    return head;
}       //inutile se si inizializza il file con -1

bool check_invalid_scores(p_pos head){
    p_pos tmp = head;
    while (tmp != NULL){
        if(tmp->points == -1) return true;
        tmp = tmp->next;
    } return false;
}//per ora non serve

p_pos remove_invalid_scores(p_pos head) {
    if(head == NULL) return NULL; //caso lista vuota
    if(head->points == -1){          //caso el in testa
        p_pos tmp = new pos;
        tmp = head->next;
        return tmp;
    }
    else{                         //caso el in mezzo o in coda
        p_pos tmp=head, p_before=head;
        while(tmp != NULL){
            if(tmp->points == -1){
                p_before->next = tmp->next;
                delete tmp;
                tmp = p_before;
            }
        p_before = tmp;
        tmp = tmp->next;
    }
    } return head;
}//per ora non serve