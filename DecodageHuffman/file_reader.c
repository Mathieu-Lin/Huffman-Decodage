#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"


#define TAILLE_BLOC 1024 // Taille du bloc de lecture


    // Fonction pour lire le fichier .bin compress�
CoupleBinLong lireBin(const char* fichier) {
    // D�claration de la structure CoupleBinLong
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
    fseek(fich, 0, SEEK_END); // D�place le curseur � la fin du fichier
    long tailleFich = ftell(fich); // R�cup�re la position du curseur (qui est la taille du fichier)
    fseek(fich, 0, SEEK_SET); // Remet le curseur au d�but du fichier
    printf("longueur via fichier : %ld \n", tailleFich);

    // Alloue dynamiquement de la m�moire pour stocker le contenu du fichier
    unsigned char* contenu = (unsigned char*)malloc(tailleFich); // Ajoute 1 pour le caract�re de fin de cha�ne
    if (contenu == NULL) {
        printf("Erreur lors de l'allocation de m�moire\n");
        fclose(fich);
        couple.chaine = NULL;
        couple.longueur = 0;
        return couple;
    }

    // Lit le contenu du fichier dans le tampon
    size_t bytesLus = fread(contenu, sizeof(unsigned char), tailleFich, fich);
    printf("longueur lue via fichier : %zu \n", bytesLus);
    if (bytesLus == 0) {
        printf("Erreur lors de la lecture du fichier\n");
        free(contenu);
        fclose(fich);
        couple.chaine = NULL;
        couple.longueur = 0;
        return couple;
    }

    // Attribution des valeurs � la structure CoupleBinLong
    couple.chaine = contenu;
    couple.longueur = bytesLus;

    fclose(fich);
    return couple;
}
// Fonction pour lire le fichier .txt et compl�ter la liste cha�n�e
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
        // Trouver la position du d�but de la valeur apr�s le dernier espace de la cl�
        for (int i = 0; i < strlen(ligne); i++) {
            if (ligne[i] == ' ' && ligne[i + 1] != ' ' && ligne[i + 1] != '\n' && ligne[i + 1] != '\0') {
                valeur = &ligne[i + 1];
                ligne[i] = '\0'; // Finalisation de la chaine
                break;
            }
        }

        char* cle = ligne;
        if (valeur) {
            // Supprimer la newline de la fin de la valeur
            char* newline = strchr(valeur, '\n');
            if (newline) {
                *newline = '\0';
            }

            //if (strcmp(cle, "Saut") == 0) {
            //    cle = "\n";  // Remplace "Saut" avec newline
            //}

            DictionnaireFreq* newEntry = malloc(sizeof(DictionnaireFreq));
            if (newEntry) {
                newEntry->cle = strdup(cle);
                newEntry->valeur = strdup(valeur);
                newEntry->suiv = *dict;
                *dict = newEntry;
            } else {
                fprintf(stderr, "Echec d'allocation du m�moire.\n");
            }
        }
    }

    fclose(fich);
}

// Fonction qui lit le fichier .txt et compl�te pour reste (il sert � completer les bits inf�rieur � 8 bits)
char* lireTxtRest(const char* fichier, char *reste) {
    char chemin[512];
    snprintf(chemin, sizeof(chemin), "%s%s", "../../../Data/Compressed_data/", fichier);
    FILE* fich = fopen(chemin, "r");

    if (fich == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", chemin);
        return reste;
    }

    char ligne[256]; // Assumant que chaque ligne fait au maximum 255 caract�res
    while (fgets(ligne, sizeof(ligne), fich) != NULL) {
        // Concat�nez chaque ligne � la cha�ne existante
        strcat(reste, ligne);
    }
    fclose(fich);
    return reste;
}
// Fonction pour lib�rer dynamiquement la m�moire allou�e pour la liste chain�e
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
/* Partie gestion liste chain�e */
/*********************************************************************/
// Fonction pour �changer les donn�es de deux DictionnaireFreq
void echangerDictionnaireFreq(DictionnaireFreq *a, DictionnaireFreq *b) {
    char* temp_cle = a->cle;
    a->cle = b->cle;
    b->cle = temp_cle;

    char* temp_valeur = a->valeur;
    a->valeur = b->valeur;
    b->valeur = temp_valeur;
}

// Fonction pour trier la liste cha�n�e � l'ordre croissant avec le tri � bulles
void triBulle(DictionnaireFreq **tete) {
    int echanger;
    DictionnaireFreq *ptr;
    DictionnaireFreq *queue = NULL;

    // Cas sp�cial : Si la liste chain�e est vide ou contient un seul �l�ment
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

// Fonction a pour inverser l'ordre de la liste chain�e
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

// Fonction pour afficher la liste cha�n�e
void afficherListe(DictionnaireFreq *tete) {
    DictionnaireFreq *ptr = tete;
    while (ptr != NULL) {
        printf("Cle: %s, Valeur: %s\n", ptr->cle, ptr->valeur);
        ptr = ptr->suiv;
    }
}

// Fonction pour retirer le premier �l�ment de la liste chain�e
void retirerPremier(DictionnaireFreq **tete) {
    if (*tete == NULL) {
        return; // Liste vide, rien � retirer
    }

    DictionnaireFreq *temp = *tete; // Stocke le premier �l�ment dans temp
    *tete = (*tete)->suiv; // Met � jour la t�te pour pointer vers le deuxi�me �l�ment
    free(temp->cle); // Lib�re la m�moire allou�e pour la cl�
    free(temp->valeur); // Lib�re la m�moire allou�e pour la valeur
    free(temp); // Lib�re la m�moire allou�e pour le n�ud retir�
}

// Fonction pour ajouter un �l�ment dans la liste chain�e
void ajouterElement(DictionnaireFreq **tete, const char *cle, const char *valeur) {
    // Cr�ation d'un nouvel �l�ment
    DictionnaireFreq *nouveau = malloc(sizeof(DictionnaireFreq));
    if (nouveau == NULL) {
        printf("Erreur : m�moire insuffisante pour cr�er un nouvel �l�ment.\n");
        return;
    }

    // Allouer de la m�moire pour la cl� si elle est pr�sente
    if (cle != NULL) {
        nouveau->cle = strdup(cle);
        if (nouveau->cle == NULL) {
            printf("Erreur : m�moire insuffisante pour allouer la cl�.\n");
            free(nouveau); // Lib�rer la m�moire allou�e pour le nouvel �l�ment
            return;
        }
    } else {
        nouveau->cle = NULL;
    }

    // Allouer de la m�moire pour la valeur
    nouveau->valeur = strdup(valeur);
    if (nouveau->valeur == NULL) {
        printf("Erreur : m�moire insuffisante pour allouer la valeur.\n");
        free(nouveau->cle); // Lib�rer la m�moire allou�e pour la cl� si elle existe
        free(nouveau); // Lib�rer la m�moire allou�e pour le nouvel �l�ment
        return;
    }

    // Mettre � jour les liens
    nouveau->suiv = *tete;
    *tete = nouveau;
}



// Fonction pour v�rifier la longueur d'une cha�ne de caract�res
int longueurChaine(const char* chaine) {
    int longueur = 0;
    // Parcours de la cha�ne jusqu'� rencontrer le caract�re de fin de cha�ne ('\0')
    while (chaine[longueur] != '\0') {
        longueur++; // Incr�mentation de la longueur pour chaque caract�re non nul
    }
    return longueur; // Retourne la longueur de la cha�ne
}
