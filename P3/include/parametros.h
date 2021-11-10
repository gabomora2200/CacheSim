#ifndef PARAMETROS_H
#define PARAMETROS_H

class Parametros {
  public:
    int contador_pred;
    bool valid;
    bool dirty;
    int tag;
    int rp_value;

    Parametros **cache_blocks(int ways, int idx_size);
};


#endif 