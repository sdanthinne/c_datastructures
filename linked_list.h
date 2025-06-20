#pragma once

#include <stddef.h>

struct node {
        struct node * next;
        int data;
};

struct node * append(struct node * head, int data);
struct node * at_index(struct node * head, int index);
struct node * insert(struct node * head, int index, int data);
size_t length(struct node * head);
struct node * reverse(struct node * head);
void destroy(struct node * head);
struct node * copy(struct node * head);
int equal(struct node * node1, struct node * node2);
