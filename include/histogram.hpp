#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include "image.hpp"

class Histogram {
    std::unique_ptr<int[]> mData;
    int mNumBins;

 public:
    Histogram() : mNumBins(0) {}
    explicit Histogram(const std::vector<int>& data);
    Histogram(const RGBImage& img, int num_bins) { process(img, num_bins); }

    void process(const RGBImage& img, int num_bins);

    int getBin(int i) const { return mData.get()[i]; }
    int getNumBins() const { return mNumBins; }

    void print(int height) const;
    bool operator==(const Histogram& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Histogram& h) {
        os << "[ ";
        for (int i = 0; i < h.mNumBins; i++) {
            os << h.mData[i] << ' ';
        }
        return os << ']';
    }
};
