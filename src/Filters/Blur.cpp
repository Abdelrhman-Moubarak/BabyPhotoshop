#include "../filters.h"

Image Blur(Image& image) {
    for (int i = 6; i < image.height - 6; ++i) {
        for (int j = 6; j < image.width - 6; ++j) {
            for (int k = 0; k < 3; ++k) {
                int sum = 0;
                for (int di = -6; di <= 6; ++di) {
                    for (int dj = -6; dj <= 6; ++dj) {
                        sum += image.getPixel(j + dj, i + di, k);
                    }
                }
                int avg = sum / 200;
                image.setPixel(j, i, k, avg);
            }
        }
    }
    return image;
}