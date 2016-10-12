#ifndef __DRAW_H__
#define __DRAW_H__

#include <GLFW/glfw3.h>
#include <cstring>
#include <string>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <iostream>
#include <vector>

//Canvas Size
const int width = 1024;
const int height = 768;

//Pixel Array
float* pixels = new float[width * height * 3];


#endif