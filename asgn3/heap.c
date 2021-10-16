#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

// def  max_child(A: list , first: int , last: int):
// 2      left = 2 * first
// 3      right = left + 1
// 4      if right  <= last  and A[right - 1] > A[left - 1]:
// 5           return  right
// 6      return  left

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    if (right <= last && (cmp(stats, A[right - 1], A[left - 1]) == 1)) {
        return right;
    }
    return left;
}

// def  fix_heap(A: list , first: int , last: int):
// 9      found = False
// 10      mother = first
// 11      great = max_child(A, mother , last)
// 12
// 13      while  mother  <= last // 2 and  not  found:
// 14           if A[mother  - 1] < A[great  - 1]:
// 15                A[mother  - 1], A[great - 1] = A[great - 1], A[mother  - 1]
// 16                mother = great
// 17                great = max_child(A, mother , last)
// 18           else:
// 19                found = True

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    int found = 0;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);

    while ((mother <= last / 2) && found == 0) {
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = 1;
        }
    }
}

// def  build_heap(A: list , first: int , last: int):
// 2      for  father  in  range(last // 2, first  - 1,  -1):
// 3           fix_heap(A, father , last)

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = last / 2; father > (first - 1); father--) {
        fix_heap(stats, A, father, last);
    }
}

// 5  def  heap_sort(A: list):
// 6      first = 1
// 7      last = len(A)
// 8      build_heap(A, first , last)
// 9      for  leaf in  range(last , first ,  -1):
// 10           A[first - 1], A[leaf - 1] = A[leaf - 1], A[first - 1]
// 11           fix_heap(A, first , leaf - 1)

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
