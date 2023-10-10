#include <gtest/gtest.h>
#include "utils.hpp"

using namespace std;

TEST(Task3a, BrightestPixelTestTiny) {
    RGBImage img = load("01_ex_t6.ppm");
    Coordinate p = img.findBrightestPixel();
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 1);
    EXPECT_DOUBLE_EQ(img.getPixel(p).getBrightness(), 1.0);
}

TEST(Task3a, BrightestPixelTestGrey) {
    RGBPixel data[] = {
        RGBPixel(100, 100, 100), RGBPixel(150, 150, 150), RGBPixel(0, 0, 0)
    };
    RGBImage img(data, 2, 1);
    Coordinate p = img.findBrightestPixel();
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 0);
}

TEST(Task3a, BrightestPixelTestReal) {
    RGBImage img = load("03_stars.ppm");
    Coordinate p = img.findBrightestPixel();
    EXPECT_DOUBLE_EQ(img.getPixel(p).getBrightness(), 1.0);
}

TEST(Task3b, SaveImageTestTiny) {
    RGBImage img(exData, exDataWidth, exDataHeight);
    ostringstream buffer;
    img.write(buffer);
    string data = buffer.str();

    ifstream file(getImagePath("01_ex_t6.ppm"));
    ostringstream expected;
    expected << file.rdbuf();
    EXPECT_EQ(data, expected.str());
}

TEST(Task3b, SaveImageTestReal) {
    RGBImage img = load("03_stars.ppm");
    ostringstream buffer;
    img.write(buffer);
    const int file_size = 1160097;
    EXPECT_EQ(buffer.str().length(), file_size);
}
