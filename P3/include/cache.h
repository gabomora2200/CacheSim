#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <bitset>
#include "metrics.h"

using namespace std;

// Estructura con flags de cache
struct flags {
  int contador_pred;
  bool valid;
  bool dirty;
  int tag;
  int rp_value; // Posible cambio
};

flags **cache_blocks(int ways, int idx_size);

// Estructura que contiene metadata de la cache
class Cache_metadata {
  private:
    int tag;
    int idx;
    int offset;

  public:
    Cache_metadata(int cache_size, int block_size, int asociativity);

    //Funcion para obtener tag de la direccion dada por el benchmark
    int get_tag(long address);

    //Funcion para obtener index de la direccion dada por el benchmark
    int get_index(long address);

    //Funcion para la politica de reemplazo LRU con optimizacion
    void lru_opt(int idx, int tag, int associativity, bool loadstore, flags* cache_blocks, int prediction[], metrics_data* metrics, int *contador);

    //Funcion para la politica de reemplazo LRU
    void lru(int idx, int tag, int associativity, bool loadstore, flags* cache_blocks, metrics_data* metrics, int* contador);
};

#endif // CACHE_H