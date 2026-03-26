#include "../filters.h"

Image Darken(const Image& image) {
    Image darkened_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                darkened_image(i, j, k) /= 2;
            }
        }
    }
    return darkened_image;
}

Image lighten(Image image) {
    Image lightened_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (image(i, j, k) <= 170) {
                    lightened_image(i, j, k) *= 1.5;
                } else {
                    lightened_image(i, j, k) = 255;
                }
            }
        }
    }
    return lightened_image;
}