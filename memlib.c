/*notes on bracket type:
  <> seaches system include paths only: they are for system headers
  "" searchs your directory first: for our own headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memlib.h"
#include <errno.h>
#include <assert.h>
#include <stdint.h>

//1 megabyte is 1<<20: 2^20
//but we want 20MB so multiply by 20
#define MAX_HEAP (20*(1<<20))
//static at file scope - internal linkage
static char *mem_heap;//only memlib.c can see this
static char *mem_brk;//
static char *mem_max_addr;


void mem_init(void){
    mem_heap = malloc(MAX_HEAP);
    if(mem_heap == NULL){
      fprintf(stderr,"malloc failed\n");
      exit(1);
    }
    assert(((uintptr_t)mem_heap&0x7)==0);
    mem_brk = mem_heap;
    mem_max_addr = mem_heap + MAX_HEAP;

}
//it returns a void pointer
void *mem_sbrk(int incr){
  char *old_brk = mem_brk;
  if(incr < 0 || mem_brk + incr> mem_max_addr){
   errno = ENOMEM; 
    return (void *) -1;
}
  mem_brk += incr;
  return (void *) old_brk;

}

void mem_deinit(void){
  free(mem_heap);
  mem_heap = NULL;
  mem_brk = NULL;
  mem_max_addr = NULL;

}

void mem_reset_brk(void){
  mem_brk = mem_heap;

}
void *mem_heap_lo(void){
  return (void *)mem_heap;
}

void *mem_heap_hi(void){
    return (void *) mem_brk -1;
}

size_t mem_heapsize(void){
  return (size_t)(mem_brk - mem_heap);

}
size_t mem_pagesize(void){
  return (size_t)getpagesize();

}



