#ifndef MM_H
#define MM_H
#include <stddef.h>

//it builds the intial heap strucuter
// it gives us raw region of bytes
//it has to construct the padding word, prologue header, prologue footer,and
//Epilogue header
//then it sets heap_listp to point at the prologue 
// make extend_heap to create an intial free block

int mm_init(void);
//take a byte and return a pointer to a block of at least that many usable bytes
void *mm_malloc(size_t size);
//returns the block pointed to by ptr to the free pool
// ptr must be a value previously returned by mm_malloc and not yet free
// after the call ptr is dangling
void mm_free(void *ptr);
//resizes teh block at ptr to size bytes
// on failure return NULL and the original block is unchanged and still valid.
void *mmn_realloc(void *ptr, size_t size);
//debugging tool.
//reports whcih block and which invariant , with enought detail to locate the 
//problem, then either aborts or return
void mm_checkheap(int lineno);






#endif
