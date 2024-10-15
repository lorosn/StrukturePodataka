#define MAX_BOD 100.0
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char ime[50];
    char prez[50];
    float bod;
} student;

int main()
{
    student* stud, tren;
    int n = 0;

    stud = malloc(sizeof(student));
    if (stud == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return 1;
    }
    printf("Uspesno alocirana pocetna memorija.\n");

    FILE* fp = fopen("Studenti.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        free(stud);
        return 1;
    }

    while (fgetc(fp) != '\n');

    while (fscanf(fp, "%s %s %f", tren.ime, tren.prez, &tren.bod) == 3)
    {
        student* temp = realloc(stud, (n + 1) * sizeof(student));
        if (temp == NULL) {
            printf("Greska pri realokaciji memorije!\n");
            free(stud);
            fclose(fp);
            return 1;
        }
        stud = temp;
        stud[n] = tren;
        n++;
    }

    fclose(fp);

    printf("Ime\t\tPrezime\t\tBodovi\t\tRelativni Bodovi\n");
    for (int i = 0; i < n; i++) {
        float relBod = (stud[i].bod / MAX_BOD) * 100;
        printf("%s %s %.2f\t\t%.2f%%\n", stud[i].ime, stud[i].prez, stud[i].bod, relBod);
    }

    free(stud);
    return 0;
}