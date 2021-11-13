#ifndef METRICS_H
#define METRICS_H

#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

using namespace std;

/* Estructura para guardar metricas de la cache */
class Metrics_data
{
    public: 
        float store_hit;
        float load_hit;
        float store_miss;
        float load_miss;
        int victim;
    
        Metrics_data(float load_miss, float store_miss, float load_hit, float hits_store, int victim);
        /* Imprime resultados de las funciones */
        void show_metrics(int size, int associativity, int block_size, int* contador, int* contador_opt , bool optimized);
};



#endif // METRICS_H