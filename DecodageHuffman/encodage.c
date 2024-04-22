#include "node.h"
#include "encodage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour convertir un caractère en sa représentation binaire sur 8 bits
char* charToBinary(char c) {
    char* binary = (char*)malloc(9 * sizeof(char)); // 8 bits + 1 pour le caractère de fin de chaîne
    if (binary == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 7; i >= 0; i--) {
        binary[7 - i] = (c & (1 << i)) ? '1' : '0'; // Bitwise AND avec un masque de bit
    }
    binary[8] = '\0'; // Terminer la chaîne avec le caractère de fin de chaîne
    return binary;
}

// Fonction pour convertir une chaîne de caractères en une chaîne binaire
char* stringToBinary(char* str) {
    int len = strlen(str);
    char* binaryString = (char*)malloc((len * 8 + 1) * sizeof(char)); // Chaque caractère est représenté sur 8 bits
    if (binaryString == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    binaryString[0] = '\0'; // Initialiser la chaîne binaire avec une chaîne vide
    for (int i = 0; i < len; i++) {
        char* binaryChar = charToBinary(str[i]);
        strcat(binaryString, binaryChar); // Concaténer la représentation binaire de chaque caractère
        free(binaryChar); // Libérer la mémoire allouée pour la représentation binaire du caractère
    }
    return binaryString;
}



// Fonction pour décoder une chaîne binaire en utilisant l'arbre de Huffman
void decoderHuffman(Node* racine, char* binaire) {
    Node* courant = racine;
    int i = 0;
    while (binaire[i] != '\0') {
        if (binaire[i] == '0') {
            // Aller à gauche dans l'arbre
            courant = courant->left;
        } else if (binaire[i] == '1') {
            // Aller à droite dans l'arbre
            courant = courant->right;
        }

        // Si on atteint une feuille, afficher le caractère et revenir à la racine
        if (courant->left == NULL && courant->right == NULL) {
            printf("%c", courant->lettre);
            courant = racine;
        }

        i++;
    }
}
