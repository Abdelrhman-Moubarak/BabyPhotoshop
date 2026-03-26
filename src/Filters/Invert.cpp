#include "../filters.h"

Image Inverted(Image image) {
    Image inverted_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                inverted_image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    return inverted_image;
}