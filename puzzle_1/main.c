#include<stdio.h>
#include<stdlib.h>

typedef struct list_item {
    int i1;
    int i2;
    struct list_item *next;
} list_item;

int main(int argc, char const *argv[])
{
    FILE *f = fopen("input.txt", "r");
    int c;
    list_item *list_head = NULL;
    list_item *list_tail = NULL;
    while (c != EOF) {
        list_item *l = (list_item*) malloc(sizeof(list_item));
        l->i1 = -1;
        l->i2 = -1;
        if (!list_head) {
            list_head = l;
            list_tail = l;
        } else {
            list_tail->next = l;
            list_tail = l;
        }
        while (c != '\n') {
            if (c >= 48 && c <= 57) {
                if (l->i1 < 0) l->i1 = c;
                else l->i2 = c;
            }
            c = fgetc(f);
        }
        c = fgetc(f);
    }
    fclose(f);
    return 0;
}
