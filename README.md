# robot_arm_aansturing

Software for controlling a Lynx AL5D robot arm with ROS.

### Build dependencies

Make sure these are installed first:

    cmake 3.1 and above
    ROS Melodic Morenia
    boost
    c++ 14


## Compile

From root catkin workspace:

```
catkin_make
```

## Run

Pre condition:

* Ros core is running

### robot_arm_controller
From root catkin workspace:
```
source ./devel/setup.bash
rosrun robot_arm_aansturing robot_arm
```

### robot_arm_controller
From root catkin workspace:
```
source ./devel/setup.bash
rosrun robot_arm_aansturing robot_arm_controller
```


## Documenation

* [site](https://muisje.github.io/robot_arm_aansturing/)
* [pdf](docs/doc.pdf)

## Building documentation

From package robot_arm_aansturing root:
```
cd docs
pandoc -N --variable mainfont="Palatino" --variable sansfont="Helvetica" --variable monofont="Menlo" --variable fontsize=12pt --variable version=2.0 doc.md -o doc.pdf
```
