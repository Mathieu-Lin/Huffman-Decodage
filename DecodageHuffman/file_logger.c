#include <stdio.h>
#include "file_logger.h"

// Fonction qui permet d'enregistrer le r�sultat d�compress� dans un "nomFichier = 'fichier.txt' "
void enregistrerResultat(const char* resultat, const char* nomFichier) {
    char chemin[512];
    snprintf(chemin, sizeof(chemin), "%s%s", "../../../Data/Uncompressed_data/", nomFichier);
    // Ouvrir le fichier en mode �criture
    FILE* fichier = fopen(chemin, "w");

    // V�rifier si l'ouverture du fichier a r�ussi
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }

    // �crire la cha�ne r�sultante dans le fichier
    fprintf(fichier, "%s", resultat);

    // Fermer le fichier
    fclose(fichier);

    printf("Le r�sultat a �t� enregistr� dans le fichier %s\n", nomFichier);
}
