/**
 * @file utils.hpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief Utils header
 * @version 0.0.1
 */
#ifndef __UTILS_TLE_HPP__
#define __UTILS_TLE_HPP__

#include <arpa/inet.h>

/**
 * @brief Returns the resolved ip address from a destination ip
 * 
 * @param dst_address destination address 
 * @return in_addr_t 
 */
extern in_addr_t get_ip_by_hostname(const char *dst_address);

#endif //__UTILS_TLE_HPP__