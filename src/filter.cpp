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
    std::cout << "starting box blur";
    if (src.getWidth() != dest.getWidth()
        || src.getHeight() != dest.getHeight()) {
        throw runtime_error("Size mismatch");
    }

    int width = src.getWidth();
    int height = src.getHeight();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint16_t totalRed = 0, totalGreen = 0, totalBlue = 0;
            uint8_t numberOfPixels = 0;

            for (int8_t diffY = -1; diffY <= 1; diffY++) {
                int pixelY = y + diffY;
                if (pixelY < 0 || pixelY >= height) {
                    continue;
                }
                for (int8_t diffX = -1; diffX <= 1; diffX++) {
                    int pixelX = x + diffX;
                    if (pixelX < 0 || pixelX >= width) {
                        continue;
                    }

                    RGBPixel pixel = src.getPixel(pixelX, pixelY);
                    numberOfPixels++;
                    totalRed += pixel.red;
                    totalGreen += pixel.green;
                    totalBlue += pixel.blue;
                }
            }

            dest.setPixel(x, y, {totalRed / numberOfPixels, totalGreen / numberOfPixels, totalBlue / numberOfPixels});
        }
    }
}

void applyGaussianBlur(const RGBImage& src, RGBImage& dest, double sigma) {
    if (src.getWidth() != dest.getWidth()
        || src.getHeight() != dest.getHeight()) {
        throw runtime_error("Size mismatch");
    }
    const int radius = (int)sigma;

    int width = src.getWidth();
    int height = src.getHeight();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double b = 0;
            double total_weights = 0;

            for (int dy = -radius; dy <= radius; dy++) {
                int pixelY = y + dy;
                if (pixelY < 0 || pixelY >= height) {
                    continue;
                }
                for (int dx = -radius; dx <= radius; dx++) {
                    int pixelX = x + dx;
                    if (pixelX < 0 || pixelX >= width) {
                        continue;
                    }

                    double weight = computeGaussian(dx, dy, sigma);
                    b += src.getPixel(pixelX, pixelY).getBrightness() * weight;
                    total_weights += weight;
                }
            }

            b /= total_weights;

            RGBPixel px(int(b*255), int(b*255), int(b*255));
            dest.setPixel(x, y, px);
        }
    }
}
