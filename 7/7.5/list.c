#include <stdlib.h>

void free_linked_list(void *node, int nextoffsetbytes) {
  if(node == NULL)
    return;
  free_linked_list(*(void **)((char *)node + nextoffsetbytes), nextoffsetbytes);
  free(node);
}
