/**
 * @file utils.cpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief Utils source
 * @version 0.0.1
 */
#include "../header-files/utils.hpp"
#include <netdb.h>
#include <stdexcept>

in_addr_t get_ip_by_hostname(const char *dst_address)
{
    struct hostent *p_host;

    p_host = gethostbyname(dst_address);
    if (p_host == 0)
    {
        throw std::runtime_error("Unknown destination address");
    }
    
    return *(in_addr_t *)p_host->h_addr;
}