# Description
Hardware Monitor allows to read hardware sensors, store the values, and analyze it with Fast Fourier Transformation.


# Usage

## Command line

### hardmon-reader

`hardmon-reader` reads and stores in HDF5 file data from sensors.

A configuration file to be provided to the tool specifying the sensors.
The configuration file should have YAML format.
An example of config file is available at [config/reader.yml.sample](config/reader.yml.sample)


The following command line options are available for `hardmon-reader`:
```sh
hardmon-reader --help
Allowed options:
  --help                produce help message
  --config arg          path to config file
  --data arg            path to output HDF5 file
```


### hardmon-plotter

`hardmon-plotter` uses stored data to create graphical plots.

It allows as creation of time/value graphs, as conducting Fast Fourier Transformation to measure power spectrum of the signal.

In order to produce the graph, path to the HDF5 file and the sensor identifier must be specified on command line.

Generation of FFT graph is being controlled by `--fft` option with optional `--threads` option specifying number of threads to use for FFT.

The generated graphs may be opened with `gnuplot` utility. Example: `gnuplot -p fft.gnuplot`.


The following command line options are available for `hardmon-plotter`:
```sh
hardmon-plotter --help
Usage:
  --help                produce help message
  --data arg            path to input HDF5 file
  --sensor arg          identifier of the sensor to draw
  --plot arg            path to output gnuplot file
  --fft                 transform data with FFT
  --threads arg         threads to use for FFT
```


## Sensors

The following sensors are available:

### regular-file

`regular-file` sensor reads a single values from a file.
This sensor is suitable for reading system characteristics, such as CPU frequency, FAN speed, temperature, etc. from the system files, like: `/sys/devices/system/cpu/cpufreq/policy0/scaling_cur_freq`

Sensor options:
* `filename`: string, path to the file to read


### snd-file
`snd-file` sensor reads frames from a sound file.

The sensor imitates playback by skipping amount of frames between measurements accordingly to passed time.

Sensor options:
* `filename`: string, path to the file to read
* `channel`: integer (default: 0), index of the channel to measure
* `skip-millisec` integer (default: 0), skip the specified amount of milliseconds from the beginning of the file before reading


# Build dependencies

All necessary build dependencies mentioned below may be installed on Ubuntu with the following command:
```sh
sudo apt install build-essential cmake g++ libyaml-cpp-dev libboost-all-dev libhdf5-dev libfftw3-dev libsndfile1-dev libgtest-dev libgmock-dev
```

### Compiler
GCC is being used by the author. Nevertheless, another **C++20** compatible compiler should be appropriate as well.


### CMake
CMake is an open-source, cross-platform family of tools designed to build, test and package software.

<https://cmake.org/>


### yaml-cpp
yaml-cpp is a YAML parser and emitter in C++ matching the YAML 1.2 spec.

<https://github.com/jbeder/yaml-cpp>


### HighFive
HighFive - HDF5 header-only C++ Library.
_Added as a Git submodule._

<https://github.com/BlueBrain/HighFive>


### hdf5
Hierarchical Data Format 5.

<https://www.hdfgroup.org/solutions/hdf5>


### FFTW
FFTW is a C subroutine library for computing the discrete Fourier transform (DFT).

<https://www.fftw.org/>


### FFTW++
FFTW++: Fast Fourier Transform C++ Header/MPI Transpose for FFTW3.
_Added as a Git submodule._

<https://fftwpp.sourceforge.net/>


### boost >= 1.41
Boost provides free peer-reviewed portable C++ source libraries.

<https://www.boost.org/>


### libsndfile
Libsndfile is a C library for reading and writing files containing sampled sound.

<https://github.com/libsndfile/libsndfile>


### GTest & GMock
Google Test is a C++ test framework.

<https://github.com/google/googletest>


# Installation

### Configuration
Ensure that submodules are loaded:
```sh
git submodule update --init --recursive
```

To configure the project use CMake. Example command:
```sh
mkdir build
cd build
cmake ..
```

### Build
Command to build:
```sh
cmake --build . --target all
```


### Testing

By default tests are being enabled. To disable tests use the following CMake option during configuration: `ENABLE_UNIT_TESTS`.

Example:
```sh
mkdir build
cd build
cmake -DENABLE_UNIT_TESTS=OFF ..
```

Testing is implemented with GTest.


Tests can be launched with `ctest` command from CMake package.

Alternatively `check` target can be built, which will execute the tests:
```sh
cmake --build . --target check
```
