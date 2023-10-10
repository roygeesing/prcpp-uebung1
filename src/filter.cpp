#include <iostream>
#include <cmath>
#include <numbers>
#include "filter.hpp"

using namespace std;

double computeGaussian(int dx, int dy, double sigma) {
    double dist_sq = dx*dx + dy*dy;
    return 1 / sqrt(2 * numbers::pi_v<double> * sigma*sigma) * exp(-dist_sq / (2 * sigma*sigma));
}

void applyBoxBlur(const RGBImage& src, RGBImage& dest) {
    if (src.getWidth() != dest.getWidth()
        || src.getHeight() != dest.getHeight()) {
        throw runtime_error("Size mismatch");
    }

    // TODO [Aufgabe] 4.a)
}

void applyGaussianBlur(const RGBImage& src, RGBImage& dest, double sigma) {
    if (src.getWidth() != dest.getWidth()
        || src.getHeight() != dest.getHeight()) {
        throw runtime_error("Size mismatch");
    }
    const int radius = (int)sigma;

    for (int y = 0; y < src.getHeight(); y++) {
        for (int x = 0; x < src.getWidth(); x++) {
            // TODO [Aufgabe] 4.b)
            double b = src.getPixel(x, y).getBrightness();

            double result = 0;
            double total_weights = 0;

            for (int dy = -radius; dy <= radius; dy++) {
                // ...
            }

            RGBPixel px(int(b*255), int(b*255), int(b*255));
            dest.setPixel(x, y, px);
        }
    }
}
