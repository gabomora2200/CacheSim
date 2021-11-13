#include "cache.h"
#include "metrics.h"
#include "flags.h"

// Funcion para obtener metadatos de la cache
Cache_metadata::Cache_metadata(int cache_size, int block_size, int asociativity){
	// Obteniendo metadatos de cache
	this->offset = log2(block_size);
	this->idx = log2(cache_size * 1024 / (block_size * asociativity));
	this->tag = 32 - idx - offset;
}

// Funcion para obtener el tag de la direccion dada por el benchmark
int Cache_metadata::get_tag(long address){
	bitset<32> tag_s(address); 
	tag_s >>= idx + offset;
	int tag = (int)(tag_s.to_ulong());
	return tag;
}

// Funcion para obtener el index de la direccion dada por el benchmark
int Cache_metadata::get_index(long address){
	bitset<32> index_s(address);
	index_s <<= tag;
	index_s >>= tag + offset;
	int index = (int)(index_s.to_ulong());
	return index;
}

void Cache_metadata::lru_opt(int index, int tag, int associativity, bool loadstore, Flags *cache_blocks, int pred_array[], Metrics_data* metrics, int *contador){
	bool hit_miss = false;
	// Revisar todas las vias del bloque de cache
	int greatest = 0, greatest_contador = 0;
	int valorInicial = pred_array[index];
	int i = valorInicial;
	int contador_valInit = 0;

	int first_case = 0;

	while( 1 )
	{	
		if(i == associativity) {
			i = 0;
		}
		if(i == valorInicial) {
			contador_valInit++;
			if(contador_valInit == 2) {
				break;
			}
		}
		first_case = first_case + 1;
		// Si el tag coincide con el de la direccion y valid es 1, se da un HIT
		if (cache_blocks[i].tag == tag && cache_blocks[i].valid) {
			
			// Hubo hit
			hit_miss = true;

			// No hay victimizacion de bloque
			metrics->victim = metrics->victim;

			// Si es load, se da un HIT de lectura
			if (!loadstore) {
				cache_blocks[i].contador_pred++;
				metrics->load_hit = (metrics->load_hit) + 1;//result->miss_hit = LOAD_HIT;
			}
			// Por el contrario, se da HIT de escritura
			else{
				metrics->store_hit = (metrics->store_hit) + 1;
				// El dirty se pasa a TRUE debido a que se escribe en cache un nuevo dato
				cache_blocks[i].dirty = true;
				cache_blocks[i].contador_pred++;
			}

			// Se actualiza criterio del LRU
			for (int j = 0; j < associativity; j++){
				if (cache_blocks[j].rp_value > cache_blocks[i].rp_value){
					cache_blocks[j].rp_value--;
				}
			}

			if (pred_array[index] <= cache_blocks[i].contador_pred){
				pred_array[index] = i;
			}

			// El bloque que obtuvo HIT ahora es el MRU
			cache_blocks[i].rp_value = associativity - 1;
			if(first_case == 1) *contador = *contador + 1;
			
			break;
		}
		i++;
	}

	// Hubo miss
	if (!hit_miss){
		// Se busca el valor LRU
		for (int i = 0; i < associativity; i++){
			if (cache_blocks[i].rp_value == 0){
				// La victimizacion del bloque depende del bit dirty del way LRU, si esta existe se lleva el bloque de cache a memoria
				if(cache_blocks[i].dirty){	
					metrics->victim = (metrics->victim) + 1;
				}
				else{
					metrics->victim = metrics->victim;
				}
				//result->dirty_eviction = cache_blocks[i].dirty;
				//result->evicted_address = cache_blocks[i].tag;

				// Si hubo un load, se da MISS de lectura y dirty bit es cero
				if (!loadstore){
					cache_blocks[i].dirty = false;
					metrics->load_miss = (metrics->load_miss) + 1;
					cache_blocks[i].contador_pred = 0;
				}

				// Si hubo store, se da un MISS de escritura y dirty bit es uno
				else{
					cache_blocks[i].dirty = true;
					//result->miss_hit = STORE_MISS;
					metrics->store_miss = (metrics->store_miss) + 1;
					cache_blocks[i].contador_pred = 0;
				}

				// Se actualiza criterio del LRU
				for (int j = 0; j < associativity; j++)
				{
					if (cache_blocks[j].rp_value > cache_blocks[i].rp_value)
					{
						cache_blocks[j].rp_value--;
					}
				}

				// El bloque que obtuvo MISS ahora es el MRU
				cache_blocks[i].rp_value = associativity - 1;

				// Si hubo miss se actualiza metadata del cache en el way respectivo
				cache_blocks[i].tag = tag;
				cache_blocks[i].valid = true;
				break;
			}
		}
	}
}

void Cache_metadata::lru(int index, int tag, int associativity, bool loadstore, Flags *cache_blocks, Metrics_data *metrics, int* contador){
	bool hit_miss = false;
	// Revisar todas las vias del bloque de cache
	for (int i = 0; i < associativity; i++){
		// Si el tag coincide con el de la direccion y valid es 1, se da un HIT
		if (cache_blocks[i].tag == tag && cache_blocks[i].valid) {
			
			// Hubo hit
			hit_miss = true;

			// No hay victimizacion de bloque
			metrics->victim = metrics->victim;

			// Si es load, se da un HIT de lectura
			if (!loadstore) metrics->load_hit = (metrics->load_hit) + 1;//result->miss_hit = LOAD_HIT;
			
			// Por el contrario, se da HIT de escritura
			else{
				metrics->store_hit = (metrics->store_hit) + 1;
				// El dirty se pasa a TRUE debido a que se escribe en cache un nuevo dato
				cache_blocks[i].dirty = true;
			}

			// Se actualiza criterio del LRU
			for (int j = 0; j < associativity; j++){
				if (cache_blocks[j].rp_value > cache_blocks[i].rp_value){
					cache_blocks[j].rp_value--;
				}
			}

			// El bloque que obtuvo HIT ahora es el MRU
			cache_blocks[i].rp_value = associativity - 1;
			break;
		}
	}

	// Hubo miss
	if (!hit_miss){
		// Se busca el valor LRU
		for (int i = 0; i < associativity; i++){
			if (cache_blocks[i].rp_value == 0){
				// La victimizacion del bloque depende del bit dirty del way LRU, si esta existe se lleva el bloque de cache a memoria
				if(cache_blocks[i].dirty){	
					metrics->victim = (metrics->victim) + 1;
				}
				else{
					metrics->victim = metrics->victim;
				}

				// Si hubo un load, se da MISS de lectura y dirty bit es cero
				if (!loadstore){
					cache_blocks[i].dirty = false;
					metrics->load_miss = (metrics->load_miss) + 1;
				}

				// Si hubo store, se da un MISS de escritura y dirty bit es uno
				else{
					cache_blocks[i].dirty = true;
					metrics->store_miss = (metrics->store_miss) + 1;
				}

				// Se actualiza criterio del LRU
				for (int j = 0; j < associativity; j++)
				{
					if (cache_blocks[j].rp_value > cache_blocks[i].rp_value)
					{
						cache_blocks[j].rp_value--;
					}
				}

				// El bloque que obtuvo MISS ahora es el MRU
				cache_blocks[i].rp_value = associativity - 1;

				// Si hubo miss se actualiza metadata del cache en el way respectivo
				cache_blocks[i].tag = tag;
				cache_blocks[i].valid = true;
				break;
			}
		}
	}
}