# openexr-bind

Python bindings of OpenEXR library using pybind

## Requirements:
- ilmbase
- openexr
- pyilmbase (reuse ilmbase base types) - hence requires Boost python
- python
- cmake

## Building
```
cmake -DPYTHON_VERSION=3.7 ..
```

## Example:
```
python3.7 -c "import example; print (example.add(2,3))"
```

## Troubleshooting

#### Install Python headers
sudo apt install python2.7-dev/bionic-updates

#### Install Python CMake files
In case CMake returns the following error:
```
Could not find a package configuration file provided by "Python" (requested version 3.7) with any of the following names:
    PythonConfig.cmake
    python-config.cmake
```
It is recommended to build CMake from scratch so that it is installed with all the addons.
```
git clone https://github.com/Kitware/CMake.git
git checkout v3.15.0
./bootstrap && make && sudo make install
```


