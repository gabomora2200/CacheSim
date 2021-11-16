#ifndef PARAMETROS_H
#define PARAMETROS_H

class Parametros {
  public:
    int counter_pred;
    bool valid_bit;
    bool dirty_bit;
    int tag;
    int rp_value;

    Parametros **cache_blocks(int ways, int index_size);
};

#endif 