#include "read_from_config.h"
#include "example.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CONFIG read_config(int argc, char *argv[]) {

    const char *delim = "=\n";
    CONFIG config;
    char str[MAXSTR];
    FILE *fp = NULL;
    char *filename = argv[1];
    char *token;

    if (argc > 2) {
        fprintf(stderr, "Too many arguments.");
        fprintf(stderr, "\nUsage mode: ./program_name config.ini");
        exit(1);
    }
    if (argc == 1) {
        fprintf(stderr, "Too few arguments.");
        fprintf(stderr, "\nUsage mode: ./program_name config.ini");
        exit(1);
    }
    else {
        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Unable to open configuration file.");
            fprintf(stderr, "\nUsage mode: ./program_name config.ini");
            exit(1);
        }
    }
    while (fgets(str, MAXSTR, fp) != NULL) {
        if (strchr(str, '=')) {
            char varname[100];
            int value;
            token = strtok(str, delim);
            strcpy(varname, token);
            token = strtok(NULL, delim);
            value = atoi(token);
            set_config_val(&config, varname, value);
        }
    }
    fclose(fp);
    return config;
}

void set_config_val(CONFIG *config, const char *key, int val)
{
    if(strcmp(key, "xdim") == 0) {
        config->xdim = val;
    }
    else if(strcmp(key, "ydim") == 0) {
        config->ydim = val;
    }
    else if(strcmp(key, "nzombies") == 0) {
        config->nzombies = val;
    }
    else if(strcmp(key, "nhumans") == 0) {
        config->nhumans = val;
    }
    else if(strcmp(key, "nzplayers") == 0) {
        config->nzplayers = val;
    }
    else if(strcmp(key, "nhplayers") == 0) {
        config->nhplayers = val;
    }
    else if(strcmp(key, "maxturns") == 0) {
        config->turns = val;
    }
}
