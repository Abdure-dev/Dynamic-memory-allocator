#include <stdlib.h>
#include <stdio.h>
#include "mm.h"


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

