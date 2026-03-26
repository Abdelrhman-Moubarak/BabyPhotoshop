#include "../filters.h"

Image Edges(const Image& image) {
    Image result_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            result_image(i, j, 0) = avg;
            result_image(i, j, 1) = avg;
            result_image(i, j, 2) = avg;
        }
    }
    for (int i = 0; i < image.width - 1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {
            for (int k = 0; k < 3; ++k) {
                int diff1 = abs(result_image(i, j, k) - result_image(i + 1, j + 1, k));
                int diff2 = abs(result_image(i, j + 1, k) - result_image(i + 1, j, k));
                result_image(i, j, k) = std::min(diff1 + diff2, 255);
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                result_image(i, j, k) = 255 - result_image(i, j, k);
            }
        }
    }
    return result_image;
}