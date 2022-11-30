#pragma once
#ifndef NAT_PMP_OPTIONS_H
#define NAT_PMP_OPTIONS_H

enum action {
    ACTION_ADD_MAPPING,
    ACTION_DELETE_MAPPING,
    ACTION_SHOW_EXTERNAL_IP
};

struct options {
    enum action act;

    char *gateway;
    int gw_port;

    int internal_port;
    int external_port;

    int lifetime_in_secs;
};

struct options parse_argv(int argc, char *argv[]);

#endif //NAT_PMP_OPTIONS_H
