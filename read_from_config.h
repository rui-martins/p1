#ifndef READ_FROM_CONFIG_H
#define READ_FROM_CONFIG_H
#define MAXSTR 500

/**
 * Structure defining configuration variables.
 *
 * */
typedef struct {
    unsigned int xdim;
    unsigned int ydim;
    unsigned int nzombies;
    unsigned int nhumans;
    unsigned int nzplayers;
    unsigned int nhplayers;
    unsigned int turns;
} CONFIG;

/**
 * Read from config file.
 *
 * @param argc Number of arguments passed through command line.
 * @param argv Array of strings that contain the arguments passed.
 * @return A new `CONFIG` object.
 * */
CONFIG read_config(int argc, char *argv[]);

/**
 * Set config values
 *
 * @param config Pointer to `CONFIG` object.
 * @param key Constant string.
 * @param val Integer value.
 * */
void set_config_val(CONFIG *config, const char *key, int val);

#endif
