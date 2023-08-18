#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "string_linked_list.h"

void string_linked_list_append(struct StringLinkedList* node, const char* string) {
    int length = strlen(string);
    while (1) {
        if (node->string == NULL) {
            node->string = malloc(sizeof(char) * (length + 1));
            memset(node->string, 0, sizeof(char) * (length + 1));
            strncpy(node->string, string, length);
            return;
        }
        if (node->next == NULL) {
            node->next = malloc(sizeof(struct StringLinkedList));
            memset(node->next, 0, sizeof(struct StringLinkedList));
        }
        node = node->next;
    }
}

bool string_linked_list_contains(struct StringLinkedList* node, const char* string) {
    if (string == NULL) {
        return false;
    }
    int length1 = strlen(string);
    while (node != NULL && node->string != NULL) {
        int length2 = strlen(node->string);
        if (length1 == length2 && (strcmp(string, node->string) == 0)) {
            return true;
        }
        node = node->next;
    }
    return false;
}

bool string_linked_list_mismatch(struct StringLinkedList* a, struct StringLinkedList* b) {
    struct StringLinkedList* a1 = a;
    while (a1 != NULL && a1->string != NULL) {
        if (!string_linked_list_contains(b, a1->string)) { return true; }
        a1 = a1->next;
    }

    struct StringLinkedList* b1 = b;
    while (b1 != NULL && b1->string != NULL) {
        if (!string_linked_list_contains(a, b1->string)) { return true; }
        b1 = b1->next;
    }

    return false;
}

int string_linked_list_count(struct StringLinkedList* node) {
    int count = 0;
    while (node != NULL) {
        if (node->string != NULL) {
            count++;
        }
        node = node->next;
    }
    return count;
}

void string_linked_list_free(struct StringLinkedList* node) {
    struct StringLinkedList* head = node;
    struct StringLinkedList* prevNode = head;
    while (node != NULL) {
        if (node->string != NULL) { free(node->string); }
        node = node->next;
        if (prevNode != NULL && prevNode != head) { free(prevNode); }
        prevNode = node;
    }

    if (prevNode != NULL && prevNode != head) { free(prevNode); }
}
