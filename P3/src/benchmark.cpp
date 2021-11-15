#include <benchmark.h>

Benchmark::Benchmark(float load_miss, float store_miss, float load_hit, float hits_store, int victim){
  this->load_miss = load_miss;
  this->store_miss = store_miss;
  this->load_hit = load_hit;
  this->store_hit = hits_store;
  this->victim = victim;
}


void Benchmark::show_metrics(int size, int associativity, int block_size, int* contador, int* contador_opt, bool optimized){
  
  float totHits = load_hit + store_hit;
  float totMiss = load_miss + store_miss;
  float ratioMissHit = 100 - ((float(*contador_opt))/(float(*contador)))*100;

  if(optimized){
    // si la cache esta optimizada  imprime esto
    cout << "\nDatos de cache optimizada: " << endl;

  }
  else{
    // si la cache NO esta optimizada imprime esto
    cout << "\n=======================================================================\n" << endl;
    cout << "Datos de cache sin optimizacion: " << endl;

  }

  //Impresion de parametros de la cache
  cout << "\nParametros Fisicos Cache: \n"<< endl;
  cout << "Tamaño del cache(KB):       "  << size << endl;
  cout << "Cantidad de ways:           "  << associativity << endl;
  cout << "Tamaño de bloque(B):        "  << block_size << endl;
  cout << "\n"                            << endl;
  cout << "Resultados obtenidos:\n"       << endl;

  // Imprimir valores enteros, sin notacion cientifica
  cout << fixed;
  cout << setprecision(0);
  cout << "Cantidad total de Victimizaciones:      "<< victim << endl;
  cout << "Cantidad total misses en lectura:       "<< load_miss << endl;
  cout << "Cantidad total misses en escritura:     "<< store_miss << endl;
  cout << "Cantidad total misses:                  "<< totMiss << endl;
  cout << "\n"                                      << endl;
  cout << "Cantidad total hits en lectura:         "<< load_hit << endl;
  cout << "Cantidad total hits en escritura:       "<< store_hit << endl;
  cout << "Cantidad total hits:                    "<< totHits << endl;
  cout << "\n"                                      << endl;

  //Resultados finales 
  cout << setprecision(2);
  cout << "\nRelacion final:"           << endl;
  cout << "Hit rate:                   "<< (totHits/(totHits + totMiss))*100.0 << "%" << endl;
  cout << "Miss rate:                  "<< (totMiss/(totHits + totMiss))*100.0 << "%" << endl;
  cout << "\n"                          << endl;

  
  if(optimized){
    //Imprime la cantidad total de predicciones con optimizacion
    cout << "Cantidad de predicciones correctas mediante la optimización: "<< *contador_opt << endl;

  }
  else{
    
    cout << "\nRelacion de hits acertados optimizacion: " << (*contador_opt/totHits)*100 << "%" <<endl;
    cout << "\n"                                              << endl;

  }

  return;
}