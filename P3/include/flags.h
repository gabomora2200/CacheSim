#ifndef FLAGS_H
#define FLAGS_H

class Flags {
  public:
    int counter_pred;
    bool valid_bit;
    bool dirty_bit;
    int tag;
    int rp_value;

    Flags **cache_blocks(int ways, int idx_size);
};

#endif 