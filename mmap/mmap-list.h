#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

struct list {
    int val;
    struct list *next;
}; // 16 bytes == sizeof(struct list)

static struct list *list_bot;
static struct list *list_top;
static long list_siz;

int list_init(long len) {
    list_top = (struct list *)mmap(NULL,
                                   len * sizeof(struct list),
                                   PROT_READ | PROT_WRITE,
                                   MAP_PRIVATE | MAP_ANONYMOUS,
                                   -1, 0);
    if (list_top == MAP_FAILED)
        return -1;
    
    list_bot = list_top;
    list_siz = len;
    printf("list_init: top=%p, len=%ld\n", list_top, len);
    return 0;
}

struct list *list_alloc(void) {
    long siz = list_top - list_bot;
    if (siz >= list_siz) {
        errno = ENOMEM;
        return NULL;
    }
    
    list_top->next = NULL;
    printf("allocated %p (length: %ld)\n", list_top, siz + 1);
    return list_top++;
}

struct list *list_free(void) {
    /* 구현하지 않음 - left as an exercise */
    return NULL;
}

struct list *list_add(struct list *l, int val) {
    struct list *elt;
    if ((elt = list_alloc()) == NULL)
        return NULL;

    elt->val = val;
    elt->next = l;
    return elt;
}

void list_visit(const char *label, struct list *l) {
    printf("[%s] visit list: ", label);
    while (l != NULL) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("\n");
}
