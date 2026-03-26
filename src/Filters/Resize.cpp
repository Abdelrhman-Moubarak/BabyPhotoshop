#include "../filters.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

using namespace std;

Image Resize(Image image) {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Please Enter the desired dimensions (width height): ";
    string input, new_width, new_height;
    getline(cin, input);
    istringstream v1(input);
    getline(v1, new_width, ' ');
    input.erase(0, (new_width.length() + 1));
    istringstream v2(input);
    getline(v2, new_height, ' ');
    int x = stoi(new_width);
    int y = stoi(new_height);
    double ratio_wide = static_cast<double>(image.width) / x;
    double ratio_height = static_cast<double>(image.height) / y;
    Image resized_image(x, y);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int old_x = static_cast<int>(round(i * ratio_wide));
                int old_y = static_cast<int>(round(j * ratio_height));
                resized_image(i, j, k) = image(old_x, old_y, k);
            }
        }
    }
    return resized_image;
}