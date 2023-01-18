/**
 * @file icmp.cpp
 * @author Leo Mota <leonardoestevaoif@gmail.com>
 * @brief ICPM class method sources
 * @version 0.0.1
 */

#include "../header-files/icmp.hpp"


Icmp::Icmp(icmp_type_t type, icmp_code_t code) : type(type), 
                                             code(code), 
                                             checksum(0)
{
    this->data = std::vector<unsigned char>(2, 0);
}


std::vector<unsigned char> Icmp::encode()
{
/*  
   RFC 792 (Internet Standard) 

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
    std::vector<unsigned char> icmp_header;
    
    this->checksum_update();
    
    icmp_header.push_back(this->type);
    icmp_header.push_back(this->code);
    icmp_header.push_back(this->checksum >> 8);
    icmp_header.push_back(this->checksum & 0xFF);
    
    for (unsigned char &p_it : this->data)
    {
        icmp_header.push_back((p_it >> 8));
        icmp_header.push_back((p_it & 0xFF));
    }
    
    return icmp_header;
}

/**
 * @brief Updates the checksum field of the ICMP message
 *        with the calculated value
 * 
 * @return void
 */
void Icmp::checksum_update()
{
    unsigned int sum;

    sum = (this->type << 8) | this->code;
    
    for (unsigned char &p_it : this->data)
    {
        sum += p_it;
    }
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);

    this->checksum = ~sum;
}