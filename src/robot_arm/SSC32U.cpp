#define CR 13

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
    const int min_pos = -90;
    const int max_pos = 90;

    const int min_pulse = 500;
    const int max_pulse = 2500;

    int pos_width = max_pos - min_pos;
    int pulse_diff = max_pulse - min_pulse;
    int zero_pulse = round(float(pulse_diff) / 2.0) + min_pulse;
    int pulse_per_pos = round(float(pulse_diff) / float(pos_width));

    uint16_t pulseWidth = zero_pulse + position * pulse_per_pos;

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