#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "cachelab.h"
typedef struct {
  bool valid;
  int tag;
  int age;
} line_t;

typedef struct {
  line_t *lines;
} set_t;

typedef struct {
  set_t *sets;
} cache_t;

typedef struct {
    int s;     // Number of Sets
    int S;     // 2 ** s
    int E;     // Number of lines
    int b;     // block bits
    int B;     // 2 ** b
    int size;  // S * E * B
} cache_size_t;
cache_size_t *CACHE_SIZE;
cache_t cache = {};
int hits = 0;
int misses = 0;
int evictions = 0;

char* parseInput(int, char **);
void cacheInit();
void simulate(int);
void update(set_t *, size_t);

int main(int argc, char *argv[]) {
  FILE *trace; char cmd; int addr;

  char* file_name = parseInput(argc, argv);
  trace = fopen(file_name, "r");
  
  // check input command
  if (!CACHE_SIZE->s || !CACHE_SIZE->E || !CACHE_SIZE->b || !trace) return 1;

  // cache initialize
  cacheInit();

  while (fscanf(trace, " %c %x%*c%*d", &cmd, &addr) != EOF) {
    // printf("cmd %c %d\n", cmd, addr);
    switch(cmd) {
      case 'I':
        break;
      case 'L':
        simulate(addr);
        break;
      case 'S':
        simulate(addr);
        break;
      case 'M':
        simulate(addr);
        simulate(addr);	
        break;
      default:
        break;
    }
  }
  printSummary(hits, misses, evictions);
  fclose(trace);
  for (size_t i = 0; i < CACHE_SIZE->S; ++i) { free(cache.sets[i].lines); }
  free(cache.sets);
  return 0;
}

char* parseInput(int argc, char *argv[]) {
  CACHE_SIZE = malloc(sizeof(cache_size_t));
  char opt;
  char* file_name;
  while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
    switch (opt) {
      case 's':
        CACHE_SIZE->s = atoi(optarg); 
        CACHE_SIZE->S = 1 << CACHE_SIZE->s;
        break;
      case 'E':
        CACHE_SIZE->E = atoi(optarg);
        break;
      case 'b':
        CACHE_SIZE->b = atoi(optarg);
        CACHE_SIZE->B = 1 << CACHE_SIZE->b;
        break;
      case 't': 
        file_name = optarg;
        break;
      default:
        break;
    }                                                                                                                                                            
  }
  CACHE_SIZE->size = CACHE_SIZE->S * CACHE_SIZE->B * CACHE_SIZE->E;
  return file_name;
}

void cacheInit() {
  cache.sets = malloc(sizeof(set_t) * CACHE_SIZE->S);
  for (int i = 0; i < CACHE_SIZE->S; i++) {
    cache.sets[i].lines = malloc(sizeof(line_t) * CACHE_SIZE->E);
  }
}

void simulate(int addr) {
  int set_index = (0x7fffffff >> (31 - CACHE_SIZE->s)) & (addr >> CACHE_SIZE->b);
  int tag = 0xffffffff & (addr >> (CACHE_SIZE->s + CACHE_SIZE->b));

  set_t *set = &cache.sets[set_index];

  // Look up for cache hit
  for (int i = 0; i < CACHE_SIZE->E; i++) {
    line_t* line = &set->lines[i];

    // Check if the cache line is valid
    if (!line->valid) { continue; }
    // Compare tag bits
    if (line->tag != tag) { continue; }

    // Cache hit!
    ++hits;
    update(set, i);
    return;
  }

  // Cache miss!
  ++misses;

  // Look up for empty cache line
  for (size_t i = 0; i < CACHE_SIZE->E; ++i) {
    line_t* line = &set->lines[i];

    if (line->valid) { continue; }

    line->valid = true;
    line->tag = tag;
    update(set, i);
    return;
  }

  // No empty cache line, eviction!
  ++evictions;

  // Look up for least recently used cache line
  for (size_t i = 0; i < CACHE_SIZE->E; ++i) {
    line_t* line = &set->lines[i];

    if (line->age) { continue; }

    line->valid = true;
    line->tag = tag;
    update(set, i);
    return;
  }
}

void update(set_t *set, size_t line_no) {
  line_t *line = &set->lines[line_no];

  for (size_t i = 0; i < CACHE_SIZE->E; ++i) {
    line_t *it = &set->lines[i];
    if (!it->valid) { continue; }
    if (it->age <= line->age) { continue; }

    --it->age;
  }

  line->age = CACHE_SIZE->E - 1;
}