# Horn-Schunck Motion Estimation Method
This repository contains a C implementation of the Horn-Schunck motion estimation method, which is a classical optical flow algorithm that aims to estimate the dense optical flow between two consecutive frames in a video sequence.

The Horn-Schunck method is based on the assumption that the optical flow between two consecutive frames is smooth, and that it can be represented as a single vector field. The method formulates the estimation problem as an optimization problem that minimizes a cost function that balances the smoothness and accuracy of the flow estimate.

The implementation in this repository includes the following features:

Ability to handle grayscale or color video sequences
Ability to adjust the smoothness weight in the cost function
Ability to adjust the number of iterations in the optimization process
To use this implementation, simply call the hs_motion_estimation function with the input frames and desired parameters as inputs. The function will return the estimated optical flow as a two-dimensional array of vectors.

## Authors : 
- Youcef CHORFI
- Nacereddine LADDAOUI

## Dependencies
* [CMake](https://cmake.org/)

## Install
```
git clone https://github.com/Youcef-11/Horn-Schunck-Motion-Estimation-Method.git
mkdir build
cd build
cmake ..
make
./HornSchunk
```

## Results
<p align="center"><a href=https://github.com/Youcef-11/Horn-Schunck-Motion-Estimation-Method/blob/master/results/optical_flow.png?raw=true><img width="100%" src="./results/optical_flow.png" /></a></p>

Note that this implementation is provided for educational purposes and is not optimized for speed or memory usage. If you plan to use this method for real-time applications or large-scale video processing, you may need to consider alternative methods or optimize the code further.
