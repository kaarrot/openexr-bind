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
### CMake flags
-DPYTHON_VERSION=2.7 - version of Python
-DBUILD_BOOST_PYTHON=OFF - Builds local version of Boost-Python (may be required for building python3 bindings). Default version uses system Boost 
-DOFFLINE=OFF Uses tar.gz files located in the root of the projects. Skip download step.
-DUSE_CUSTOM_PYTHON="" Specify custom version of Python to build bindings. The version has to match -DPYTHON_VERSION flag


## Example (testing Pybind11):
```
python3.7 -c "import example; print (example.add(2,3))"
```

## Testing
```
cd tests
run_tests.sh
```

## Building custom Python
```
git clone https://github.com/python/cpython.git
./configure --enable-shared --prefix=$HOME/toolchains/python
make install
```
Building Boost-Python find python executable py running 'python'. Create a Symlink  python to pythonX.X
```
cd $HOME/python/bin && ln -s python3.9 python
```
Similarily for shared library as it is -lpython is used in pyilmbase link tests
```
cd $HOME/python/lib && ln -s python3.so python.so
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


