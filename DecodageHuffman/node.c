#include "node.h"
#include "file_reader.h"
#include "list_node.h"
#include <stdio.h>
#include <stdlib.h>

/** Creation d'un noeud **/
// Créer un nœud de l'arbre de Huffman
Node *creerNode(char lettre, int freq) {
    Node *nouvNode = (Node *)malloc(sizeof(Node));
    if (nouvNode != NULL) {
        nouvNode->lettre = lettre;
        nouvNode->freq = freq;
        nouvNode->left = NULL;
        nouvNode->right = NULL;
        nouvNode->speciale = NULL; //Initialise le code binaire à NULL
    }
    return nouvNode;
}

// Créer un nœud de l'arbre de Huffman avec les nœuds gauche et droit
Node *creerNode2(char lettre, int freq, Node *gauche, Node *droite) {
    Node *nouvNode = (Node *)malloc(sizeof(Node));
    if (nouvNode != NULL) {
        nouvNode->lettre = lettre;
        nouvNode->freq = freq;
        nouvNode->left = gauche;
        nouvNode->right = droite;
        nouvNode->speciale = NULL; // Initialise le code binaire à NULL
    }
    return nouvNode;
}

// Créer un nœud de l'arbre de Huffman
Node *creerNode3(char lettre, int freq, char speciale) {
    Node *nouvNode = (Node *)malloc(sizeof(Node));
    if (nouvNode != NULL) {
        nouvNode->lettre = lettre;
        nouvNode->freq = freq;
        nouvNode->left = NULL;
        nouvNode->right = NULL;
        nouvNode->speciale = speciale;
    }
    return nouvNode;
}

// Créer un nœud de l'arbre de Huffman avec les nœuds gauche et droit
Node *creerNode4(char lettre, int freq, Node *gauche, Node *droite, char speciale) {
    Node *nouvNode = (Node *)malloc(sizeof(Node));
    if (nouvNode != NULL) {
        nouvNode->lettre = lettre;
        nouvNode->freq = freq;
        nouvNode->left = gauche;
        nouvNode->right = droite;
        nouvNode->speciale = speciale;
    }
    return nouvNode;
}

/** Gestion d'une liste chainée des noeuds **/
// Fonction pour convertir DictionnaireFreq en List_Node
List_Node *convertirEnListeNode(DictionnaireFreq *dict) {
    List_Node *teteListe = NULL;
    List_Node *dernier = NULL;

    // Parcourir la liste DictionnaireFreq
    while (dict != NULL) {
        // Créer un nouveau nœud List_Node
        List_Node *nouveauNode = (List_Node *)malloc(sizeof(List_Node));
        if (nouveauNode != NULL) {
            // Copier les données de DictionnaireFreq vers List_Node
            if (strcmp(dict->cle, "Saut") == 0) {
                nouveauNode->node.lettre = 'W';  // Si la clé est "Saut", utiliser '\n' comme caractère
                nouveauNode->node.speciale = 'S';
            } else {
                nouveauNode->node.lettre = *(dict->cle);  // Sinon, utiliser la première lettre comme caractère
                nouveauNode->node.speciale = '\0';
            }

            // Convertir la valeur de la fréquence en entier
            int frequence = atoi(dict->valeur);

            // Attribuer cette valeur au nœud
            nouveauNode->node.freq = frequence;
            nouveauNode->node.left = NULL;
            nouveauNode->node.right = NULL;


            // Mettre à jour les pointeurs de la liste
            nouveauNode->suiv = NULL;
            if (teteListe == NULL) {
                teteListe = nouveauNode;
            } else {
                dernier->suiv = nouveauNode;
            }
            dernier = nouveauNode;
        }
        // Passer au prochain élément de la liste DictionnaireFreq
        dict = dict->suiv;
    }

    // Retourner la tête de la liste List_Node
    return teteListe;
}

// Fonction pour échanger les données de deux nœuds
void echangerNodes(List_Node *a, List_Node *b) {
    Node temp = a->node;
    a->node = b->node;
    b->node = temp;
}

