# robot_arm_aansturing

## Compile

From root catkin workspace:

```
catkin_make
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
