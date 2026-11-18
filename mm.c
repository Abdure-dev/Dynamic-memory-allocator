#include <stdlib.h>
#include <stdio.h>
#include "mm.h"
#include "memlib.h"

#define WSIZE 4 /*word and header/footer size(bytes)*/
#define DSIZE 8 /*Double word size(bytes)*/
#define CHUNKSIZE (1<<12) /*Extened heap by this amount(bytes)*/ 
#define ALIGNMENT 8 /*the alignment requirement*/
//combines size and an allocated bit into a single word
#define PACK(size,alloc) ((size) | (alloc))
//read a word from address p
//p will be a void * or char * and we need to read 4 bytes as an integer
#define GET(p) (*(unsigned int *)(p))
//write a word to address p
#define PUT(p,val) (*(unsigned int*)(p) = (val))
/*read the size dn allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p)&0x1)

/*Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/*given block ptr bp,compute address of the next and prevous block */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE((char *) (bp) - DSIZE)) 

//create a heap with an intial free block
static char *heap_listp;
static void *coalesce(void *bp);
static void *extend_heap(size_t words){
  size_t size;
  char *p;
  if((words%2) != 0){
    size = (words + 1)*WSIZE;
  }else{
    size = words*WSIZE;
    }
   p = mem_sbrk(size);
   if((long)p == -1)
     return NULL;
/*Intialize fre block heade/footer and teh epilogue header*/
 PUT(HDRP(p), PACK(size,0)); /*Free block header */
 PUT(FTRP(p), PACK(size,0));/*Free block footer */
 //next epilogue
 PUT(HDRP(NEXT_BLKP(p)), PACK(0,1));
 /*Coalesce if teh previous block was free */
  return coalesce(p);

}
int mm_init(void){
  //mem_sbrk: returns old_brk = the first of the 16 new bytes
 char *old_brk = mem_sbrk(4*WSIZE);
 if(old_brk == (void *) -1)
   return -1;
 //adding teh padding
 PUT(old_brk, 0);
 //adding teh prologue header
 PUT(old_brk + 1*WSIZE, PACK(DSIZE,1));
 //prologue footer
 PUT(old_brk + 2*WSIZE, PACK(DSIZE,1));
 PUT(old_brk + 3*WSIZE, PACK(0,1));

 heap_listp = old_brk + 2*WSIZE;
/*extend the empty heap with  a free block of CHUNKSIZE bytes */
 if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
   return -1;
 return 0;
  

}
