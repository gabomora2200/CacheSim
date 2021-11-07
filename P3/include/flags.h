#ifndef FLAGS_H
#define FLAGS_H

class Flags {
  public:
    int contador_pred;
    bool valid;
    bool dirty;
    int tag;
    int rp_value;

    Flags **cache_blocks(int ways, int idx_size);
};


#endif 