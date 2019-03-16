# Notes

Set position ofset with pulse -100 to 100 is around 15 degrees

0 is no ofset default baudrate

1  baudrate 115200 (green and red led) and doing weird things base is 850 (pulse) right up

2 default baudrate

"robot 2" kan niet rechtop elbow is fout

map robotarm , ofset per joint

## timing


### gripper

Name: HS-422

Speed: 4.8V: 0.21 sec/60°
6.0V: 0.16 sec/60°
Pulse Width: 900-2100 µs

worst_case_min = 180 / 60 * 0.21 = 0.63 s

Rotational Range: 180°

bronnen:

* [lynx motion: al5d](http://www.lynxmotion.com/c-130-al5d.aspx)
* [ServoDatabase.com: Hitec HS-422 - Deluxe Standard Servo](https://servodatabase.com/servo/hitec/hs-422)

### Serial

9600, 38400, and 115200 bits per second are the standard baud rates

#### 1 commando

command = #4P2100\r

9 characters is 9 bytes is 72 bits

72 / 9600   = 0.0075   seconden voor het commando over serial @ 9600   baud
72 / 38400  = 0.001875 seconden voor het commando over serial @ 38400  baud
72 / 115200 = 0.000625 seconden voor het commando over serial @ 115200 baud

#### 6 commando's

0.0075   * 6 = 0.045   seconden voor het commando over serial @ 9600   baud
0.001875 * 6 = 0.01125 seconden voor het commando over serial @ 38400  baud
0.000625 * 6 = 0.00375 seconden voor het commando over serial @ 115200 baud

### robot_arm_controller

controller.sendRequest(input);

min = 424 ms max is 703 ms

### robot_arm

robotArm.gotoPosition took 0 milliseconds

#### opmerkingen
  
* Lijkt slomer te worden na lang gebruik. Komt hoogstwaarschijnlijk door de while loop.
* fans gaan behoorlijk blazen.

### Onbekend

* verwerkingstijd van SCC32U voor commando's