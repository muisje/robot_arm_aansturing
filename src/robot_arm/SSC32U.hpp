#ifndef SSC32U_HPP
#define SSC32U_HPP

#include <string>
#include <boost/asio.hpp>

class SSC32U
{
public:
    SSC32U(std::string portName, unsigned int baudRate = 9600);
    ~SSC32U();

    void move(uint8_t pin, int16_t position, uint16_t speed = 0, uint16_t time = 0);
    void setPositionOffset(uint8_t pin, int8_t pulse);
    
private:
    void sendCommand(uint8_t pin, uint16_t pulseWidth, uint16_t speed = 0, uint16_t time = 0);

    boost::asio::serial_port * port;
};

#endif