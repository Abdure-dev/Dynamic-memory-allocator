/*notes on bracket type:
  <> seaches system include paths only: they are for system headers
  "" searchs your directory first: for our own headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memlib.h"

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
    mem_brk = mem_heap;
    mem_max_addr = mem_heap + MAX_HEAP;

}
