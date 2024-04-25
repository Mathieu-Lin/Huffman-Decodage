#ifndef ENCODAGE_H
#define ENCODAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Fonction pour convertir un caractère en sa représentation binaire sur 8 bits
char* charToBinary(char c);

// Fonction pour convertir une chaîne de caractères en une chaîne binaire
char* stringToBinary(char* str, size_t longueur);

// Fonction pour décoder une chaîne binaire en utilisant l'arbre de Huffman
char* decoderHuffman(Node* racine, char* binaire);
#endif
