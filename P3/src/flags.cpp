#include "flags.h"
#include "cache.h"
#include "metrics.h"

Flags **Flags::cache_blocks(int asociativity, int index)
{
	// Cantidad de bloques en cache
	int set_amount = pow(2, index);

	// Crea matriz de sets
	Flags **cache = new Flags *[set_amount];

	// Crea ways para la cache
	for (int i = 0; i < set_amount; i++) cache[i] = new Flags[asociativity];

	// Se inicializa los valores de toda la cache
	for (int i = 0; i < set_amount; i++)
		for (int j = 0; j < asociativity; j++){
			cache[i][j].valid_bit = false;
			cache[i][j].dirty_bit = false;
			cache[i][j].tag = 0;
			cache[i][j].rp_value = j;
		}
	
	return cache;
}