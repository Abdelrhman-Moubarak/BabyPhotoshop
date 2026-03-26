#include "../filters.h"
#include <iostream>
#include <sstream>

using namespace std;

Image Crop(Image image) {
    cin.ignore();
    int x, y;
    string input1, input2, x_co, y_co, width, height;
    cout << "Enter the (x , y) Coordinates of the cropped area: ";
    getline(cin, input1);
    input1.erase(0, 1);
    istringstream v1(input1);
    getline(v1, x_co, ' ');
    input1.erase(0, x_co.length() + 3);
    istringstream v2(input1);
    getline(v2, y_co, ')');
    x = stoi(x_co);
    y = stoi(y_co);
    cout << "Enter the dimensions of the cropped area:";
    getline(cin, input2);
    istringstream v3(input2);
    getline(v3, width, ' ');
    input2.erase(0, width.length() + 3);
    istringstream v4(input2);
    getline(v4, height, ' ');
    Image cropped_image(stoi(width), stoi(height));
    for (int i = 0; i < stoi(width); i++) {
        for (int j = 0; j < stoi(height); j++) {
            for (int k = 0; k < image.channels; k++) {
                if (x + i >= 0 && x + i < image.width && y + j >= 0 && y + j < image.height) {
                    cropped_image(i, j, k) = image(x + i, y + j, k);
                }
            }
        }
    }
    return cropped_image;
}