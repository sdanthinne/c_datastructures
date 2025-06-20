#include "linked_list.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


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


struct node * ll_append(struct node * head, int data)
{
        struct node * new = new_node(data);
        if(head)
        {
                struct node * end = endof(head);
                end->next = new;
        }
        return head ? head : new;
}

struct node * ll_at_index(struct node * head, int index)
{
        if(!head)
                return NULL;
        if(!index)
                return head;
        return ll_at_index(head->next, index-1);
}

struct node * ll_insert(struct node * head, int index, int data)
{
        struct node * before = ll_at_index(head, index);
        struct node * new = new_node(data);
        if(before)
        {
                new->next = before->next;
                before->next = new;
        }
        return head ? head : new;
}

size_t ll_length(struct node * head)
{
        if(!head)
                return 0;
        return ll_length(head->next) + 1;
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

struct node * ll_reverse(struct node * head)
{
        struct node * new_head = endof(head);
        help_reverse(head);
        head->next = NULL;
        return new_head;
}

void ll_destroy(struct node * head)
{
        if(!head)
                return;
        ll_destroy(head->next);
        free(head);
}

struct node * ll_copy(struct node * head)
{
        if(!head)
                return head;
        struct node * new = new_node(head->data);
        new->next = ll_copy(head->next);
        return new;
}

static struct node * create_random_list(size_t len)
{
        struct node * head = NULL;
        while(len)
        {
                head = ll_insert(head, 0, rand());
                --len;
        }
        return head;
}

int ll_equal(struct node * node1, struct node * node2)
{
        if(!node1 && !node2)
                return 0;
        if(!node1 || !node2)
                return -1;
        return ll_equal(node1->next, node2->next) + (node1->data - node2->data);
}

struct node * ll_remove(struct node * head, int index)
{
        if(!head)
                return NULL;
        if(index == 0)
                return head->next;

        if(index == 1)
        {
                struct node * element_to_remove = head->next;
                head->next = head->next->next; //skip to next element
                free(element_to_remove);
        }

        ll_remove(head->next, index - 1);

        return head;
}

static int test_function(void)
{
        srand((unsigned int)time(NULL));
        // length test
        {
                size_t test_length = (size_t) rand() % 1000;
                struct node * list = create_random_list(test_length);
                printf("\n length: %zu:%zu\n", ll_length(list), test_length);
                assert(ll_length(list) == test_length);
                ll_destroy(list);
        }

        // reverse test
        {
                struct node * list = create_random_list(10);
                printf("before reverse: ");
                print_list(list);
                printf("\nafter reverse: ");
                list = ll_reverse(list);
                print_list(list);
                printf("\n");

                ll_destroy(list);
        }
        // copy test
        {
                struct node * list = create_random_list(10);
                printf("Copying list: ");
                print_list(list);
                printf("\n");
                struct node *new_list = ll_copy(list);
                printf("modifying old list\n");
                ll_at_index(list, 2)->data = 101;
                printf("copied list: ");
                print_list(new_list);
                printf("\n");
                
                assert(ll_equal(list, new_list) != 0);

                ll_destroy(list);
                ll_destroy(new_list);
        }
        return TEST_PASS;
}

REGISTER_TEST(linked_list, test_function, true)
