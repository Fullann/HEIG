/*
===============================================================================
File:                   unit_test.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          27.05.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the units tests must be
                        implemented
===============================================================================
*/

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "btree.h"

void test_create_node() {
    Node* node = create_node(true);
    CU_ASSERT_PTR_NOT_NULL(node);
    CU_ASSERT_TRUE(node->is_leaf);
    CU_ASSERT_EQUAL(node->n, 0);
    free_node(node);
}

void test_insert_simple() {
    Node* root = create_node(true);
    insert(&root, 10);
    CU_ASSERT_PTR_NOT_NULL(root);
    CU_ASSERT_EQUAL(root->n, 1);
    CU_ASSERT_EQUAL(root->keys[0], 10);
    CU_ASSERT_TRUE(root->is_leaf);
    free_tree(root);
}

void test_search_simple() {
    Node* root = create_node(true);
    insert(&root, 10);
    Node* result = search(root, 10);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(result->keys[0], 10);
    free_tree(root);
}

void test_insert_with_split() {
    Node* root = create_node(true);
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    CU_ASSERT_EQUAL(root->n, 1);
    CU_ASSERT_EQUAL(root->keys[0], 10);
    CU_ASSERT_FALSE(root->is_leaf);
    CU_ASSERT_PTR_NOT_NULL(root->children[0]);
    CU_ASSERT_PTR_NOT_NULL(root->children[1]);
    free_tree(root);
}

void test_insert_with_two_splits() {
    Node* root = create_node(true);
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);
    CU_ASSERT_EQUAL(root->n, 1);
    CU_ASSERT_EQUAL(root->keys[0], 10);
    CU_ASSERT_FALSE(root->is_leaf);
    CU_ASSERT_PTR_NOT_NULL(root->children[0]);
    CU_ASSERT_PTR_NOT_NULL(root->children[1]);
    free_tree(root);
}

void test_insert_with_deep_split() {
    Node* root = create_node(true);
    for (int i = 1; i <= 20; i++) {
        insert(&root, i);
    }
    CU_ASSERT_EQUAL(root->n, 1);
    CU_ASSERT_FALSE(root->is_leaf);
    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("BTree Tests", 0, 0);

    CU_add_test(suite, "test_create_node", test_create_node);
    CU_add_test(suite, "test_insert_simple", test_insert_simple);
    CU_add_test(suite, "test_search_simple", test_search_simple);
    CU_add_test(suite, "test_insert_with_split", test_insert_with_split);
    CU_add_test(suite, "test_insert_with_two_splits", test_insert_with_two_splits);
    CU_add_test(suite, "test_insert_with_deep_split", test_insert_with_deep_split);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
