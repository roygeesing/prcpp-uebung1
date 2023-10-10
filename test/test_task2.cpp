#include <gtest/gtest.h>
#include <sstream>
#include "utils.hpp"

using namespace std;

TEST(Task2a, BrightnessTest) {
    RGBImage img = load("01_ex_t6.ppm");
    EXPECT_DOUBLE_EQ(img.getPixel(0, 1).getBrightness(), 2.0/3);
    EXPECT_DOUBLE_EQ(img.getPixel(1, 0).getBrightness(), 1.0/3);
    EXPECT_EQ(img.getPixel(1, 1).getBrightness(), 1.0);
    EXPECT_EQ(img.getPixel(2, 1).getBrightness(), 0.0);
}

TEST(Task2b, HistogramComputeTestArtificial) {
    RGBImage img = load("02_gradients.ppm");
    const int n_bins = 10;
    Histogram h(img, 10);
    cout << "alive" << endl;
    Histogram h_expected({771, 535, 512, 759, 844, 200, 185, 186, 210, 298});
    EXPECT_EQ(h, h_expected);
}

TEST(Task2b, HistogramComputeTestReal) {
    RGBImage img = load("03_stars.ppm");
    Histogram h(img, 20);
    Histogram h_expected({
        367060, 14742, 2202, 760, 395, 251, 187, 119, 128, 81,
        80, 63, 59, 52, 48, 36, 37, 41, 51, 302
    });
    EXPECT_EQ(h, h_expected);
}

void check_hist_output(const Histogram& h, int height, const int expected[]) {
    stringstream captured_stdout;
    streambuf *original_stdout = cout.rdbuf(captured_stdout.rdbuf());
    h.print(height);
    // Restore cout
    cout.rdbuf(original_stdout);

    vector<int> expected_full(expected, expected+height);
    expected_full.push_back(0);
    expected_full.push_back(0);

    string line;
    int i = 0;
    while (getline(captured_stdout, line)) {
        cout << line << endl;
        int n_pluses = -1;
        int pos = -1;
        do {
            pos = line.find("❚", pos+1);
            n_pluses++;
        } while (pos != string::npos);
        EXPECT_EQ(n_pluses, expected_full[i++]);
    }
}

TEST(Task2c, HistogramOutputTestSmall) {
    Histogram h({100, 30, 75, 60, 5, 10});
    const int expected[] = {1, 1, 3, 3, 4, 5};
    check_hist_output(h, 5, expected);
}

TEST(Task2c, HistogramOutputTestLarge) {
    Histogram h({11, 22, 33, 17, 99, 0, 66, 120});
    const int expected[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 5, 7};
    check_hist_output(h, 12, expected);
}

TEST(Task2c, HistogramFullTest) {
    RGBImage img = load("02_gradients.ppm");
    Histogram h(img, 30);
    const int expected[] = {1, 3, 5, 5, 7, 8, 15, 15, 16, 18, 30, 30};
    check_hist_output(h, 12, expected);
}
