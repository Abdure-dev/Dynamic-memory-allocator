/* guards: protects it against being included twice in one translation unit.
   if mm.c includes memlib.h and also incldue soemthign else that includes it,
   we will get duplicate declarations

 */
#ifndef MEMLIB_H // undefiend->enter,define it, read the file
#define MEMLIB_H // defined -> skip to #endif

#include <stddef.h>
// intialize the memory: 
//it acquires the heap region(size fixed by compile-time constatnt)
// must be called before any other memlib function
// Does not return on failure, prints and exists
// calling it twice leaks the previous region
//NB: this is the on time setup that brings the simulated heap into existence
//before it runs there is not heap, no bytes, no pointers, nothing for
// mm_malloc to crave up.
void mem_init(void);
//the allocator calls it everytime it runs out of space
// it return the value of the break before the increment
// on failure it doesn't return NULL;it returns (void *) -1
//there are two failure condtions: incr is negative(shrinking is rejected) and
// request would push the break past the end of the max region
// the break advanced by incr, so mem_heapsize() and mem_heap_hi() change
// the returned memmory is unintilized, not zeored. unlike real sbrk, which 
// which gives zero pages.
void *mem_sbrk(int incr);
//free teh region acquired in mem_init
// calling anythign else after it is undefiend, since the pointers now dangle

void mem_deinit(void);
//sets mem_brk back to mem_heap, givign us a fresh empty heap without 
//reacquiring the region
void mem_reset_brk(void);
//return the first bye of the heap.
//it exists so our heap checker can verify every pointer it encounter lies
//within the heap
// it is set once and never moves
void *mem_heap_lo(void);
//It returns the last valid bye of the heap, mem_brk -1
void *mem_heap_hi(void);
//return how many byte fo heap currently exist:
//right after mem_init it returns 0
//every succesful mem_sbrk increases it; 
// mem_reset_brk zeroes it
size_t mem_heapsize(void);
//return sthe system page size in bytes
// it is a system property, not memlib proepty, constant for the life of the process
// intened for the allcoator to size its heap-extension requests. 
size_t mem_pagesize(void);

#endif 
