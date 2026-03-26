#include "../filters.h"
#include <algorithm>

Image Flip_Horizontally(const Image& image) {
    Image flipped_image = image;
    for (int i = 0; i < image.width / 2; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                std::swap(flipped_image(i, j, k), flipped_image(image.width - i - 1, j, k));
            }
        }
    }
    return flipped_image;
}

Image Flip_Vertically(Image image) {
    Image flipped_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                std::swap(flipped_image(i, j, k), flipped_image(i, image.height - j - 1, k));
            }
        }
    }
    return flipped_image;
}