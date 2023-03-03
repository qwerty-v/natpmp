#ifndef NATPMP_MEM_AREA_H
#define NATPMP_MEM_AREA_H

#include <stdint.h>
#include <stddef.h>

struct mem_node {
    void *ptr;
    struct mem_node *next;
};

struct mem_area {
    struct mem_node *head;
};

struct mem_area *mem_area_create();

struct mem_node *mem_area_append(struct mem_area *area, void *ptr);

void *mem_area_malloc(struct mem_area *area, size_t size);

void *mem_area_calloc(struct mem_area *area, size_t count, size_t size);

void mem_area_free(struct mem_area *area);

#endif //NATPMP_MEM_AREA_H
