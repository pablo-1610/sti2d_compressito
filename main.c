#include <stdio.h>
#include <stdlib.h>

int size = 0;
int replaces[];

char askForFileLocation() {
    printf("\nInidiquez le chemin du fichier: ");
    char fileLocation[15];
    scanf("%s", &fileLocation);
    printf("Test, selection: %c", fileLocation);
    return fileLocation;
}

int askForSelection() {
    int selection;
    printf("Faites un choix:\n\n1) Compression\n2) Décompression\n\nRéponse: ");
    scanf("%i", &selection);
    return (selection);
}

void handleSelection(int selection) {
    if (selection == 1 || selection == 2) {
        char fileLocation = askForFileLocation();
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
    handleSelection(selection);
    return (0);
}
