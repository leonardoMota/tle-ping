/**
 * @file socket.hpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief Socket class method header
 * @version 0.0.1
 */
#ifndef __SOCKET_TLE_HPP__
#define __SOCKET_TLE_HPP__

#include <arpa/inet.h>
#include <memory>
#include <vector>
#include <array>

/**********************************************
 * Public Defines 
 *********************************************/
#define TTL_INIT 255
#define RCV_TIMEOUT 1
#define MAX_SIZE_MSG_TO_RCV 76
/**********************************************/

class Socket
{
    public:
        /**
         * @brief Socket class constructor
         * 
         * @param dst_address destination address
         * @param port destination port
         * @param protocol connection protocol
         */
        Socket(in_addr_t dst_address, unsigned short port, unsigned char protocol);

        /**
         * @brief Send the message to the destination address
         * 
         * @param msg_to_snd message to be sent
         */
        void snd_msg(std::vector<unsigned char> msg_to_snd);

        /**
         * @brief returns message received from destination address
         */
        std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> rcv_msg();

    private:
        /** @brief Socket file descriptor */
        int fd;
        /** @brief Socket configuration  */
        struct sockaddr_in socket_addr;

        /** @brief Socket configuration size */
        socklen_t socket_addr_size;
};

#endif //__SOCKET_TLE_HPP__
//EOF