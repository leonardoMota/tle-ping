/**
 * @file main.cpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief Main application file 
 * @version 0.0.1
 */

#include <iostream>
#include "../header-files/icmp.hpp"
#include "../header-files/socket.hpp"
#include "../header-files/utils.hpp"
#include <chrono>
#include <unistd.h>

#define MAX_PARAMETERS 3
#define MILLISECONDS_SCALE 1000

int main(int argc, char *argv[])
{
    in_addr_t dst_ip;
    std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> msg_rcvd;
    try
    {   
        uint32_t n_ping_tries = atoi(argv[2]);
        for(uint32_t i = 0; i < n_ping_tries; i++){
            
            usleep(500000);

            if (argc > MAX_PARAMETERS)
            {
                throw std::runtime_error("Number of parameters exceeded. Run only destination IP Address [255.255.255.0] plus [N times] to run");
            }

            dst_ip = get_ip_by_hostname(argv[1]);
            std::unique_ptr<Icmp> icmp = std::make_unique<Icmp>();
            std::unique_ptr<Socket> socket = std::make_unique<Socket>(dst_ip, ICMP_PORT, IPPROTO_ICMP);
            
            auto start_time = std::chrono::steady_clock::now();
            
            socket->snd_msg(icmp->encode()); // Sends ICMP message
            msg_rcvd = socket->rcv_msg(); // receive message reply 

            auto end_time = std::chrono::steady_clock::now();

            //Calculates the time to receive the response
            std::chrono::duration<double> diff_time = (end_time - start_time)*MILLISECONDS_SCALE;

            std::cout << "Reply from " << argv[1] << ": time = " << diff_time.count() << " milliseconds. \n";
        }
    
    }
    catch (const std::runtime_error &error)
    {
        std::cout << "Exception: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}