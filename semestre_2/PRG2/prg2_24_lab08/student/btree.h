/*
===============================================================================
File:                   btree.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo & Clément Dieperink
Creation Date:          27.05.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the utils functions for the B-Tree
                        and the structures are declared.
===============================================================================
*/

#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>

#define M 4 // Définir le nombre maximal de clés par noeud

typedef struct node {
    int n;                  // Nombre de clés actuellement stockées dans le noeud
    int keys[M];            // Tableau de clés
    struct node* children[M + 1]; // Pointeurs vers les enfants
    bool is_leaf;           // Booléen indiquant si le noeud est une feuille
} Node;

// Fonctions pour le B-Tree
Node* create_node(bool is_leaf);
void free_node(Node* node);
void free_tree(Node* node);
Node* search(Node* root, int key);
void insert(Node** root, int key);

#endif // BTREE_H
