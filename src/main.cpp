#include <iostream>
#include <fstream>
#include "image.hpp"
#include "histogram.hpp"
#include "filter.hpp"

using namespace std;

const char *separator = "===========================";

void print_header(string title) {
    cout << separator << endl << title << endl << separator << endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " [path]" << endl << endl
             << "Please provide the path of an image file to load." << endl;
        return 127;
    }

    string path = argv[1];

    print_header("(1) Loading image...");
    ifstream file(path);
    if (!file.good()) {
        throw runtime_error("File not found: " + path);
    }
    const RGBImage img = RGBImage(file);

    print_header("(2) Computing histogram...");
    const Histogram hist = Histogram(img, 40);
    hist.print(15);

    print_header("(3) Applying blur filters...");
    RGBImage blurred_box(img.getWidth(), img.getHeight());
    RGBImage blurred_gauss(img.getWidth(), img.getHeight());

    // Add suffixes to filename
    size_t ext_pos = path.rfind(".");
    string path_box = path;
    path_box.insert(ext_pos, "_boxblur");
    string path_gauss = path;
    path_gauss.insert(ext_pos, "_gauss");

    cout << "Box blur" << endl;
    applyBoxBlur(img, blurred_box);
    // Save to file
    ofstream out_box(path_box);
    blurred_box.write(out_box);
    cout << "> " << path_box << endl;
    out_box.close();

    cout << "Gaussian blur" << endl;
    applyGaussianBlur(img, blurred_gauss, 10.0);
    // Save to file
    ofstream out_gauss(path_gauss);
    blurred_gauss.write(out_gauss);
    cout << "> " << path_gauss << endl;
    out_gauss.close();

    print_header("(4) Finding brightest object...");
    Coordinate p = blurred_gauss.findBrightestPixel();
    cout << "Brightest object found at point ("
        << p.x << "/" << p.y << ") in image" << endl;

    return 0;
}
