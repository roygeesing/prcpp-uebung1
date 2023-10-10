#include <gtest/gtest.h>
#include "utils.hpp"

using namespace std;

void checkTinyEx(const RGBImage& img) {
    int i = 0;
    for (int y = 0; y < exDataHeight; y++) {
        for (int x = 0; x < exDataWidth; x++) {
            const RGBPixel px = img.getPixel(x, y);
            const RGBPixel ref = exData[i++];
            EXPECT_EQ(px.red, ref.red);
            EXPECT_EQ(px.green, ref.green);
            EXPECT_EQ(px.blue, ref.blue);
        }
    }
}

TEST(Task1a, TinyT3Image) {
    RGBImage img = load("01_ex_t3.ppm");
    checkTinyEx(img);
}

TEST(Task1b, TinyT6Image) {
    RGBImage img = load("01_ex_t6.ppm");
    checkTinyEx(img);
}

TEST(Task1b, RealImage) {
    RGBImage img = load("03_stars.ppm");
    size_t expected_size = 386694;
    EXPECT_EQ(img.getSize(), expected_size);
}

TEST(Task1a, InvalidFileType) {
    EXPECT_ANY_THROW(load("00_not_an_img.txt.ppm"));
}

TEST(Task1a, InvalidFileCorrupt) {
    EXPECT_ANY_THROW(load("00_corrupted.ppm"));
}
