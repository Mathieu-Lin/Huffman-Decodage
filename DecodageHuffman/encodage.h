#ifndef ENCODAGE_H
#define ENCODAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Fonction pour d�coder le texte compress� � partir de la cha�ne de caract�res binaire
char* charToBinary(char c);
char* stringToBinary(char* str, size_t longueur);

char* decoderHuffman(Node* racine, char* binaire);
#endif
