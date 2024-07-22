/*
===============================================================================
File:                   btree.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo & Clément Dieperink
Creation Date:          27.05.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the utils functions for the B-Tree
                        are implemented.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"

// Création d'un nouveau noeud
Node* create_node(bool is_leaf) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->n = 0;
    new_node->is_leaf = is_leaf;
    for (int i = 0; i < M + 1; i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

// Libération d'un noeud
void free_node(Node* node) {
    if (node != NULL) {
        free(node);
    }
}

// Libération récursive des enfants d'un noeud
void free_tree(Node* node) {
    if (node != NULL) {
        if (!node->is_leaf) {
            for (int i = 0; i <= node->n; i++) {
                free_tree(node->children[i]);
            }
        }
        free_node(node);
    }
}

// Recherche d'une clé dans le B-Tree
Node* search(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    int i = 0;
    while (i < root->n && key > root->keys[i]) {
        i++;
    }

    if (i < root->n && key == root->keys[i]) {
        return root;
    }

    if (root->is_leaf) {
        return NULL;
    }

    return search(root->children[i], key);
}

// Fonction pour insérer une clé dans un noeud non-plein
void insert_non_full(Node* node, int key) {
    int i = node->n - 1;

    if (node->is_leaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        if (node->children[i]->n == M) {
            split_child(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

// Fonction pour diviser un enfant en deux noeuds
void split_child(Node* parent, int i, Node* full_child) {
    Node* new_child = create_node(full_child->is_leaf);
    new_child->n = M / 2;

    for (int j = 0; j < M / 2; j++) {
        new_child->keys[j] = full_child->keys[j + M / 2 + 1];
    }

    if (!full_child->is_leaf) {
        for (int j = 0; j <= M / 2; j++) {
            new_child->children[j] = full_child->children[j + M / 2 + 1];
        }
    }

    full_child->n = M / 2;

    for (int j = parent->n; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = new_child;

    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = full_child->keys[M / 2];
    parent->n++;
}

// Fonction pour insérer une nouvelle clé dans le B-Tree
void insert(Node** root, int key) {
    if (*root == NULL) {
        *root = create_node(true);
    }

    if ((*root)->n == M) {
        Node* new_root = create_node(false);
        new_root->children[0] = *root;
        split_child(new_root, 0, *root);
        int i = 0;
        if (new_root->keys[0] < key) {
            i++;
        }
        insert_non_full(new_root->children[i], key);
        *root = new_root;
    } else {
        insert_non_full(*root, key);
    }
}

// Fonction main pour tester le B-Tree
int main() {
    Node* root = create_node(true);

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);

    Node* result = search(root, 6);
    if (result != NULL) {
        printf("Clé 6 trouvée dans le noeud.\n");
    } else {
        printf("Clé 6 non trouvée.\n");
    }

    free_tree(root);
    return 0;
}
