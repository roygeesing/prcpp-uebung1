#include <gtest/gtest.h>
#include <sstream>
#include "utils.hpp"
#include "filter.hpp"

using namespace std;

void check_blurred_image(const RGBImage &img) {
    // Check middle pixels in squares
    EXPECT_DOUBLE_EQ(img.getPixel(15, 45).getBrightness(), 1.0);
    // Check some black pixels
    EXPECT_DOUBLE_EQ(img.getPixel(25, 25).getBrightness(), 0.0);
    EXPECT_DOUBLE_EQ(img.getPixel(14, 15).getBrightness(), 0.0);
    EXPECT_DOUBLE_EQ(img.getPixel(36, 15).getBrightness(), 0.0);

    // Check horizontal symmetry
    const int width = 50-1;
    EXPECT_DOUBLE_EQ(img.getPixel(9, 31).getBrightness(),
                     img.getPixel(width-9, 31).getBrightness());
    EXPECT_DOUBLE_EQ(img.getPixel(20, 9).getBrightness(),
                     img.getPixel(width-20, 9).getBrightness());
}

TEST(Task4a, BoxBlurFilterTest) {
    RGBImage raw = load("02_checkerboard.ppm");
    RGBImage img(raw.getWidth(), raw.getHeight());
    applyBoxBlur(raw, img);

    string out_path = getImagePath("02_checkerboard_boxblur.ppm");
    ofstream file(out_path);
    img.write(file);
    cout << "> " << out_path << endl;

    const double tolerance = 0.01;

    // Check invariants
    check_blurred_image(img);

    // Check some pixels on edges
    double b1 = img.getPixel(5, 10).getBrightness();
    EXPECT_GE(b1, 95.0/255 * (1-tolerance));
    EXPECT_LE(b1, 95.0/255 * (1+tolerance));
    double b2 = img.getPixel(11, 26).getBrightness();
    EXPECT_GE(b2, 69.0/255 * (1-tolerance));
    EXPECT_LE(b2, 69.0/255 * (1+tolerance));
}

TEST(Task4b, GaussianBlurFilterTest) {
    RGBImage raw = load("02_checkerboard.ppm");
    RGBImage img(raw.getWidth(), raw.getHeight());
    applyGaussianBlur(raw, img, 3.0);

    string out_path = getImagePath("02_checkerboard_gaussian.ppm");
    ofstream file(out_path);
    img.write(file);
    cout << "> " << out_path << endl;

    const double tolerance = 0.01;

    // Check invariants
    check_blurred_image(img);

    // Check some pixels on edges
    double b1 = img.getPixel(5, 10).getBrightness();
    EXPECT_GE(b1, 84.0/255 * (1-tolerance));
    EXPECT_LE(b1, 84.0/255 * (1+tolerance));
    double b2 = img.getPixel(11, 26).getBrightness();
    EXPECT_GE(b2, 51.0/255 * (1-tolerance));
    EXPECT_LE(b2, 51.0/255 * (1+tolerance));
}

TEST(Task4c, FindBrightestObjectTest) {
    RGBImage raw = load("03_stars.ppm");
    RGBImage img(raw.getWidth(), raw.getHeight());
    applyGaussianBlur(raw, img, 10.0);
    Coordinate p = img.findBrightestPixel();

    const double tolerance = 2;

    EXPECT_GE(p.x, 294-tolerance);
    EXPECT_LE(p.x, 294+tolerance);
    EXPECT_GE(p.y, 269-tolerance);
    EXPECT_LE(p.x, 294+tolerance);
}
