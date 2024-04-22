#ifndef ENCODAGE_H
#define ENCODAGE_H

// Fonction pour décoder le texte compressé à partir de la chaîne de caractères binaire
char* charToBinary(char c);
char* stringToBinary(char* str);

void decoderHuffman(Node* racine, char* binaire);
#endif
