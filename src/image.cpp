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
    RGBPixel (*pixelFunction) (istream& in);

    if (magic == "P3") {
        pixelFunction = getPlainPixel;
    } else {
        pixelFunction = getBinaryPixel;
    }

    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
            if (in.peek() == EOF) {
                throw std::runtime_error("error");
            }
            setPixel(x, y, pixelFunction(in));
        }
    }
}

void RGBImage::write(ostream& out) const {
    // TODO [Aufgabe] 3.b)
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
    // TODO [Aufgabe] 3.a)
    return {0, 0};
}
