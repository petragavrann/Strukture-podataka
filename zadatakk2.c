#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;
typedef struct _Person {
    char name[50];
    char lastName[50];
    int year;
    Position next;
} Person;

// Pomoćna funkcija za kreiranje novog čvora i alokaciju memorije
Position createPerson(char* ime, char* prezime, int god) {
    Position newPerson = (Position)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->year = god;
    newPerson->next = NULL;

    return newPerson;
}

// Unos iza određenog elementa
int insertAfter(Position p, Position newP) {
    newP->next = p->next;
    p->next = newP;
    return 0;
}

// a) Dodavanje na početak liste (iza head elementa)
int insertBegin(Position head, char* ime, char* prezime, int god) {
    Position newPerson = createPerson(ime, prezime, god);
    if (newPerson == NULL) return -1;

    insertAfter(head, newPerson);
    return 0;
}

// b) Ispis liste
int printList(Position p) {
    p = p->next;
    if (p == NULL) {
        printf("Lista je prazna.\n");
        return 0;
    }

    while (p != NULL) {
        printf("Ime: %s, Prezime: %s, Godina: %d\n", p->name, p->lastName, p->year);
        p = p->next;
    }
    return 0;
}

// c) Dodavanje na kraj liste
int insertEnd(Position head, char* ime, char* prezime, int god) {
    Position newPerson = createPerson(ime, prezime, god);
    if (newPerson == NULL) return -1;

    Position temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    insertAfter(temp, newPerson);
    return 0;
}

// d) Pronalaženje elementa po prezimenu
Position findLastN(Position p, char* prezime) {
    for (p = p->next; p != NULL; p = p->next) {
        if (strcmp(p->lastName, prezime) == 0) {
            return p;
        }
    }
    return NULL;
}

// e) Brisanje određenog elementa po prezimenu
int deletePerson(Position p, char* prez) {
    Position curr = findLastN(p, prez);

    if (curr == NULL) {
        printf("Osoba s prezimenom %s nije pronadjena!\n", prez);
        return -1;
    }

    Position prev = p;
    while (prev->next != curr) {
        prev = prev->next;
    }

    prev->next = curr->next;
    free(curr);

    printf("Osoba s prezimenom %s je uspjesno obrisana.\n", prez);
    return 0;
}

int main() {
    // Inicijalizacija head elementa
    Person Head = { .name = "", .lastName = "", .year = 0, .next = NULL };

    // Testiranje funkcija
    insertBegin(&Head, "Ana", "Anic", 2005);
    insertBegin(&Head, "Ivan", "Ivic", 2003);
    insertEnd(&Head, "Marko", "Maric", 2001);

    printf("Trenutna lista:\n");
    printList(&Head);

    printf("\nTrazenje osobe:\n");
    Position trazen = findLastN(&Head, "Anic");
    if (trazen != NULL) {
        printf("Pronadjena osoba: %s %s, %d\n", trazen->name, trazen->lastName, trazen->year);
    }
    else {
        printf("Osoba nije pronadjena.\n");
    }

    printf("\nBrisanje osobe:\n");
    deletePerson(&Head, "Anic");

    printf("\nLista nakon brisanja:\n");
    printList(&Head);

    return 0;
}


