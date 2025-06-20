#pragma once

#include <stddef.h>

struct node {
        struct node * next;
        int data;
};

struct node * ll_append(struct node * head, int data);
struct node * ll_at_index(struct node * head, int index);
struct node * ll_insert(struct node * head, int index, int data);
struct node * ll_remove(struct node * head, int index);
size_t ll_length(struct node * head);
struct node * ll_reverse(struct node * head);
void ll_destroy(struct node * head);
struct node * ll_copy(struct node * head);
int ll_equal(struct node * node1, struct node * node2);
