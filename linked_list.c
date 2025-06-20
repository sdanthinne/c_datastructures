#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

struct node {
        struct node * next;
        int data;
};

static void print_list(struct node * head)
{
        if(!head)
                return;
        printf("%d->", head->data);
        print_list(head->next);
}

static struct node * endof(struct node * head)
{
        if(!head->next)
                return head;
        return endof(head->next);
}

static struct node * new_node(int data)
{
        struct node * node = malloc(sizeof(struct node));
        assert(node);
        node->data = data;
        node->next = NULL;
        return node;
}


struct node * append(struct node * head, int data)
{
        struct node * new = new_node(data);
        if(head)
        {
                struct node * end = endof(head);
                end->next = new;
        }
        return head ? head : new;
}

struct node * at_index(struct node * head, int index)
{
        if(!head)
                return NULL;
        if(!index)
                return head;
        return at_index(head->next, index-1);
}

struct node * insert(struct node * head, int index, int data)
{
        struct node * before = at_index(head, index);
        struct node * new = new_node(data);
        if(before)
        {
                new->next = before->next;
                before->next = new;
        }
        return head ? head : new;
}

size_t length(struct node * head)
{
        if(!head)
                return 0;
        return length(head->next) + 1;
}

static struct node * help_reverse(struct node * current)
{
        struct node * call_next = current->next;
        if(!call_next)
                return NULL;
        help_reverse(call_next);
        call_next->next = current;
        return current;
}

struct node * reverse(struct node * head)
{
        struct node * new_head = endof(head);
        help_reverse(head);
        head->next = NULL;
        return new_head;
}

void destroy(struct node * head)
{
        if(!head)
                return;
        destroy(head->next);
        free(head);
}

struct node * copy(struct node * head)
{
        if(!head)
                return head;
        struct node * new = new_node(head->data);
        new->next = copy(head->next);
        return new;
}

struct node * create_random_list(size_t len)
{
        struct node * head = NULL;
        while(len--)
        {
                head = insert(head, 0, rand());
        }
        return head;
}

int equal(struct node * node1, struct node * node2)
{
        if(!node1 && !node2)
                return 0;
        if(!node1 || !node2)
                return -1;
        return equal(node1->next, node2->next) + (node1->data - node2->data);
}

static int test_function()
{
        srand(time(NULL));
        // length test
        {
                int test_length = rand() % 1000;
                struct node * list = create_random_list(test_length);
                printf("\n length: %zu:%d\n", length(list), test_length);
                assert(length(list) == test_length);
                destroy(list);
        }

        // reverse test
        {
                struct node * list = create_random_list(10);
                printf("before reverse: ");
                print_list(list);
                printf("\nafter reverse: ");
                list = reverse(list);
                print_list(list);
                printf("\n");

                destroy(list);
        }
        // copy test
        {
                struct node * list = create_random_list(10);
                printf("Copying list: ");
                print_list(list);
                printf("\n");
                struct node *new_list = copy(list);
                printf("modifying old list\n");
                at_index(list, 2)->data = 101;
                printf("copied list: ");
                print_list(new_list);
                printf("\n");
                
                assert(equal(list, new_list) != 0);

                destroy(list);
                destroy(new_list);
        }
        return TEST_PASS;
}

REGISTER_TEST(linked_list, test_function, true)
