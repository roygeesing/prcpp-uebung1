#include <iostream>
#include <sstream>
#include "image.hpp"

using namespace std;

RGBImage::RGBImage(const RGBPixel data[], int width, int height)
    : mWidth(width), mHeight(height), mSize(width * height) {
    mData = make_unique<RGBPixel[]>(mSize);
    copy(data, data+mSize, mData.get());
}

RGBPixel getPlainPixel(istream& in) {
    short r, g, b;
    in >> r >> g >> b;
    return {r, g, b};
}

RGBPixel getBinaryPixel(istream& in) {
    uint8_t values[3];
    in.read(reinterpret_cast<char *>(values), 3);
    auto [r, g, b] = values;
    return {r, g, b};
}

void RGBImage::load(istream& in) {
    // Check size
    in.seekg(0, ios::end);
    size_t filesize = in.tellg();
    cout << "Reading file of size " << filesize << " bytes" << endl;
    in.seekg(0, ios::beg);

    // File header
    // ===========
    // First line: magic bytes
    string magic;
    in >> magic;

    // Second line: dimensions
    in >> mWidth >> mHeight;
    mSize = mWidth * mHeight;
    mData = make_unique<RGBPixel[]>(mSize);

    // Third line: color depth
    uint16_t maxval;
    in >> maxval;
    if (maxval != 255) throw std::runtime_error("unexpected maxval");
    in >> std::ws; // Discard newline

    // Image data
    // ==========
    RGBPixel (*pixelFunction)(istream& in);

    if (magic == "P3") {
        pixelFunction = getPlainPixel;
    } else {
        pixelFunction = getBinaryPixel;
    }

    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
            setPixel(x, y, pixelFunction(in));
            if (in.eof() != 0) {
                throw std::runtime_error("unexpected eof");
            }
        }
    }
}

void RGBImage::write(ostream& out) const {
    out << "P6" << std::endl;
    out << mWidth << " " << mHeight << std::endl;
    out << "255" << std::endl;

    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
            RGBPixel pixel = getPixel(x, y);
            out.put(reinterpret_cast<char &>(pixel.red));
            out.put(reinterpret_cast<char &>(pixel.green));
            out.put(reinterpret_cast<char &>(pixel.blue));
        }
    }
}

const RGBPixel RGBImage::getPixel(int x, int y) const {
    return mData[y*mWidth + x];
}

void RGBImage::setPixel(int x, int y, const RGBPixel &px) {
    mData.get()[y*mWidth + x] = px;
}

double RGBPixel::getBrightness() const {
    return (red + green + blue) / (3.0 * 255);
}

Coordinate RGBImage::findBrightestPixel() const {
    int maxX = -1;
    int maxY = -1;
    double maxBrightness = -1;
    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
            RGBPixel pixel = getPixel(x, y);
            double brightness = pixel.getBrightness();
            if (brightness > maxBrightness) {
                maxX = x;
                maxY = y;
                maxBrightness = brightness;
            }
        }
    }
    return {maxX, maxY};
}
