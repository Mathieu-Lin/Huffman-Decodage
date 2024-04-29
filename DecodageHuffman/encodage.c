#include "node.h"
#include "encodage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour convertir un caract�re en sa repr�sentation binaire sur 8 bits
char* charToBinary(char c) {
    char* binary = (char*)malloc(9 * sizeof(char)); // 8 bits + 1 pour le caract�re de fin de cha�ne
    if (binary == NULL) {
        perror("Erreur d'allocation de m�moire");
        exit(EXIT_FAILURE);
    }
    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = (c & (1 << i)) ? '1' : '0'; // Bitwise AND avec un masque de bit
    }
    binary[8] = '\0'; // Terminer la cha�ne avec le caract�re de fin de cha�ne
    return binary;
}

// Fonction pour convertir une cha�ne de caract�res en une cha�ne binaire
char* stringToBinary(char* str, size_t longueur) {
    size_t len = longueur;
    char* binaryString = (char*)malloc((len * 8 + 1) * sizeof(char)); // Chaque caract�re est repr�sent� sur 8 bits, +1 pour le caract�re de fin de cha�ne
    if (binaryString == NULL) {
        perror("Erreur d'allocation de m�moire");
        exit(EXIT_FAILURE);
    }
    binaryString[0] = '\0'; // Initialiser la cha�ne binaire avec une cha�ne vide
    for (size_t i = 0; i < len; i++) {
        char* binaryChar = charToBinary(str[i]);
        strcat(binaryString, binaryChar); // Concat�ner la repr�sentation binaire de chaque caract�re
        free(binaryChar); // Lib�rer la m�moire allou�e pour la repr�sentation binaire du caract�re
    }
    return binaryString;
}


// Fonction pour d�coder une cha�ne binaire en utilisant l'arbre de Huffman
char* decoderHuffman(Node* racine, char* binaire) {
    Node* courant = racine;
    int i = 0;
    char* resultat = (char*)malloc(sizeof(char) * (strlen(binaire) + 1)); // Allouer de la m�moire pour le r�sultat // � debugger
    int index = 0;
    while (binaire[i] != '\0') {
        if (binaire[i] == '0') {
            // Aller � gauche dans l'arbre
            courant = courant->left;
        } else if (binaire[i] == '1') {
            // Aller � droite dans l'arbre
            courant = courant->right;
        }

        // Si on atteint une feuille, ajouter le caract�re au r�sultat et revenir � la racine
        if (courant->left == NULL && courant->right == NULL) {
            // Si le speciale est 'S', ajouter la cha�ne "\n" au r�sultat
            if (courant->speciale == 'S')  {
                resultat[index++] = '\n';
            } else {
                resultat[index++] = courant->lettre;
            }
            courant = racine;
        }

        i++;
    }
    resultat[index] = '\0'; // Terminer la cha�ne r�sultante
    return resultat;
}
