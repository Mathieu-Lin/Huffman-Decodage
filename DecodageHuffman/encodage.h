#ifndef ENCODAGE_H
#define ENCODAGE_H

// Fonction pour d�coder le texte compress� � partir de la cha�ne de caract�res binaire
char* charToBinary(char c);
char* stringToBinary(char* str);

void decoderHuffman(Node* racine, char* binaire);
#endif
