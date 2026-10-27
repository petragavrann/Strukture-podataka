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
    return 0;
}

// 3.a) Dinamički dodaje novi element iza određenog elementa (traženog po prezimenu)
int insertNewAfter(Position head, char* targetLastName, char* ime, char* prezime, int god) {
    Position target = findLastN(head, targetLastName);
    if (target == NULL) {
        printf("Zadani element s prezimenom %s nije pronadjen.\n", targetLastName);
        return -1;
    }

    Position newPerson = createPerson(ime, prezime, god);
    if (newPerson == NULL) return -1;

    insertAfter(target, newPerson);
    return 0;
}

// 3.b) Dinamički dodaje novi element ispred određenog elementa (traženog po prezimenu)
int insertBefore(Position head, char* targetLastName, char* ime, char* prezime, int god) {
    Position target = findLastN(head, targetLastName);
    if (target == NULL) {
        printf("Zadani element s prezimenom %s nije pronadjen.\n", targetLastName);
        return -1;
    }

    Position prev = head;
    while (prev->next != target) {
        prev = prev->next;
    }

    Position newPerson = createPerson(ime, prezime, god);
    if (newPerson == NULL) return -1;

    insertAfter(prev, newPerson);
    return 0;
}

// 3.c) Sortira listu po prezimenima (Bubble sort)
int sortFun(Position head) {
    Position p = NULL;
    Position q = NULL;
    Position temp = NULL;
    Position end = NULL;

    if (head->next == NULL) return 0;

    while (head->next != end) {
        p = head->next;
        q = head;
        while (p->next != end) {
            if (strcmp(p->lastName, p->next->lastName) > 0) {
       
                temp = p->next;
                q->next = temp;
                p->next = temp->next;
                temp->next = p;

                p = temp;
            }
            q = p;
            p = p->next;
        }
        end = p;
    }
    return 0;
}

// 3.d) Upisuje listu u datoteku
int writeToFile(Position head, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje!\n");
        return -1;
    }

    Position p = head->next;
    while (p != NULL) {
        fprintf(fp, "%s %s %d\n", p->name, p->lastName, p->year);
        p = p->next;
    }

    fclose(fp);
    printf("Lista je uspjesno upisana u datoteku %s.\n", filename);
    return 0;
}

// 3.e) Čita listu iz datoteke
int readFromFile(Position head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za citanje!\n");
        return -1;
    }

    char ime[50];
    char prezime[50];
    int god;

   
    while (fscanf(fp, "%s %s %d", ime, prezime, &god) == 3) {
        insertEnd(head, ime, prezime, god);
    }

    fclose(fp);
    printf("Lista je uspjesno ucitana iz datoteke %s.\n", filename);
    return 0;
}

int main() {

    Person Head = { .name = "", .lastName = "", .year = 0, .next = NULL };

    insertBegin(&Head, "Ana", "Anic", 2005);
    insertBegin(&Head, "Ivan", "Ivic", 2003);
    insertEnd(&Head, "Marko", "Maric", 2001);

    printf("Pocetna lista:\n");
    printList(&Head);

    printf("\nDodavanje iza i ispred:\n");
    insertNewAfter(&Head, "Anic", "Maja", "Majic", 2004);
    insertBefore(&Head, "Ivic", "Petra", "Petric", 2002);
    printList(&Head);

    //Sortiranje
    printf("\nLista nakon sortiranja po prezimenima\n");
    sortFun(&Head);
    printList(&Head);

    //Upis u datoteku
    printf("\nDatoteka\n");
    writeToFile(&Head, "osobe.txt");

    return 0;
}


