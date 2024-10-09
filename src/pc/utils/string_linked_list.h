#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H

struct StringLinkedList {
    char* string;
    struct StringLinkedList* next;
};

void string_linked_list_append(struct StringLinkedList* node, const char* string);
bool string_linked_list_contains(struct StringLinkedList* node, const char* string);
bool string_linked_list_mismatch(struct StringLinkedList* a, struct StringLinkedList* b);
int string_linked_list_count(struct StringLinkedList* node);
void string_linked_list_free(struct StringLinkedList* node);

#endif