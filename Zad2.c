#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* position;

typedef struct _person {
	char fname[32], lname[32];
	int birth_year;
	position next;
} person;

position create_person(char* fname, char* lname, int birth_year);
int prepend_list(position head, char* fname, char* lname, int birth_year);
int insert_after(position previous, position to_insert);
int append_list(position head, char* fname, char* lname, int birth_year);
int print_list(position first);
position find_last(position head);
position find_by_lastname(position head, char* lname);
int delete_by_lastname(position head, char* lname);

position create_person(char* fname, char* lname, int birth_year) {
    position new_person = NULL;
    new_person = (position)malloc(sizeof(person));
    if (!new_person) {
        printf("Malloc failed in function create_person!\n");
        return NULL;
    }

    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = birth_year;
    new_person->next = NULL;

    return new_person;
}

int prepend_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = NULL;
    new_person = create_person(fname, lname, birth_year);

    if (!new_person) {
        return -1;
    }

    new_person->next = head->next;
    head->next = new_person;

    return EXIT_SUCCESS;
}

int print_list(position first) {
    position temp = first->next;
    while (temp) {
        printf("First name: %s\nLast name: %s\nBirth year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int append_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = NULL;
    new_person = create_person(fname, lname, birth_year);

    if (!new_person) {
        return -1;
    }

    position last = find_last(head);
    last->next = new_person;

    return EXIT_SUCCESS;
}

position find_last(position head) {
    position temp = head;

    while (temp->next) {
        temp = temp->next;
    }
    return temp;
}

position find_by_lastname(position head, char* lname) {
    position temp = head->next;

    while (temp) {
        if (strcmp(temp->lname, lname) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL; 
}

int delete_by_lastname(position head, char* lname) {
    position prev = head;
    position curr = head->next;

    while (curr) {
        if (strcmp(curr->lname, lname) == 0) {
            prev->next = curr->next;
            free(curr);
            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
    }

    return -1; 
}

int main() {
    person head = { .fname = "", .lname = "", .birth_year = 0, .next = NULL };

    prepend_list(&head, "Pero", "Peric", 1990);
    prepend_list(&head, "Ivo ", "Ivic", 1985);
    append_list(&head, "Mate", "Matic", 1975);

    printf("Lista before deletion:\n");
    print_list(&head);


    position found = find_by_lastname(&head, "Peric");
    if (found) {
        printf("\nFound person: %s %s\n", found->fname, found->lname);
    }
    else {
        printf("\nPerson not found.\n");
    }

  
    if (delete_by_lastname(&head, "Ivic") == EXIT_SUCCESS) {
        printf("\nPerson deleted successfully.\n");
    }
    else {
        printf("\nPerson not found for deletion.\n");
    }

    printf("\nList after deletion:\n");
    print_list(&head);

    return 0;
}
