#pragma once
#include "image.hpp"

void applyBoxBlur(const RGBImage& src, RGBImage& dest);
void applyGaussianBlur(const RGBImage& src, RGBImage& dest, double sigma);
double computeGaussian(int dx, int dy, double sigma);