// Fonction de tri à bulle pour List_Node par ordre croissant de fréquence
void triBulleNodes(List_Node *tete) {
    int echanger;
    List_Node *ptr;
    List_Node *queue = NULL;

    // Cas spécial : Si la liste est vide ou contient un seul élément
    if (tete == NULL || tete->suiv == NULL) {
        return;
    }

    do {
        echanger = 0;
        ptr = tete;

        while (ptr->suiv != queue) {
            if (ptr->node.freq > ptr->suiv->node.freq) {
                echangerNodes(ptr, ptr->suiv);
                echanger = 1;
            }
            ptr = ptr->suiv;
        }
        queue = ptr;
    } while (echanger);
}

// Fonction pour retirer le premier élément d'une liste chaînée
void retirerPremierNodes(List_Node **tete) {
    if (*tete != NULL) {
        List_Node *temp = *tete;  // Stocke le premier nœud temporairement
        *tete = (*tete)->suiv;    // Met à jour le pointeur de tête pour pointer vers le deuxième nœud
        free(temp);               // Libère la mémoire du premier nœud retiré
    }
}

// Fonction pour ajouter un nœud à une liste chaînée
void ajouterNode(List_Node **tete, Node *node) {
    // Crée un nouveau nœud de la liste
    List_Node *nouvNode = (List_Node *)malloc(sizeof(List_Node));
    if (nouvNode == NULL) {
        perror("Erreur d'allocation de mémoire");
        return;
    }

    // Initialise les champs du nouveau nœud
    nouvNode->node = *node;
    nouvNode->suiv = NULL;

    // Si la liste est vide, le nouveau nœud devient la tête de liste
    if (*tete == NULL) {
        *tete = nouvNode;
    } else {
        // Sinon, trouve le dernier nœud de la liste et ajoute le nouveau nœud à la fin
        List_Node *temp = *tete;
        while (temp->suiv != NULL) {
            temp = temp->suiv;
        }
        temp->suiv = nouvNode;
    }
}

/** Construction d'un arbre sans codage binaire**/
// Construire un arbre de Huffman à partir d'une liste de nœuds
Node *buildTree(List_Node *tete) {
    // Répéter jusqu'à ce qu'il ne reste qu'un seul nœud dans la liste
    while (tete->suiv != NULL) {
        // Tri à bulle par fréquence
        triBulleNodes(tete);

        // Prendre les deux nœuds avec les fréquences les plus faibles
        Node *left = &(tete->node);
        Node *right = &(tete->suiv->node);

        // Créer un nœud parent avec ses deux nœuds fils
        Node *parent = creerNode('\0', left->freq + right->freq);
        if (left->speciale != NULL) {
            parent->left = creerNode4(left->lettre, left->freq,left->left, left->right,left->speciale);
        } else {
            parent->left = creerNode2(left->lettre, left->freq,left->left, left->right);
        }
        if (right->speciale != NULL){
            parent->right = creerNode4(right->lettre, right->freq, right->left, right->right,right->speciale);
        }else {
            parent->right = creerNode2(right->lettre, right->freq, right->left, right->right);
        }

        // Retirer les deux nœuds avec les fréquences les plus faibles
        retirerPremierNodes(&tete);
        retirerPremierNodes(&tete);
        // Ajouter le nouveau nœud parent à la liste
        ajouterNode(&tete, parent);
    }
    return &(tete->node); // Retourner la racine de l'arbre de Huffman construit
}

// Fonction qui permet d'afficher un arbre en récursif
void afficherArbre(Node *racine, int niveau) {
    if (racine == NULL) {
        return; // Condition d'arrêt : nœud nul
    }

    // Afficher le sous-arbre droit
    afficherArbre(racine->right, niveau + 1);

    // Afficher l'indentation selon le niveau
    for (int i = 0; i < niveau; i++) {
        printf("    ");
    }

    // Afficher le nœud actuel
    printf("(%c, %d, %c)\n", racine->lettre, racine->freq, racine->speciale);

    // Afficher le sous-arbre gauche
    afficherArbre(racine->left, niveau + 1);
}
// Fonction pour afficher les éléments de la liste chaînée
void afficherListeNodes(List_Node *tete) {
    List_Node *courant = tete;

    printf("Liste de noeuds :\n");
    while (courant != NULL) {
        printf("(%c, %d) -> ", courant->node.lettre, courant->node.freq);
        courant = courant->suiv;
    }
    printf("NULL\n");
}

