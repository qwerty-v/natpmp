#include <assert.h>
#include <string.h>

#include "../../src/options.h"

int test_show_external_ip() {
    char *argv[] = {
            "natpmp",
            "-s",
            "192.168.1.1"
    };
    struct options opts = parse_argv(3, argv);

    assert(opts.act == ACTION_SHOW_EXTERNAL_IP);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 5351);

    return 0;
}

int test_show_external_ip_with_port() {
    char *argv[] = {
            "natpmp",
            "-s",
            "192.168.1.1",
            "-p",
            "1234"
    };
    struct options opts = parse_argv(5, argv);

    assert(opts.act == ACTION_SHOW_EXTERNAL_IP);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 1234);

    return 0;
}

int test_add_mapping() {
    char *argv[] = {
            "natpmp",
            "-a",
            "192.168.1.1",
            "8080",
            "80"
    };
    struct options opts = parse_argv(5, argv);

    assert(opts.act == ACTION_ADD_MAPPING);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 5351);
    assert(opts.internal_port == 8080);
    assert(opts.external_port == 80);
    assert(opts.lifetime_in_secs == 24 * 60 * 60);

    return 0;
}

int test_add_mapping_with_lifetime() {
    char *argv[] = {
            "natpmp",
            "-a",
            "192.168.1.1",
            "8080",
            "80",
            "-l",
            "60"
    };
    struct options opts = parse_argv(7, argv);

    assert(opts.act == ACTION_ADD_MAPPING);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 5351);
    assert(opts.internal_port == 8080);
    assert(opts.external_port == 80);
    assert(opts.lifetime_in_secs == 60);

    return 0;
}

int test_add_mapping_with_port() {
    char *argv[] = {
            "natpmp",
            "-a",
            "192.168.1.1",
            "-p",
            "1234",
            "8080",
            "80"
    };
    struct options opts = parse_argv(7, argv);

    assert(opts.act == ACTION_ADD_MAPPING);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 1234);
    assert(opts.internal_port == 8080);
    assert(opts.external_port == 80);
    assert(opts.lifetime_in_secs == 24 * 60 * 60);

    return 0;
}

int test_add_mapping_with_lifetime_and_port() {
    char *argv[] = {
            "natpmp",
            "-a",
            "192.168.1.1",
            "-p",
            "1234",
            "8080",
            "80",
            "-l",
            "60"
    };
    struct options opts = parse_argv(9, argv);

    assert(opts.act == ACTION_ADD_MAPPING);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 1234);
    assert(opts.internal_port == 8080);
    assert(opts.external_port == 80);
    assert(opts.lifetime_in_secs == 60);

    return 0;
}

int test_delete_mapping() {
    char *argv[] = {
            "natpmp",
            "-d",
            "192.168.1.1",
            "8080",
    };
    struct options opts = parse_argv(4, argv);

    assert(opts.act == ACTION_DELETE_MAPPING);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 5351);
    assert(opts.internal_port == 8080);

    return 0;
}

int test_delete_mapping_with_port() {
    char *argv[] = {
            "natpmp",
            "-d",
            "192.168.1.1",
            "-p",
            "1234",
            "8080",
    };
    struct options opts = parse_argv(6, argv);

    assert(opts.act == ACTION_DELETE_MAPPING);
    assert(strcmp(opts.gateway, "192.168.1.1") == 0);
    assert(opts.gw_port == 1234);
    assert(opts.internal_port == 8080);

    return 0;
}

int main() {
    test_show_external_ip();
    test_show_external_ip_with_port();

    test_add_mapping();
    test_add_mapping_with_lifetime();
    test_add_mapping_with_port();
    test_add_mapping_with_lifetime_and_port();

    test_delete_mapping();
    test_delete_mapping_with_port();
    return 0;
}