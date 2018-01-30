#include "read_from_config.h"
#include "example.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CONFIG read_config(int argc, char *argv[]) {

    const char *delim = "=\n"; /* Delimitator */
    CONFIG config; /* CONFIG object */
    char str[MAXSTR]; /* String to store value read from file */
    FILE *fp = NULL; /* Pointer to FILE object */
    char *filename = argv[1]; /* String that will hold second param of argv */
    char *token; /* Var that will receive value from strtok */

    /* If parameters are more than 2 show error message */
    if (argc > 2) {
        fprintf(stderr, "Too many arguments.");
        fprintf(stderr, "\nUsage mode: ./program_name config.ini\n");
        exit(1);
    }
    /* If parameter is 1 show error message */
    if (argc == 1) {
        fprintf(stderr, "Too few arguments.");
        fprintf(stderr, "\nUsage mode: ./program_name config.ini\n");
        exit(1);
    }
    /* Show message if unable to open configuration file */
    else {
        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Unable to open configuration file.");
            fprintf(stderr, "\nUsage mode: ./program_name config.ini\n");
            exit(1);
        }
    }
    /* Read from file */
    while (fgets(str, MAXSTR, fp) != NULL) {
        /* Searches for the first occurence of character '=' */
        if (strchr(str, '=')) {
            /* String to receive value from config file */
            char varname[100];
            int value;
            /* Strtok will split what's before and after '=' */
            token = strtok(str, delim);
            /* Copy token to varname */
            strcpy(varname, token);
            token = strtok(NULL, delim);
            /* Value receives a numeric value from token */
            value = atoi(token);
            /* Calls function to set configuration values */
            set_config_val(&config, varname, value);
        }
    }
    /* Close the file */
    fclose(fp);
    /* Return config object that contains variables from the config.ini file */
    return config;
}

/* Function to set values from config.ini file */
void set_config_val(CONFIG *config, const char *key, int val)
{
    /* If key is equal to xdim (config file param) then val receives xdim value */
    if(strcmp(key, "xdim") == 0) {
        config->xdim = val;
    }
    /* If key is equal to ydim (config file param) then val receives ydim value */
    else if(strcmp(key, "ydim") == 0) {
        config->ydim = val;
    }
    /* If key is equal to nzombies then val receives nzombies value */
    else if(strcmp(key, "nzombies") == 0) {
        config->nzombies = val;
    }
    /* If key is equal to nhumans then val receives nhumans value */
    else if(strcmp(key, "nhumans") == 0) {
        config->nhumans = val;
    }
    /* If key is equal to nzplayers then val receives nzplayers value */
    else if(strcmp(key, "nzplayers") == 0) {
        config->nzplayers = val;
    }
    /* If key is equal to nhplayers then val receives nhplayers value */
    else if(strcmp(key, "nhplayers") == 0) {
        config->nhplayers = val;
    }
    /* If key is equal to maxturns then val receives maxturns value */
    else if(strcmp(key, "maxturns") == 0) {
        config->turns = val;
    }
}
