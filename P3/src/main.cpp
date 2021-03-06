#include <cache.h>
#include <benchmark.h>
#include <parametros.h>

int main(int argc, char *argv []) {

  // Parametros de cache
  int cache_size, block_size, asociativity;
  
  // Se obtienen parámetros desde comando 
  if( argv[1] != NULL ) {
    cache_size = atoi(argv[1]);
  }
  if( argv[2] != NULL ) {
    block_size = atoi(argv[2]);
  }
  if( argv[3] != NULL ) {
    asociativity = atoi(argv[3]);
  }

  // Se crean instancias de ambas caches
  Cache_metadata metadata(cache_size, block_size, asociativity);
  Cache_metadata metadata_opt(cache_size, block_size, asociativity);

  int index_size = log2(cache_size * 1024 / (block_size * asociativity));

  Parametros inst1;
  Parametros inst2;

  Parametros **cache = inst1.cache_blocks(asociativity, index_size);
  Parametros **cache_opt = inst2.cache_blocks(asociativity, index_size);
  
  int set_amount = pow(2, index_size);
  int pred_array_opt[set_amount];

  for(int i = 0; i < set_amount; i++) pred_array_opt[i] = 0;

  // Se crea instancia para guardas las metricas y se inicializan los valores 
  Benchmark metrics(0.0, 0.0, 0.0, 0.0,0);

  Benchmark metrics_opt(0.0, 0.0, 0.0, 0.0,0);
  
  // Se crean las variables de interes
  int load_store, tag, index;
  
  // Lineas de lectura y direccion
  char linea[200];
  char direccion_linea[10]; 
  long direccion;      

  // Contadores para ambas cache, con y sin optimizacion
  int counter = 0;
  int counter_opt = 0;

  while(fgets(linea, 50, stdin)!= NULL){
    // Si linea es valida se revisa y se obtienen los datos
    if(linea == NULL) break;
    else{
      sscanf(linea, "%*s %d %s", &load_store, direccion_linea);
      // String a long integer
      direccion = strtol(direccion_linea, NULL, 16); 
    }
  
  // Se obtiene para cada direccion el tag e index respectivo 
  tag = metadata.get_tag(direccion);
  index = metadata.get_index(direccion);

  // Se aplica la política LRU

  // Cache optimizada
  metadata_opt.lru_opt(index, tag, asociativity, load_store, cache_opt[index], pred_array_opt, &metrics_opt, &counter_opt);
  
  // Cache sin optimizacion
  metadata.lru(index, tag, asociativity, load_store, cache[index], &metrics, &counter);

  }

  // Se imprimen metricas de cache
  metrics_opt.show_metrics(cache_size, asociativity, block_size, &counter, &counter_opt, true);
  metrics.show_metrics(cache_size, asociativity, block_size,  &counter, &counter_opt, false);


  return 0;
}