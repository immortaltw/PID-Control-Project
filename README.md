# PID Control Project

The goal of this project is to use PID control to drive the car safely in the simulated environment.

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Result

![Result](./PID.gif)

## Discussion

From the lecture we learned that I (integral) term helps to compensate for biases, P term (proportional) is a straight forward compensation in proportion to the error. This term introduces overshoot. The D term (derivative) helps mitigate the overshoot introduced by P term. It kind of estimate future trend of the error.

The final hyperparameters for P, I and D I used in this project are 1.78952, 0.000205549, 15.2015 respectively. I used twiddle to find these three parameters. I found that it's important to choose the right initial value, since twiddle algorithm gives you local optimums. Some local optimums performs better than the others. Also I set throttle to 0.6 and set the training dataset size to 600 when training with twiddle. This helped to get a parameter set which works at higher speed.


