#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <bitset>
#include "benchmark.h"
#include "parametros.h"

using namespace std;

class Cache_metadata {
  private:
    int tag;
    int index;
    int offset;

  public:
    Cache_metadata(int cache_size, int block_size, int asociativity);

    //Funcion para obtener tag de la direccion dada por el benchmark
    int get_tag(long address);

    //Funcion para obtener index de la direccion dada por el benchmark
    int get_index(long address);

    //Funcion para la politica de reemplazo LRU con optimizacion
    void lru_opt(int index, int tag, int associativity, bool load_store, Parametros* cache_blocks, int prediction[], Benchmark* metrics, int *counter);

    //Funcion para la politica de reemplazo LRU
    void lru(int index, int tag, int associativity, bool load_store, Parametros* cache_blocks, Benchmark* metrics, int* counter);
};

#endif // CACHE_H