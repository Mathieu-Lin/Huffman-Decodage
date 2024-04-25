#ifndef FILE_READER_H
#define FILE_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure pour une paire de clé-valeur sous une liste chainée
typedef struct DictionnaireFreq {
    char* cle;   // une caractère ou un spécifique (Saut)
    char* valeur; // une fréquence
    struct DictionnaireFreq *suiv; // le suivant
} DictionnaireFreq;

// Structure pour avoir un couple bin + longueur.
typedef struct CoupleBinLong {
    char* chaine; // une chaine des caractères
    size_t longueur; // longueur d'une chaine des caractères
}CoupleBinLong;


/** Lecture **/
// Fonction pour lire un fichier texte
void lireTxt (const char* fichier, DictionnaireFreq** dict);

// Fonction pour lire un fichier binaire
CoupleBinLong lireBin(const char* fichier);

// Fonction pour libérer la mémoire allouée pour la liste chainée
void libererDictionnaireFreq(DictionnaireFreq* dict);

/** GestionDico **/
// Fonction pour échanger les données de deux DictionnaireFreq
void echangerDictionnaireFreq(DictionnaireFreq *a, DictionnaireFreq *b);

// Fonction pour trier la liste chaînée à l'ordre croissant avec le tri à bulles
void triBulle(DictionnaireFreq **tete);

// Fonction a pour inverser l'ordre de la liste
void inverserListe(DictionnaireFreq **tete);

// Fonction pour afficher la liste chaînée
void afficherListe(DictionnaireFreq *tete);

// Fonction pour retirer le premier élément de la liste chainée
void retirerPremier(DictionnaireFreq **tete);

// Fonction pour ajouter un élément dans la liste chainée
void ajouterElement(DictionnaireFreq **tete, const char *cle, const char *valeur);

// Fonction pour vérifier la longueur d'une chaîne de caractères
int longueurChaine(const char* chaine);
#endif

