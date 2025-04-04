#pragma once

#include <netinet/in.h>

struct tcp_traffic_pkg {
    in_port_t src_port;
    in_addr_t dst_addr;
    in_port_t dst_port;
    const size_t sz;
};

struct tcp_traffic {
    in_addr_t src_addr;
    struct tcp_traffic_pkg* pkgs;
    size_t pkgs_sz;
};