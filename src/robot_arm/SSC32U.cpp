#define CR 13
#define MIN_POS -90
#define MAX_POS 90
#define MIN_PULSE 500
#define MAX_PULSE 2500
#define POS_WIDTH MAX_POS - MIN_POS
#define PULSE_DIFF MAX_PULSE - MIN_PULSE
#define ZERO_PULSE round(float(PULSE_DIFF) / 2.0) + MIN_PULSE
#define PULSE_PER_POS round(float(PULSE_DIFF) / float(POS_WIDTH));

#include "SSC32U.hpp"

SSC32U::SSC32U(std::string portName, unsigned int baudRate)
{
    boost::asio::io_service io;
    port = new boost::asio::serial_port(io, portName);
    port->set_option(boost::asio::serial_port_base::baud_rate(baudRate));
}

SSC32U::~SSC32U()
{
    port->close();
    delete port;
}

void SSC32U::move(uint8_t pin, int16_t position, uint16_t speed, uint16_t time)
{
    uint16_t pulseWidth = ZERO_PULSE + position * PULSE_PER_POS;
    sendCommand(pin, pulseWidth, speed, time);
}

void SSC32U::setPositionOffset(uint8_t pin, int8_t pulse)
{
    if (pulse < -100)
    {
        pulse = -100;
    }
    if (pulse > 100)
    {
        pulse = 100;
    }

    std::string command = '#' + std::to_string(pin) + "PO" + std::to_string(pulse);
    command += CR;
    port->write_some(boost::asio::buffer(command.data(), command.size()));
}

void SSC32U::sendCommand(uint8_t pin, uint16_t pulseWidth, uint16_t speed, uint16_t time)
{
    std::string command = '#' + std::to_string(pin) + 'P' + std::to_string(pulseWidth);
    if (speed != 0)
    {
        command += "S" + std::to_string(speed);
    }
    if (time != 0)
    {
        command += "T" + std::to_string(time);
    }
    command += CR;
    port->write_some(boost::asio::buffer(command.data(), command.size()));
}