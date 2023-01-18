/**
 * @file socket.cpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief Socket class method sources
 * @version 0.0.1
 */

#include "../header-files/socket.hpp"
#include <sys/time.h>


Socket::Socket(in_addr_t dst_address, unsigned short port, unsigned char protocol)
{
    int fd, ret;
    struct sockaddr_in socket_addr;
    unsigned int ttl = TTL_INIT;
    struct timeval rcv_timeout = {
        .tv_sec = RCV_TIMEOUT,
        .tv_usec = 0
    };

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = dst_address;
    socket_addr.sin_port = port;

    
    fd = socket(AF_INET, SOCK_RAW, protocol);
    if (fd < 0)
    {
        throw std::runtime_error("Error in acquiring the file descriptor");
    }

    ret = setsockopt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
    if (ret != 0)
    {
        throw std::runtime_error("Socket TTL configuration error");
    }

    ret = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&rcv_timeout, sizeof(rcv_timeout));
    if (ret != 0)
    {
        throw std::runtime_error("Error in message timeout configuration by socket");
    }

    this->socket_addr = socket_addr;
    this->socket_addr_size = sizeof(socket_addr);
    this->fd = fd;
}

void Socket::snd_msg(std::vector<unsigned char> msg_to_snd)
{
    int msg_snt;

    msg_snt = sendto(this->fd, msg_to_snd.data(), msg_to_snd.size(), 0,
                    (struct sockaddr *)&this->socket_addr, this->socket_addr_size);
    
    if (msg_snt < 0)
    {
        throw std::runtime_error("Error sending message by socket");
    }
}

std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> Socket::rcv_msg()
{
    int flag_rcvd;
    std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> msg_to_rcv;

    flag_rcvd = recvfrom(this->fd, msg_to_rcv.data(), msg_to_rcv.size(), 0,
                       (struct sockaddr *)&this->socket_addr, &this->socket_addr_size);
    
    if (flag_rcvd < 0)
    {
        throw std::runtime_error("Error when receiving message via socket");
    }
    
    return msg_to_rcv;
}

