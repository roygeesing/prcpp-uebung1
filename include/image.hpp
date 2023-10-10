#pragma once
#include <memory>
#include <vector>
#include <utility>

struct Coordinate {
    int x = 0, y = 0;
};

struct RGBPixel {
    uint8_t red, green, blue;
    RGBPixel()
        : red{0}
        , green{0}
        , blue {0}
    {}
    RGBPixel(int r, int g, int b)
        : red{static_cast<uint8_t>(r)}
        , green{static_cast<uint8_t>(g)}
        , blue{static_cast<uint8_t>(b)}
    {}

    double getBrightness() const;
};

class RGBImage {
    size_t mSize;
    int mWidth, mHeight;
    std::unique_ptr<RGBPixel[]> mData;

public:
    // Constructors
    RGBImage()
        : mSize{0}
        , mWidth{0}
        , mHeight{0}
    {}
    RGBImage(int width, int height)
        : mSize(width * height)
        , mWidth(width)
        , mHeight(height)
        , mData(std::make_unique<RGBPixel[]>(width * height))
    {}
    RGBImage(const RGBPixel data[], int width, int height);
    explicit RGBImage(std::istream& in) { load(in); }

    // I/O operators
    void load(std::istream& in);
    void write(std::ostream& out) const;

    // Getters
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }
    size_t getSize() const { return mSize; }
    const RGBPixel getPixel(int x, int y) const;
    const RGBPixel getPixel(const Coordinate &p) const {
        return getPixel(p.x, p.y);
    }

    // Setters
    void setPixel(int x, int y, const RGBPixel &px);

    // Other functions
    Coordinate findBrightestPixel() const;
};
