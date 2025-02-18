#include "../std.h"

unsigned long heap_start;
unsigned long heap_end;

const int N_CHUNKS = 1024;
const int CHUNK_SIZE = 32;
unsigned long heap_map[N_CHUNKS];
unsigned long last_free_chunk = 0;

void init_heap_map() {
    for (int i = 0; i < N_CHUNKS / CHUNK_SIZE; i++)
        heap_map[i] = 0;
}

void free_chunks(int first_chunk) {
    unsigned long i = first_chunk/32;
    unsigned long j = 1 << first_chunk%32;
    last_free_chunk = i;
    while ((heap_map[i] & j) != 0) {
        heap_map[i] = heap_map[i] ^ j;
        j <<= 1;
        if (j == 0) {
            j = 1;
            i++;
        } 
    }
}

int get_free_chunks(int num) {
    unsigned long j = 1;
    unsigned long i = last_free_chunk;
    int free_chunks = 0;
    while (free_chunks != (num + 2)) {
        if ((j & heap_map[i]) == 0) {
            free_chunks++;
        }
        else {
            free_chunks = 0;
        }
        j <<= 1;
        if (j == 0) {
            j = 1;
            i++;
            if (i >= N_CHUNKS)
                return 0; //implement heap overflow
        }
    }
    int log_j = log_two(j);
    if (num + 1 > log_j) {
        i -= (num + 1 - log_j)/ 32 + 1;
    }
    j = 1 << (32 - (num + 1 - log_j)%32);
    int return_val = (i*32) + log_two(j);
    for (int k = 0; k < num; k++) {
        heap_map[i] |=  j;
        j <<= 1;
        if (j == 0) {
            j = 1;
            i++;
        } 
    }
    last_free_chunk = i;
    return return_val;
}

void * malloc(int size) {
    int first_chunk = get_free_chunks((size - 1) / CHUNK_SIZE + 1);
    return (void *)(heap_start + CHUNK_SIZE * first_chunk);
}

void free(void * address) {
    int first_chunk = ((unsigned long)address - heap_start) / CHUNK_SIZE;
    free_chunks(first_chunk);
}

void init_heap(unsigned long heap_start_add) {
    heap_start = heap_start_add;
    init_heap_map();
}

void malloc_test() {
    char msg[] = "Malloc test:\0";
    log(msg);
    int test_size = 20000;
    void * test_var = malloc(test_size);
    void * test_var2 = malloc(test_size);
    free(test_var);
    void * test_var3 = malloc(20);
    log((unsigned long)(test_var == test_var3));

    free(test_var2);
    free(test_var3);
}
