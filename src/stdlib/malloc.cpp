#include "../std.h"

unsigned long heap_start;
unsigned long heap_end;

const int CHUNK_SIZE = 32;
const int N_CHUNKS = 0x400000 / CHUNK_SIZE;
unsigned long actual_N_chunks;
unsigned long heap_map[N_CHUNKS / 32];
unsigned long last_free_chunk = 0;

void init_heap_map() {
    for (int i = 0; i < N_CHUNKS / CHUNK_SIZE; i++)
        heap_map[i] = 0;
}

typedef struct {
    unsigned long i;
    unsigned long j;
} heap_map_position;

heap_map_position position_from_num(int num) {
    heap_map_position pos;
    pos.i = num/32;
    pos.j = 1 << num%32;
    return pos;
}

void position_step(heap_map_position *pos, int num) {
    if (num == 0)
        return;
    pos->j <<= num % 32;
    pos->i += num / 32;

    if (pos->j == 0) {
        pos->j = 1;
        pos->i++;
        if (pos->i >= actual_N_chunks) {
            char message[] = "heap owerflow \0";
            log(message); 
        }
   }
}

void position_before_alligned(heap_map_position *pos, int allign) {
    int chunk = pos->i * 32 + log_two(pos->j);
    if ((chunk + 1)%allign == 0)
        return;
    int steps = allign - chunk%allign - 1;
    position_step(pos, steps);
}

void free_chunks(int first_chunk) {
    heap_map_position pos = position_from_num(first_chunk);
    if (last_free_chunk > pos.i)
        last_free_chunk = pos.i;
    while ((heap_map[pos.i] & pos.j) != 0) {
        heap_map[pos.i] = heap_map[pos.i] ^ pos.j;
        position_step(&pos, 1);
    }
}

int find_free_chunks(int num, int allign) {
    heap_map_position pos;
    pos.j = 1;
    pos.i = last_free_chunk;
    position_before_alligned(&pos, allign);
    int free_chunks = 0;
    while (free_chunks != (num + 2)) {
        if ((pos.j & heap_map[pos.i]) == 0) {
            free_chunks++;
        }
        else {
            free_chunks = 0;
            position_step(&pos, 1);
            position_before_alligned(&pos, allign);
            continue;
        }
        position_step(&pos, 1);
    }
    return pos.i*32 + log_two(pos.j) - num - 1;
}

void mark_chunks_used(int first_chunk, int num, bool alligned) {
    heap_map_position pos = position_from_num(first_chunk);
    for (int k = 0; k < num; k++) {
        heap_map[pos.i] |=  pos.j;
        position_step(&pos, 1);
    }
    if (!alligned)
        last_free_chunk = pos.i;
}

void * malloc(int size, int allign) {
    int chunk_size = (size - 1) / CHUNK_SIZE;
    int chunk_allign = (allign - 1) / CHUNK_SIZE + 1;
    int first_chunk = find_free_chunks(chunk_size, chunk_allign);
    mark_chunks_used(first_chunk, chunk_size, chunk_allign != 1);
    return (void *)(heap_start + CHUNK_SIZE * first_chunk);
}

void free(void * address) {
    if ((unsigned long)address < heap_start || (unsigned long)address > heap_end) {
        char msg[] = "tried to free a non malloc variable\0";
        log(msg);
        return;
    }
    int first_chunk = ((unsigned long)address - heap_start) / CHUNK_SIZE;
    free_chunks(first_chunk);
}

void init_heap(unsigned long heap_start_add, unsigned long heap_end_add) {
    heap_start = heap_start_add + 0x1000 - heap_start_add%0x1000;
    heap_end = heap_end_add - CHUNK_SIZE - heap_end_add%CHUNK_SIZE;
    unsigned long chunks_space = (heap_end_add - heap_start_add ) / CHUNK_SIZE;
    chunks_space > N_CHUNKS ? actual_N_chunks = N_CHUNKS : actual_N_chunks = chunks_space;
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
    log((unsigned long)(test_var != test_var3));
    void * test_var4 = malloc(test_size, 0x1000);
    log((unsigned long)test_var4%0x1000);

    free(test_var2);
    free(test_var3);
    free(test_var4);
}
