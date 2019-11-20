#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include "cachelab.h"

typedef struct {
  bool valid;
  int tag;
  int time;
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
int evicts = 0;

char* parseInput(int, char **);
void cacheInit();
void simulate(int, int, int);
void timeUpdate(line_t*, set_t*);
line_t* findEmptyLine(set_t*);
line_t* findEvictLine(set_t*);
bool checkHit(set_t *, int);
void clearAll();

int main(int argc, char *argv[]) {
  FILE *trace; char cmd; int addr; int tag; int set_index;

  char* file_name = parseInput(argc, argv);
  trace = fopen(file_name, "r");
  
  // cache initialize
  cacheInit();

  while (fscanf(trace, " %c %x%*c%*d", &cmd, &addr) != EOF) {
    tag = 0xffffffff & (addr >> (CACHE_SIZE->s + CACHE_SIZE->b));
    set_index = (0x7fffffff >> (31 - CACHE_SIZE->s)) & (addr >> CACHE_SIZE->b);
    // printf("cmd %c %d\n", cmd, addr);
    switch(cmd) {
      case 'I':
        break;
      case 'L':
        simulate(addr, tag, set_index);
        break;
      case 'S':
        simulate(addr, tag, set_index);
        break;
      case 'M':
        simulate(addr, tag, set_index);
        simulate(addr, tag, set_index);	
        break;
      default:
        break;
    }
  }
  printSummary(hits, misses, evicts);
  fclose(trace);
  clearAll();
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
  int i;
  cache.sets = malloc(sizeof(set_t) * CACHE_SIZE->S);
  for (i = 0; i < CACHE_SIZE->S; i++) {
    cache.sets[i].lines = malloc(sizeof(line_t) * CACHE_SIZE->E);
  }
}

void timeUpdate(line_t *line, set_t *set) {
  int i;
  line_t *temp_line;
  for (i = 0; i < CACHE_SIZE->E; i++) {
    temp_line = &set->lines[i];
    if (!temp_line->valid) continue;
    if (temp_line->time > line->time) {
      temp_line->time--;
    }
  }
  line->time = CACHE_SIZE->E - 1;
}

void simulate(int addr, int tag, int set_index) {
  bool check = false;
  line_t *temp_line = NULL;
  set_t *set = &cache.sets[set_index];

  check = checkHit(set, tag);
  if (check) { // hit
    hits++;
  } else { // miss
    misses++;
    temp_line = findEmptyLine(set);
    if (temp_line) {
      temp_line->valid = true;
      temp_line->tag = tag;
      timeUpdate(temp_line, set);
    } else {  // evict
        evicts++;
        temp_line = NULL;
        temp_line = findEvictLine(set);
        temp_line->valid = true;
        temp_line->tag = tag;
        timeUpdate(temp_line, set);
    }
  }
}

bool checkHit(set_t *set, int tag) {
  bool ret = false;
  line_t *temp_line;
  int i = 0;
  for (i = 0; i < CACHE_SIZE->E; i++) {
    temp_line = &set->lines[i];
    if (temp_line->valid) {
      if (temp_line->tag == tag) {
        ret = true;
        timeUpdate(temp_line, set);
        break;
      }
    }
  }
  return ret;
}

line_t* findEmptyLine(set_t *set) {
  int i;
  line_t* ret = NULL;
  for (i = 0; i < CACHE_SIZE->E; i++) {
    line_t* temp_line = &set->lines[i];
    if (!temp_line->valid) {
      ret = temp_line;
      break;
    }
  }
  return ret;
}

line_t* findEvictLine(set_t *set) {
  int i; 
  int ret_time = -1;
  line_t *ret = NULL;
  for (i = 0; i < CACHE_SIZE->E; i++) {
    line_t* temp_line = &set->lines[i];
    if (!temp_line->valid) continue;
    if (ret_time == -1) {
      ret = temp_line;
      ret_time = ret->time;
    } else {
      if (ret_time > temp_line->time) {
        ret = temp_line;
        ret_time = ret->time;
      }
    }
  }
  return ret;
}

void clearAll() {
  int i;
  for (i = 0; i < CACHE_SIZE->S; i++) {
    free(cache.sets[i].lines);
  }
  free(cache.sets);
}