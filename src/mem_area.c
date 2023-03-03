#include "mem_area.h"
#include <stdlib.h>

struct mem_node null_node = {
        .ptr = NULL,
        .next = NULL
};

struct mem_area *mem_area_create() {
    struct mem_area *area = malloc(sizeof(struct mem_area));

    area->head = &null_node;
    return area;
}

struct mem_node *mem_area_append(struct mem_area *area, void *ptr) {
    struct mem_node *new_node = malloc(sizeof(struct mem_node));

    new_node->ptr = ptr;
    new_node->next = area->head;

    area->head = new_node;

    return new_node->ptr;
}

void *mem_area_malloc(struct mem_area *area, size_t size) {
    void *ptr = malloc(size);
    return mem_area_append(area, ptr);
}

void *mem_area_calloc(struct mem_area *area, size_t count, size_t size) {
    void *ptr = calloc(count, size);
    return mem_area_append(area, ptr);
}

void mem_area_free(struct mem_area *area) {
    struct mem_node *cur = area->head;
    while (cur != &null_node) {
        struct mem_node *next = cur->next;
        free(cur->ptr);
        free(cur);

        cur = next;
    }
    free(area);
}