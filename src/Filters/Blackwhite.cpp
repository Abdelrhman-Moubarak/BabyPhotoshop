#include "../filters.h"

Image Black_White(Image image) {
    Image bw_image = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; k++) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < image.channels; k++) {
                if (avg > 118) {
                    bw_image(i, j, k) = 255;
                } else {
                    bw_image(i, j, k) = 0;
                }
            }
        }
    }
    return bw_image;
}