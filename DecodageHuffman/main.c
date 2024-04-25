#include <stdio.h>
#include <stdlib.h>
#include "file_reader.h"
#include "node.h"
#include "list_node.h"
#include "encodage.h"
#include "file_logger.h"

// Sources : Connaissances du module INFO403 du PEIP2-INFO de l'USMB (Université Savoie Mont Blanc). 2022-2023
// IDE utilisé : CodeBlock
int main() {


    /*********************************************************************************************/
    /* PARTIE 1 : Récupération des données */
    /*********************************************************************************************/
    // Lecture des restes des bits
    char reste[128]; // Assumant une taille maximale pour la chaîne restante
    reste[0] = '\0'; // Initialise la chaîne restante à une chaîne vide
    char *resultatRest = lireTxtRest("ok_bits.txt", reste);
    printf("Contenu du fichier texte : %s\n", resultatRest);


    // Création d'un dictionnaire de fréquences
    DictionnaireFreq *dict = NULL;

    // Lecture du fichier .txt
    lireTxt("ok_freq.txt", &dict);


    // Affichage du dictionnaire
    //afficherListe(dict);

    // Inversion de l'ordre du dictionnaire
    inverserListe(&dict);

    // Tri du dictionnaire par ordre croissant avec le tri à bulles
    //triBulle(&dict);

    // Affichage de la liste après le tri
    //printf("\nListe après le tri à bulles par ordre croissant :\n");
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
    CoupleBinLong couple = lireBin("ok_comp.bin");
    // Si la lecture est un succès,
    if (couple.chaine != NULL) {
        // Il annonce la longueur du fichier
        printf("La longueur de la chaine est : %zu\n", couple.longueur);

        // Afficher chaque caractère de la chaîne de caractères binaire
        printf("Fichier binaire : ");
        // Convertir la chaîne binaire en une chaîne de caractères
        char* binaire = stringToBinary(couple.chaine,couple.longueur);
        strcat(binaire, resultatRest);
        // Affichage des octets dont le fichier .bin contient
        for (size_t i = 0; i < couple.longueur; ++i) {
            printf("%c", couple.chaine[i]);
        }
        // Affichage des bits provenant des octets
        printf(" \n %s", binaire);
        printf("\n");
        // Décoder la chaîne binaire en utilisant l'arbre de Huffman
        //printf("Texte décodé : \n");
        // Transformation vers une chaine des caractères non compressé
        char* resultat = decoderHuffman(racineArbre, binaire);
        //printf("Chaîne décodée : \n%s\n", resultat);

        // Enregistrer le résultat décodé dans un fichier
        enregistrerResultat(resultat, "bonjour.txt");


        /*********************************************************************************************/
        /* PARTIE 4 :  Détermination du taux de compression */
        /*********************************************************************************************/
        // Variables de taille dont initiale est le fichier .bin et finale est le fichier décompressé
        long int tailleInitiale = couple.longueur;
        long int tailleFinale = strlen(resultat);

        // Calcul du taux de compression
        double tauxCompression = (1.0 - ((double)tailleFinale / (double)tailleInitiale)) * 100.0;

        // Affichage du résultat des tailles et le taux de compression (dans ce cas, il est négatif)
        printf("Taille initiale : %ld octets\n", tailleInitiale);
        printf("Taille finale : %ld octets\n", tailleFinale);
        printf("Taux de compression : %.2f%%\n", tauxCompression);

        /*********************************************************************************************/
        /* PARTIE 5 :   Détermination du nombre moyen de bits de stockage d’un caractère du texte compressé*/
        /*********************************************************************************************/
        // Variable pour la valeur réelle moyenne
        double nombreMoyenBitsParCaractere;

        // Calcul du nombre moyen de bits par caractère
        nombreMoyenBitsParCaractere = (double)tailleFinale / tailleInitiale;

        // Affichage du résultat de la moyenne
        printf("Nombre moyen de bits par caractère dans le texte compressé : %.2f\n", nombreMoyenBitsParCaractere);

        // Libérer la mémoire allouée pour la chaîne binaire
        free(binaire);
        // Libérer la mémoire allouée pour la chaîne dans la structure CoupleBinLong
        free(couple.chaine);
        free(reste);
        free(resultatRest);
        free(resultat);

    } else {
        printf("Erreur lors de la lecture du fichier.\n");
    }
    /*********************************************************************************************/
    /* PARTIE 6 :  Echange entre utilisateur et programme */
    /*********************************************************************************************/

    // Variables que l'utilisateur va entrer
    char nomFichier[100];
    char nomFichierBin[100];
    char nomFichierBits[100];
    char nomEnreg[100];
    char choix;

    // Boucle while
    do {
    /*********************************************************************************************/
    /* PARTIE 0 : Demande aux utilisateurs */
    /*********************************************************************************************/
        // Demande à l'utilisateur d'entrer le nom du fichier.txt
        printf("Entrez le nom du fichier comme nomFichier.txt (s pour sortir) : ");
        scanf("%99s", nomFichier);

        // Vérifie si l'utilisateur veut sortir
        if (strcmp(nomFichier, "s") == 0) {
            printf("Sortie du programme.\n");
            break;
        }
        // Demande à l'utilisateur d'entrer le nom du fichier.bin
        printf("Entrez le nom du fichier comme nomFichier.bin (s pour sortir) : ");
        scanf("%99s", nomFichierBin);

        // Vérifie si l'utilisateur veut sortir
        if (strcmp(nomFichierBin, "s") == 0) {
            printf("Sortie du programme.\n");
            break;
        }
        // Demande à l'utilisateur d'entrer le nom du fichier.bin
        printf("Entrez le nom du fichier comme nom_Bits.txt (s pour sortir) : ");
        scanf("%99s", nomFichierBits);

        // Vérifie si l'utilisateur veut sortir
        if (strcmp(nomFichierBits, "s") == 0) {
            printf("Sortie du programme.\n");
            break;
        }

        // Demande à l'utilisateur d'entrer le nom du fichier.bin
        printf("Entrez le nom du fichier comme nomEnreg.txt (s pour sortir) : ");
        scanf("%99s", nomEnreg);

        // Vérifie si l'utilisateur veut sortir
        if (strcmp(nomEnreg, "s") == 0) {
            printf("Sortie du programme.\n");
            break;
        }



    /*********************************************************************************************/
    /* PARTIE 1 : Récupération des données */
    /*********************************************************************************************/
        // Debut du décodage
        // Lecture des restes des bits
        char reste[128]; // Assumant une taille maximale pour la chaîne restante
        reste[0] = '\0'; // Initialise la chaîne restante à une chaîne vide
        char *resultatRest = lireTxtRest(nomFichierBits, reste);
        printf("Contenu du fichier texte : %s\n", resultatRest);
        // Création d'un dictionnaire de fréquences
        DictionnaireFreq *dict = NULL;

        // Lecture du fichier .txt
        lireTxt(nomFichier, &dict);

        // Inversion de l'ordre du dictionnaire
        inverserListe(&dict);

        //printf("\nListe après le tri à bulles par ordre croissant :\n");
        afficherListe(dict);

    /*********************************************************************************************/
    /* PARTIE 2 : Construction de l’arbre de Huffman */
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
    /* PARTIE 3 : Décodage du texte comprimé  */
    /*********************************************************************************************/
        // Lecture fichier .bin
        CoupleBinLong couple = lireBin("bonjour_comp.bin");
        if (couple.chaine != NULL) {
            // Affichage de la longueur du fichier .bin
            printf("La longueur de la chaine est : %zu\n", couple.longueur);

            // Afficher chaque caractère de la chaîne de caractères binaire
            printf("Fichier binaire : ");

            // Convertir la chaîne binaire en une chaîne de caractères
            char* binaire = stringToBinary(couple.chaine,couple.longueur);

            // Ajout du reste
            strcat(binaire, resultatRest);
            // Affichage du contenu du fichier .bin (utilisé seulement pour tester)
            for (size_t i = 0; i < couple.longueur; ++i) {
                //printf("%c", couple.chaine[i]);
            }
            //printf(" \n %s", binaire);
            printf("\n");
            // Décoder la chaîne binaire en utilisant l'arbre de Huffman
            //printf("Texte décodé : \n");
            // Transformation vers une chaine des caractères décompressé
            char* resultat = decoderHuffman(racineArbre, binaire);
            //printf("Chaîne décodée : \n%s\n", resultat);

            // Enregistrer le résultat décodé dans un fichier
            enregistrerResultat(resultat,nomEnreg );


            /*********************************************************************************************/
            /* PARTIE 4 :  Détermination du taux de compression */
            /*********************************************************************************************/
            // Variables pour les longueurs dont l'initiale grâce fichier.bin et l'autre grâce au fichier.txt décompressé.
            long int tailleInitiale = couple.longueur;
            long int tailleFinale = strlen(resultat);

            // Calcul du taux de compression
            double tauxCompression = (1.0 - ((double)tailleFinale / (double)tailleInitiale)) * 100.0;

            // Affichage du résultat des tailles et du taux de compression (négatif vue de la décompression)
            printf("Taille initiale : %ld octets\n", tailleInitiale);
            printf("Taille finale : %ld octets\n", tailleFinale);
            printf("Taux de compression : %.2f%%\n", tauxCompression);

            /*********************************************************************************************/
            /* PARTIE 5 :   Détermination du nombre moyen de bits de stockage d’un caractère du texte compressé*/
            /*********************************************************************************************/
            // Variable moyenne de valeur réelle
            double nombreMoyenBitsParCaractere;

            // Calcul du nombre moyen de bits par caractère
            nombreMoyenBitsParCaractere = (double)tailleFinale / tailleInitiale;

            // Affichage du résultat du moyenne
            printf("Nombre moyen de bits par caractère dans le texte compressé : %.2f\n", nombreMoyenBitsParCaractere);

            // Libérer la mémoire allouée pour la chaîne binaire
            free(binaire);
            // Libérer la mémoire allouée pour la chaîne dans la structure CoupleBinLong
            free(couple.chaine);
            free(resultat);
        } else {
            printf("Erreur lors de la lecture du fichier.\n");
        }
        free(reste);
        free(resultatRest);


        } while (choix != 's');

    // FIN du programme
    return 0;
}





