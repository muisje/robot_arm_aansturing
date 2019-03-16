# robot_arm_aansturing

## Compile

From root:

```
mkdir build
cd build
cmake ../src
make
```

## Documenation

* [site](https://muisje.github.io/robot_arm_aansturing/)
* [pdf](docs/doc.pdf)

## Building documentation

```
cd docs
pandoc -N --variable mainfont="Palatino" --variable sansfont="Helvetica" --variable monofont="Menlo" --variable fontsize=12pt --variable version=2.0 doc.md -o doc.pdf
```
