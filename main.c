#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

int size = 0;
int replaces[];

int askForSelection() {
    int selection;
    printf("Faites un choix:\n\n1) Compression\n2) Décompression\n\nRéponse: ");
    scanf("%i", &selection);
    return (selection);
}

/*
 * --------------------------
 * Fonctions utilitaires
 * --------------------------
 */

int fileExists(char location[50]) {
    return (access(location, F_OK) == 0);
}

int endwiths(const char *str, const char *suffix) {
    if(!str || !suffix) {
        return 0;
    }
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr) {
        return 0;
    }
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

/*
 * --------------------------
 * Système de compression
 * --------------------------
 */

const int genericSize = 50;

void doCompress(char location[50]) {
    char * compression[] = {};
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int iteration = 0;

    fp = fopen(location, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        char * str = line;
        int init_size = strlen(str);
        char delim[] = " ";
        char *ptr = strtok(str, delim);
        while(ptr != NULL)
        {
            printf("%s\n", ptr);
            char * current = ptr;

            int i = 0;
            int found = 0;
            for (i = 1; i < 1500; i++) {
                char * currentString = compression[i];
                if (currentString == NULL) {
                    continue;
                }
                if (currentString == current) {
                    printf("Current String: %s", currentString);
 !;
                    found = 1;
                    break;
                }
            }

            // If found
            if (found) {
                printf("Found\n");
            } else {
                printf("NOT Found\n");
                compression[iteration] = current;
                iteration = (iteration+1);
            }

            ptr = strtok(NULL, delim);
        }
    }

    fclose(fp);
    if (line) free(line);
}

void handleSelection(int selection) {
    if (selection == 1 || selection == 2) {
        char fileLocation[50] = "";
        printf("\nIndiquez le chemin d'accès : ");
        scanf("%s", fileLocation);
        if (!fileExists(fileLocation)) {
            printf("\nLe fichier selectionné n'existe pas !");
            handleSelection(selection);
            return;
        }
        switch (selection) {
            case 1:
                // Ex : ../main.c
                if(!endwiths(fileLocation, ".txt")) {
                    printf("\nLe fichier n'est pas un fichier texte !");
                    handleSelection(selection);
                    return;
                }
                doCompress(fileLocation);
                break;
            case 2:
                // Do decompression
                break;
        }
    } else {
        printf("Ce choix est invalide, veuillez réessayer !\n");
        int newSelection = askForSelection();
        handleSelection(newSelection);
    }
}

int main() {
    int choice;
    printf("/o\\ Compressito /o\\\n\n");
    int selection = askForSelection();
    handleSelection(selection);                // Ex : ../main.c
    return (0);
}
