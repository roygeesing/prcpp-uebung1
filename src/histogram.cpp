#include <iostream>
#include "histogram.hpp"

using namespace std;

Histogram::Histogram(const vector<int> &data) {
    mNumBins = (int)data.size();
    mData = make_unique<int[]>(mNumBins);
    copy(data.begin(), data.end(), mData.get());
}

bool Histogram::operator==(const Histogram& other) const {
    if (this->getNumBins() != other.getNumBins()) {
        return false;
    }
    for (int i = 0; i < getNumBins(); i++) {
        if (this->getBin(i) != other.getBin(i)) {
            return false;
        }
    }
    return true;
}

void Histogram::process(const RGBImage& img, int numBins) {
    mNumBins = numBins;
    mData = make_unique<int[]>(numBins);
    for (int y = 0; y < img.getHeight(); y++) {
        for (int x = 0; x < img.getWidth(); x++) {
            double brightness = img.getPixel(x, y).getBrightness();
            int bin = (int) (brightness * numBins);
            mData[min(bin, numBins - 1)]++;
        }
    }
}

void Histogram::print(int height) const {
    int maxValue = 0;
    for (int i = 0; i < mNumBins; i++) {
        if (mData[i] > maxValue) {
            maxValue = mData[i];
        }
    }

    float interval = (float) maxValue / (float) height;
    for (int x = height; x > 0; x--) {
        float currentLimit = interval * (float) x;
        for (int i = 0; i < mNumBins; i++) {
            if ((float) mData[i] >= currentLimit) {
                std::cout << "❚";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    cout << "|";
    for (int i = 1; i < mNumBins-1; i++) {
        cout <<  "-";
    }
    cout << "|" << endl;

    cout << "0% ";
    for (int i = 3; i < mNumBins-4; i++) {
        cout << " ";
    }
    cout << "100%" << endl;
}
