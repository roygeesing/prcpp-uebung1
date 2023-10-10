#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "histogram.hpp"

std::string getImagePath(std::string filename);
RGBImage load(std::string filename);

const RGBPixel exData[] = {
    RGBPixel(255, 0, 0), RGBPixel(0, 255, 0), RGBPixel(0, 0, 255),
    RGBPixel(255, 255, 0), RGBPixel(255, 255, 255), RGBPixel(0, 0, 0)
};
const int exDataWidth = 3;
const int exDataHeight = 2;
