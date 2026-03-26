#include "../filters.h"

Image Grayscale(Image image) {
    Image grayscale_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; ++k) {
                grayscale_image(i, j, k) = avg;
            }
        }
    }
    return grayscale_image;
}