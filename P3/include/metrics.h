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
        float miss_load;
        float miss_store;
        float hit_load;
        float hit_store;
        int vict;
    
        Metrics_data(float miss_load, float miss_store, float hit_load, float hits_store, int vict);
        /* Imprime resultados de las funciones */
        void show_metrics(int size, int associativity, int block_size, int* contador, int* contador_opt , bool optimized);
};



#endif // METRICS_H