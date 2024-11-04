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
int insert_before(position head, position to_insert, char* lname);
int append_list(position head, char* fname, char* lname, int birth_year);
int print_list(position first);
position find_last(position head);
position find_by_lastname(position head, char* lname);
int delete_by_lastname(position head, char* lname);
void sort_list(position head);
int write_to_file(position head, const char* filename);
position read_from_file(const char* filename);
void free_list(position head);

position create_person(char* fname, char* lname, int birth_year) {
    position new_person = (position)malloc(sizeof(person));
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
    position new_person = create_person(fname, lname, birth_year);
    if (!new_person) {
        return -1;
    }

    new_person->next = head->next;
    head->next = new_person;

    return EXIT_SUCCESS;
}

int insert_after(position previous, position to_insert) {
    if (!previous || !to_insert) return -1;

    to_insert->next = previous->next;
    previous->next = to_insert;

    return EXIT_SUCCESS;
}

int insert_before(position head, position to_insert, char* lname) {
    if (!head || !to_insert) return -1;

    position prev = head;
    position curr = head->next;

    while (curr) {
        if (strcmp(curr->lname, lname) == 0) {
            to_insert->next = curr;
            prev->next = to_insert;
            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
    }

    return -1; 
}

int append_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = create_person(fname, lname, birth_year);
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

void sort_list(position head) {
    if (!head->next) return; // Empty or single item

    position i, j;
    char temp_fname[32], temp_lname[32];
    int temp_birth_year;

    for (i = head->next; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->lname, j->lname) > 0) {
                // Swap content of i and j
                strcpy(temp_fname, i->fname);
                strcpy(temp_lname, i->lname);
                temp_birth_year = i->birth_year;

                strcpy(i->fname, j->fname);
                strcpy(i->lname, j->lname);
                i->birth_year = j->birth_year;

                strcpy(j->fname, temp_fname);
                strcpy(j->lname, temp_lname);
                j->birth_year = temp_birth_year;
            }
        }
    }
}

int print_list(position first) {
    position temp = first->next;
    while (temp) {
        printf("First name: %s\nLast name: %s\nBirth year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int write_to_file(position head, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Unable to open file for writing.\n");
        return -1;
    }

    position temp = head->next;
    while (temp) {
        fprintf(file, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

position read_from_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file for reading.\n");
        return NULL;
    }

    person head = { .fname = "", .lname = "", .birth_year = 0, .next = NULL };
    char fname[32], lname[32];
    int birth_year;

    while (fscanf(file, "%s %s %d", fname, lname, &birth_year) == 3) {
        append_list(&head, fname, lname, birth_year);
    }

    fclose(file);
    return head.next; // Return the first person
}

void free_list(position head) {
    position temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    person head = { .fname = "", .lname = "", .birth_year = 0, .next = NULL };

    prepend_list(&head, "Pero", "Peric", 1990);
    prepend_list(&head, "Ivo", "Ivic", 1985);
    append_list(&head, "Mate", "Matic", 1975);

    printf("List before inserting:\n");
    print_list(&head);

    // Insert after specific person
    position insert_after_pos = find_by_lastname(&head, "Peric");
    if (insert_after_pos) {
        position new_person_after = create_person("Ana", "Anic", 1992);
        insert_after(insert_after_pos, new_person_after);
    }

    // Insert before specific person
    position new_person_before = create_person("Luka", "Lukic", 1988);
    insert_before(&head, new_person_before, "Matic");

    printf("\nList after inserting:\n");
    print_list(&head);

    // Oslobađanje memorije
    free_list(head.next);

    return 0;
}
