/**
 * @file icmp.hpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief ICPM class method header
 * @version 0.0.1
 */
#ifndef __ICMP_TLE_HPP__
#define __ICMP_TLE_HPP__

#include <memory>
#include <vector>

/**********************************************
 * Public Defines 
 *********************************************/
#define ICMP_PORT 0
/**********************************************/

/**@brief ICPM type message*/
typedef enum icmp_type
{
    ECHO_REPLY = 0,
    DESTINATION_UNREACHABLE = 3,
    SOURCE_QUENCH = 4,
    REDIRECT_MESSAGE = 5,
    ECHO_REQUEST = 8,
    ROUTER_ADVERTISEMENT = 9,
    ROUTER_SOLICITATION = 10,
    TIME_EXCEEDED = 11,
    PARAMETER_PROBLEM = 12,
    TIMESTAMP = 13,
    TIMESTAMP_REPLY = 14,
    INFORMATION_REQUEST = 15,
    INFORMATION_REPLY = 16,
    ADDRESS_MASK_REQUEST = 17,
    ADDRESS_MASK_REPLY = 18,
    TRACEROUTE = 30,
    EXTENDED_ECHO_REQUEST = 42,
    EXTENDED_ECHO_REPLY = 19,
} icmp_type_t;

/** @brief ICMP message codes by type, following the RFC792 standard */
typedef enum icmp_code
{
    /*> case icmp_type = 3 */
    NETWORK_UNREACHABLE             = 0,
    HOST_UNREACHABLE                = 1,
    PROTOCOL_UNREACHABLE            = 2,
    PORT_UNREACHABLE                = 3,
    FRAGMENTATION_NEEDED_AND_DF_SET = 4,
    SOURCE_ROUTE_FAILED             = 5,
    /*> case icmp_type = 5 */
    REDIRECT_DATAGRAMS_FOR_THE_NETWORK                      = 0,
    REDIRECT_DATAGRAMS_FOR_THE_HOST                         = 1,
    REDIRECT_DATAGRAMS_FOR_THE_TYPE_OF_SERVICE_AND_NETWORK  = 2,
    REDIRECT_DATAGRAMS_FOR_THE_TYPE_OF_SERVICE_AND_HOST     = 3,
    /*> case icmp_type = 11 */
    TIME_TO_LIVE_EXCEEDED             = 0,
    FRAGMENT_REASSEMBLY_TIME_EXCEEDED = 1,
    /*> case icmp_type = 0 || 8 || 12 || 4 || 13 || 14 || 15 || 16 */
    DEFAULT = 0
} icmp_code_t;


class Icmp
{
public:
    /**
     * @brief ICMP class Constructor
     * 
     * @param type ICMP type message
     * @param code ICMP code message
     */
    explicit Icmp(icmp_type_t type = ECHO_REQUEST, icmp_code_t code = DEFAULT);

    /**
     * @brief Encode ICMP header
     * 
     * @return std::vector<unsigned char>
     */
    std::vector<unsigned char> encode();

private:
    /** @brief ICPM message type */
    icmp_type_t type; 

    /** @brief ICPM messagem code */
    icmp_code_t code;

    /** @brief ICMP message identifier */
    unsigned short identifier{};

    /** @brief ICMP message sequence number */
    unsigned short seq{};

    /** @brief ICMP message checksum */
    unsigned int checksum;

    /** @brief ICMP message data field */
    std::vector<unsigned char> data;

    /**
     * @brief Updates the checksum field of the ICMP message
     *        with the calculated value
     * 
     * @return void
     */
    void checksum_update();
};

#endif //__ICMP_TLE_HPP__
//EOF