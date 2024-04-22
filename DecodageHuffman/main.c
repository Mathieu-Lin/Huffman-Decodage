#include <stdio.h>
#include <stdlib.h>
#include "file_reader.h"
#include "node.h"
#include "list_node.h"
#include "encodage.h"

int main() {

    /*********************************************************************************************/
    /* PARTIE 1 : Récupération des données */
    /*********************************************************************************************/

    // Création d'un dictionnaire de fréquences
    DictionnaireFreq *dict = NULL;

    // Lecture du fichier .txt
    lireTxt("alice_freq.txt", &dict);

    // Affichage du dictionnaire
    afficherListe(dict);

    // Inversion de l'ordre du dictionnaire
    inverserListe(&dict);

    // Tri du dictionnaire par ordre croissant avec le tri à bulles
    triBulle(&dict);

    // Affichage de la liste après le tri
    printf("\nListe après le tri à bulles par ordre croissant :\n");
    afficherListe(dict);

    /*********************************************************************************************/
    /* PARTIE 2 : Construction de l'arbre de Huffman */
    /*********************************************************************************************/

    // Convertir le dictionnaire de fréquences en une liste de nœuds
    List_Node *listeNoeuds = convertirEnListeNode(dict);
    afficherListeNodes(listeNoeuds);

    // Construire l'arbre de Huffman à partir de la liste de nœuds
    Node *racineArbre = buildTree(listeNoeuds);

    // Afficher l'arbre de Huffman
    printf("\nArbre de Huffman :\n");
    afficherArbre(racineArbre, 0);

    /*********************************************************************************************/
    /* PARTIE 3 :  Décodage du texte comprimé */
    /*********************************************************************************************/
    // Lecture fichier .bin
    char *octet = lireBin("alice_comp.bin");
    if (octet == NULL) {
        printf("Erreur lors de la lecture du fichier binaire.\n");
    }

    // Afficher chaque caractère de la chaîne de caractères binaire
    printf("Fichier binaire : ");
    for (int i = 0; octet[i] != '\0'; ++i) {
        printf("%c", octet[i]);
    }
    printf("\n");

    char* binaire = stringToBinary(octet);
    printf("Résultat binaire : %s\n", binaire);

    // Décoder la chaîne binaire en utilisant l'arbre de Huffman
    printf("Texte décodé : ");
    decoderHuffman(racineArbre, binaire);

    // Corriger pour que saut soit accepté
    return 0;
}
