/**
 * @file SSC32U.hpp
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief provides an easy to use interface for using functionality of the servo controller board SSC32U. 
 * @version 0.1
 * @date 2019-03-14
 * 
 */
#ifndef SSC32U_HPP
#define SSC32U_HPP

#include <string>
#include <boost/asio.hpp>

class SSC32U
{
public:
    /**
     * @brief Construct a new SSC32U servo controller
     * 
     * @param portName the name of the port the servo controller is connected too. For example: /dev/ttyUSB0".
     * @param baudRate the baudrate used to communicate with the board. By default it is 9600.
     */
    SSC32U(std::string portName, unsigned int baudRate = 9600);
    ~SSC32U();

    /**
     * @brief move one servo to a specific position and degrees. A speed and time can be specified in miliseconds. 
     * If not specified or 0 it will try to go as fast as possible to the given position. if both are specified it will choose the slowest one to reach the goal position.
     * 
     * @param pin of the servo you want to control. Specifiey the (signal) pin that is connected on the board with the servo.
     * @param position the desired position to move to.
     * @param speed 
     * @param time in miliseconds it will arive at the goal.
     */
    void move(uint8_t pin, int16_t position, uint16_t speed = 0, uint16_t time = 0);
    /**
     * @brief Set the Position Offset of a servo. Min is -100 max is 100. 0 is none. the max offset is about 15 degrees.
     * 
     * @param pin of the servo
     * @param pulse the pulse width ofset of the servo
     */
    void setPositionOffset(uint8_t pin, int8_t pulse);
    
private:
    void sendCommand(uint8_t pin, uint16_t pulseWidth, uint16_t speed = 0, uint16_t time = 0);

    boost::asio::serial_port * port;
};

#endif