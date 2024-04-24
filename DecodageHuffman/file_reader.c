#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"


#define TAILLE_BLOC 1024 // Taille du bloc de lecture


    // Fonction pour lire le fichier .bin compressé
CoupleBinLong lireBin(const char* fichier) {
    // Déclaration de la structure CoupleBinLong
    CoupleBinLong couple;

    // Stockage du chemin
    char chemin[512];
    snprintf(chemin, sizeof(chemin), "%s%s", "../../../Data/Compressed_data/", fichier);
    FILE* fich = fopen(chemin, "rb"); // Ouverture du fichier en mode binaire

    // Si fichier inexistant :
    if (fich == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", chemin);
        couple.chaine = NULL;
        couple.longueur = 0;
        return couple;
    }

    // Obtient la taille du fichier
    fseek(fich, 0, SEEK_END); // Déplace le curseur à la fin du fichier
    long tailleFich = ftell(fich); // Récupère la position du curseur (qui est la taille du fichier)
    fseek(fich, 0, SEEK_SET); // Remet le curseur au début du fichier
    printf("longueur via fichier : %ld \n", tailleFich);

    // Alloue dynamiquement de la mémoire pour stocker le contenu du fichier
    char* contenu = (char*)malloc(tailleFich); // Ajoute 1 pour le caractère de fin de chaîne
    if (contenu == NULL) {
        printf("Erreur lors de l'allocation de mémoire\n");
        fclose(fich);
        couple.chaine = NULL;
        couple.longueur = 0;
        return couple;
    }

    // Lit le contenu du fichier dans le tampon
    size_t bytesLus = fread(contenu, 1, tailleFich, fich);
    printf("longueur lue via fichier : %zu \n", bytesLus);
    if (bytesLus != tailleFich) {
        printf("Erreur lors de la lecture du fichier\n");
        free(contenu);
        fclose(fich);
        couple.chaine = NULL;
        couple.longueur = 0;
        return couple;
    }
    contenu[bytesLus] = '\0'; // Ajoute le caractère de fin de chaîne

    // Attribution des valeurs à la structure CoupleBinLong
    couple.chaine = contenu;
    couple.longueur = bytesLus;

    // Affichage de chaque caractère du contenu
    //printf("Contenu du fichier :\n");
    for (size_t i = 0; i < bytesLus; ++i) {
        //printf("%c", contenu[i]);
    }
    //printf("\n");

    fclose(fich);
    return couple;
}

// Fonction pour lire le fichier .txt et compléter la liste chaînée
void lireTxt(const char* fichier, DictionnaireFreq** dict) {
    char chemin[512];
    snprintf(chemin, sizeof(chemin), "%s%s", "../../../Data/Compressed_data/", fichier);
    FILE* fich = fopen(chemin, "r");
    if (fich == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", chemin);
        return;
    }

    char ligne[2048];
    while (fgets(ligne, sizeof(ligne), fich) != NULL) {
        char* valeur = NULL;
        // Trouver la position du début de la valeur après le dernier espace de la clé
        for (int i = 0; i < strlen(ligne); i++) {
            if (ligne[i] == ' ' && ligne[i + 1] != ' ' && ligne[i + 1] != '\n' && ligne[i + 1] != '\0') {
                valeur = &ligne[i + 1];
                ligne[i] = '\0'; // End the key string here
                break;
            }
        }

        char* cle = ligne;
        if (valeur) {
            // Remove potential newline from the end of valeur
            char* newline = strchr(valeur, '\n');
            if (newline) {
                *newline = '\0';
            }

            //if (strcmp(cle, "Saut") == 0) {
            //    cle = "\n";  // Replace "Saut" with newline
            //}

            DictionnaireFreq* newEntry = malloc(sizeof(DictionnaireFreq));
            if (newEntry) {
                newEntry->cle = strdup(cle);
                newEntry->valeur = strdup(valeur);
                newEntry->suiv = *dict;
                *dict = newEntry;
            } else {
                fprintf(stderr, "Memory allocation failed for new dictionary entry.\n");
            }
        }
    }

    fclose(fich);
}
// Fonction pour libérer dynamiquement la mémoire allouée pour la liste chainée
void libererDictionnaireFreq(DictionnaireFreq* dict) {
    while (dict) {
        DictionnaireFreq* temp = dict;
        dict = dict->suiv;
        free(temp->cle);
        free(temp->valeur);
        free(temp);
    }
}

    /*********************************************************************************/





