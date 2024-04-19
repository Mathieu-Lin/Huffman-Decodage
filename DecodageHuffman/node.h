#ifndef NODE_H
#define NODE_H

// Structure pour un nœud de l'arbre de Huffman
typedef struct Node {
    char lettre;          // Caractère du nœud
    int freq;             // Fréquence du caractère
    struct Node *left;    // Pointeur vers le sous-arbre gauche
    struct Node *right;   // Pointeur vers le sous-arbre droit
    char *code_binaire;   // Code binaire attribué au caractère
} Node;

typedef struct List_Node{
    Node node;
    struct List_Node *suiv;
} List_Node;

// Créer un nœud de l'arbre de Huffman
Node *creerNode(char lettre, int freq);
Node *creerNode2(char lettre, int freq, Node *gauche, Node *droite);


// Fonction pour échanger les données de deux nœuds
void echangerNodes(List_Node *a, List_Node *b);

// Fonction de tri à bulle pour List_Node par ordre croissant de fréquence
void triBulleNodes(List_Node *tete);

// Fonction pour retirer le premier élément d'une liste chaînée
void retirerPremierNodes(List_Node **tete);

// Fonction pour ajouter un nœud à une liste chaînée
void ajouterNode(List_Node **tete, Node *node);

// Construire un arbre de Huffman à partir d'une liste de nœuds
Node *buildTree(List_Node *liste);

// Fonction qui permet d'afficher un arbre en récursif
void afficherArbre(Node *racine, int niveau);

void afficherListeNodes(List_Node *tete);

#endif
