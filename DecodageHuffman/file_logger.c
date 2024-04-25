#include <stdio.h>
#include "file_logger.h"

// Fonction qui permet d'enregistrer le résultat décompressé dans un "nomFichier = 'fichier.txt' "
void enregistrerResultat(const char* resultat, const char* nomFichier) {
    char chemin[512];
    snprintf(chemin, sizeof(chemin), "%s%s", "../../../Data/Uncompressed_data/", nomFichier);
    // Ouvrir le fichier en mode écriture
    FILE* fichier = fopen(chemin, "w");

    // Vérifier si l'ouverture du fichier a réussi
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }

    // Écrire la chaîne résultante dans le fichier
    fprintf(fichier, "%s", resultat);

    // Fermer le fichier
    fclose(fichier);

    printf("Le résultat a été enregistré dans le fichier %s\n", nomFichier);
}
