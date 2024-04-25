#ifndef FILE_READER_H
#define FILE_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure pour une paire de cl�-valeur sous une liste chain�e
typedef struct DictionnaireFreq {
    char* cle;   // une caract�re ou un sp�cifique (Saut)
    char* valeur; // une fr�quence
    struct DictionnaireFreq *suiv; // le suivant
} DictionnaireFreq;

// Structure pour avoir un couple bin + longueur.
typedef struct CoupleBinLong {
    char* chaine; // une chaine des caract�res
    size_t longueur; // longueur d'une chaine des caract�res
}CoupleBinLong;


/** Lecture **/
// Fonction pour lire un fichier texte
void lireTxt (const char* fichier, DictionnaireFreq** dict);

// Fonction pour lire un fichier binaire
CoupleBinLong lireBin(const char* fichier);

// Fonction pour lib�rer la m�moire allou�e pour la liste chain�e
void libererDictionnaireFreq(DictionnaireFreq* dict);

/** GestionDico **/
// Fonction pour �changer les donn�es de deux DictionnaireFreq
void echangerDictionnaireFreq(DictionnaireFreq *a, DictionnaireFreq *b);

// Fonction pour trier la liste cha�n�e � l'ordre croissant avec le tri � bulles
void triBulle(DictionnaireFreq **tete);

// Fonction a pour inverser l'ordre de la liste
void inverserListe(DictionnaireFreq **tete);

// Fonction pour afficher la liste cha�n�e
void afficherListe(DictionnaireFreq *tete);

// Fonction pour retirer le premier �l�ment de la liste chain�e
void retirerPremier(DictionnaireFreq **tete);

// Fonction pour ajouter un �l�ment dans la liste chain�e
void ajouterElement(DictionnaireFreq **tete, const char *cle, const char *valeur);

// Fonction pour v�rifier la longueur d'une cha�ne de caract�res
int longueurChaine(const char* chaine);
#endif

