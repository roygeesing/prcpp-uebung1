#include "utils.hpp"
#include <fstream>
#include <string>

using namespace std;

std::string getImagePath(string filename) {
    return "../img/" + filename;
}

RGBImage load(string filename) {
    string path = getImagePath(filename);
    cout << endl << "< " << path << endl;
    ifstream file(path, ios::binary);
    if (!file.good()) {
        throw runtime_error("File not found: " + path);
    }
    return RGBImage(file);
}