/*********************************************************************/
/* Partie gestion liste chainée */
/*********************************************************************/
// Fonction pour échanger les données de deux DictionnaireFreq
void echangerDictionnaireFreq(DictionnaireFreq *a, DictionnaireFreq *b) {
    char* temp_cle = a->cle;
    a->cle = b->cle;
    b->cle = temp_cle;

    char* temp_valeur = a->valeur;
    a->valeur = b->valeur;
    b->valeur = temp_valeur;
}

// Fonction pour trier la liste chaînée à l'ordre croissant avec le tri à bulles
void triBulle(DictionnaireFreq **tete) {
    int echanger;
    DictionnaireFreq *ptr;
    DictionnaireFreq *queue = NULL;

    // Cas spécial : Si la liste chainée est vide ou contient un seul élément
    if (*tete == NULL || (*tete)->suiv == NULL) {
        return;
    }

    do {
        echanger = 0;
        ptr = *tete;

        while (ptr->suiv != queue) {
            if (strcmp(ptr->valeur, ptr->suiv->valeur) > 0) {
                echangerDictionnaireFreq(ptr, ptr->suiv);
                echanger = 1;
            }
            ptr = ptr->suiv;
        }
        queue = ptr;
    } while (echanger);
}

// Fonction a pour inverser l'ordre de la liste chainée
void inverserListe(DictionnaireFreq **tete) {
    DictionnaireFreq *precedent = NULL;
    DictionnaireFreq *courant = *tete;
    DictionnaireFreq *suivant = NULL;

    while (courant != NULL) {
        suivant = courant->suiv;
        courant->suiv = precedent;
        precedent = courant;
        courant = suivant;
    }

    *tete = precedent;
}

// Fonction pour afficher la liste chaînée
void afficherListe(DictionnaireFreq *tete) {
    DictionnaireFreq *ptr = tete;
    while (ptr != NULL) {
        printf("Cle: %s, Valeur: %s\n", ptr->cle, ptr->valeur);
        ptr = ptr->suiv;
    }
}

// Fonction pour retirer le premier élément de la liste chainée
void retirerPremier(DictionnaireFreq **tete) {
    if (*tete == NULL) {
        return; // Liste vide, rien à retirer
    }

    DictionnaireFreq *temp = *tete; // Stocke le premier élément dans temp
    *tete = (*tete)->suiv; // Met à jour la tête pour pointer vers le deuxième élément
    free(temp->cle); // Libère la mémoire allouée pour la clé
    free(temp->valeur); // Libère la mémoire allouée pour la valeur
    free(temp); // Libère la mémoire allouée pour le nœud retiré
}

// Fonction pour ajouter un élément dans la liste chainée
void ajouterElement(DictionnaireFreq **tete, const char *cle, const char *valeur) {
    // Création d'un nouvel élément
    DictionnaireFreq *nouveau = malloc(sizeof(DictionnaireFreq));
    if (nouveau == NULL) {
        printf("Erreur : mémoire insuffisante pour créer un nouvel élément.\n");
        return;
    }

    // Allouer de la mémoire pour la clé si elle est présente
    if (cle != NULL) {
        nouveau->cle = strdup(cle);
        if (nouveau->cle == NULL) {
            printf("Erreur : mémoire insuffisante pour allouer la clé.\n");
            free(nouveau); // Libérer la mémoire allouée pour le nouvel élément
            return;
        }
    } else {
        nouveau->cle = NULL;
    }

    // Allouer de la mémoire pour la valeur
    nouveau->valeur = strdup(valeur);
    if (nouveau->valeur == NULL) {
        printf("Erreur : mémoire insuffisante pour allouer la valeur.\n");
        free(nouveau->cle); // Libérer la mémoire allouée pour la clé si elle existe
        free(nouveau); // Libérer la mémoire allouée pour le nouvel élément
        return;
    }

    // Mettre à jour les liens
    nouveau->suiv = *tete;
    *tete = nouveau;
}



// Fonction pour vérifier la longueur d'une chaîne de caractères
int longueurChaine(const char* chaine) {
    int longueur = 0;
    // Parcours de la chaîne jusqu'à rencontrer le caractère de fin de chaîne ('\0')
    while (chaine[longueur] != '\0') {
        longueur++; // Incrémentation de la longueur pour chaque caractère non nul
    }
    return longueur; // Retourne la longueur de la chaîne
}
