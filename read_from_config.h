#ifndef READ_FROM_CONFIG_H
#define READ_FROM_CONFIG_H
#define MAXSTR 500

typedef struct {
    unsigned int xdim;
    unsigned int ydim;
    unsigned int nzombies;
    unsigned int nhumans;
    unsigned int nzplayers;
    unsigned int nhplayers;
    unsigned int turns;
} CONFIG;

CONFIG read_config(int argc, char *argv[]);

void set_config_val(CONFIG *config, const char *key, int val);

#endif
