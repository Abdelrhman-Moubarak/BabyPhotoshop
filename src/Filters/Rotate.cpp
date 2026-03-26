#include "../filters.h"
#include <algorithm>

Image Rotate90(Image& image) {
    Image rotated_image(image.height, image.width);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; ++k) {
                rotated_image(j, i, k) = image(i, j, k);
            }
        }
    }
    for (int i = 0; i < rotated_image.width / 2; i++) {
        for (int j = 0; j < rotated_image.height; j++) {
            for (int k = 0; k < rotated_image.channels; ++k) {
                std::swap(rotated_image(i, j, k), rotated_image(rotated_image.width - 1 - i, j, k));
            }
        }
    }
    return rotated_image;
}

Image Rotate180(Image& image) {
    Image rotated_image(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; ++k) {
                rotated_image(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
            }
        }
    }
    return rotated_image;
}

Image Rotate270(const Image& image) {
    Image rotated_image(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotated_image(j, rotated_image.height - 1 - i, k) = image(i, j, k);
            }
        }
    }
    return rotated_image;
}