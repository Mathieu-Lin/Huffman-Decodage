#ifndef ENCODAGE_H
#define ENCODAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Fonction pour convertir un caract�re en sa repr�sentation binaire sur 8 bits
char* charToBinary(char c);

// Fonction pour convertir une cha�ne de caract�res en une cha�ne binaire
char* stringToBinary(char* str, size_t longueur);

// Fonction pour d�coder une cha�ne binaire en utilisant l'arbre de Huffman
char* decoderHuffman(Node* racine, char* binaire);
#endif
