#ifndef ENCODAGE_H
#define ENCODAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Fonction pour décoder le texte compressé à partir de la chaîne de caractères binaire
char* charToBinary(char c);
char* stringToBinary(char* str, size_t longueur);

char* decoderHuffman(Node* racine, char* binaire);
#endif
