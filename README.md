# openexr-bind

Python bindings for OpenEXR library using Pybind11

## Requirements:
- ilmbase
- openexr
- pyilmbase (reuse ilmbase base types) - requires Boost python,system
- python
- cmake
- Boost Python (support for Python version the bindings are built for)

NOTE: Currently PyIlmbase does not compile using Python3.
For full functionality please use Python 2.7 for the time being. 

## Building 
```
export PYTHON=python3.6  # extra step for PyIlmbase
cmake -DPYTHON_VERSION=3.6 ..
cmake .. -DPYTHON_VERSION=3.6 -DBUILD_BOOST_PYTHON=ON
```

## Example (testing Pybind11):
```
python3.7 -c "import example; print (example.add(2,3))"
```

## Testing
```
cd tests
run_tests.sh
```

## Troubleshooting

#### Install Python headers
sudo apt install python2.7-dev

#### Install boost dependencies
Pass ```-DBUILD_BOOST_PYTHON=ON``` flag while configuring cmake or install with package manager
```
sudo apt install libboost-system1.60-dev/oldstable
sudo apt install libboost-python1.60-dev/oldstable
```
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


