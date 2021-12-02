#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

// Chaque entrée comprendra une liste de char (mots)
/*
 * Exemple :
 * compression {
 *      {"S", "a", "l", "u", "t"},
 *      {"P", "o", "u", "r", "q", "o", "u", "i", "?"},
 * }
 */
int compressed = 0;
char compression[][256] = {};

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

char * str_replace_first(char * buffer, char * s, char * by)
{
    char * p = strstr(buffer, s), * ret = NULL;
    if (p != NULL)
    {
        size_t len_p = strlen(p), len_s = strlen(s), len_by = strlen(by);
        if (len_s != len_by)
        {
            memmove(p + len_by, p + len_s, len_p);
        }
        strncpy(p, by, len_by);
        ret = buffer;
    }
    return ret;
}

/*
 * --------------------------
 * Système de compression
 * --------------------------
 */

const int genericSize = 50;

void printOne() {
    printf("\n\nTest is %s", compression[5]);
}

int retrieveCompressionId(char * toFound) {
    for (int i = 0; i < sizeof(compression) / sizeof(compression[0]); ++i) {
        printf("Insert in %i", i);
        if (strcmp(toFound, compression[i])) {
            return (i);
        }
    }
    return -1;
}

void doCompress(char location[50]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int iteration = 0;
    fp = fopen(location, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    // Lecture du fichier, pour chaque ligne...
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("\nNouvelle ligne de longueur: %zu", read);
        char * str = line;
        char delim[] = " ";
        char *ptr = strtok(str, delim);
        while(ptr != NULL)
        {
            char * current = ptr;
            str_replace_first(current, "\n", "");
            printf("\n[%s]", current);
            if (retrieveCompressionId(current) != -1) {
                // Existe déjà dans la table de compression
            } else {
                // N'existe pas dans la table de compression
                printf("\nCompression is %i", compressed);
                compression[compressed] = *current;
                printf("\n%s", compression[compressed]);
                compressed = (compressed+1);
                if (compressed == 6) {
                    printOne();
                }
                printf("\n-> Need compression");
            }
            ptr = strtok(NULL, delim); //Test
        }
    }
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
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
