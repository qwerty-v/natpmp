#include "options.h"

#include <printf.h>
#include <string.h>
#include <stdlib.h>

void print_usage() {
    printf("Usage:\n"
           "     natpmp -s gateway [-p port]\n"
           "     natpmp -a gateway [-p port] internal_port external_port [-l lifetime]\n"
           "     natpmp -d gateway [-p port] internal_port\n");
    exit(-1);
}

/**
 * returns remaining argument count
 * @param total
 * @param current
 * @return
 */
int remaining(int argc, int ind) {
    return argc - ind;
}

struct options parse_argv(int argc, char *argv[]) {
    struct options opts;
    memset(&opts, 0, sizeof(opts));

    opts.gw_port = 5351; // use 5351 port by default
    opts.lifetime_in_secs = 24 * 60 * 60; // set lifetime to day by default

    // ind is current position at the argv array
    // starting at 1 (ignoring first argument)
    int ind = 1;

    if (remaining(argc, ind) < 2) {
        // user is required to specify at least command and gateway
        print_usage();
    }

    // parse action
    char *act = argv[ind++];
    if (strncmp(act, "-s", 2) == 0) {
        opts.act = ACTION_SHOW_EXTERNAL_IP;
    } else if (strncmp(act, "-a", 2) == 0) {
        opts.act = ACTION_ADD_MAPPING;
    } else if (strncmp(act, "-d", 2) == 0) {
        opts.act = ACTION_DELETE_MAPPING;
    } else {
        // unknown action
        print_usage();
    }

    // parse gateway
    opts.gateway = argv[ind++];

    // parse gateway port
    if (remaining(argc, ind) >= 2 && strncmp(argv[ind], "-p", 2) == 0) {
        // move index since -p option was found
        ind++;

        opts.gw_port = (int) strtol(argv[ind++], NULL, 10);
    }

    if (opts.act == ACTION_SHOW_EXTERNAL_IP) {
        if (remaining(argc, ind) > 0) {
            // too many arguments
            print_usage();
        }

        return opts;
    }

    if (remaining(argc, ind) < 1) {
        // at this point user is required to specify internal port
        print_usage();
    }

    // parse internal port
    opts.internal_port = (int) strtol(argv[ind++], NULL, 10);

    if (opts.act == ACTION_DELETE_MAPPING) {
        if (remaining(argc, ind) > 0) {
            // too many arguments
            print_usage();
        }

        return opts;
    }

    if (remaining(argc, ind) < 1) {
        // at this point user is required to specify external port
        print_usage();
    }

    // parse external port
    opts.external_port = (int) strtol(argv[ind++], NULL, 10);

    if (remaining(argc, ind) == 0) {
        return opts;
    }

    if (strncmp(argv[ind++], "-l", 2) != 0) {
        // at this point user is required to specify lifetime
        print_usage();
    }

    // parse lifetime
    opts.lifetime_in_secs = (int) strtol(argv[ind++], NULL, 10);

    if (remaining(argc, ind) != 0) {
        // too many arguments
        print_usage();
    }

    return opts;
}