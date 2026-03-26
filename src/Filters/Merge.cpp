#include "../filters.h"
#include <utility>

void expandImage(Image& sourceImage, int largw, int largh) {
    Image tempImage(largw, largh);
    for (int i = 0; i < largw; ++i) {
        for (int j = 0; j < largh; ++j) {
            for (int k = 0; k < 3; ++k) {
                tempImage(i, j, k) = sourceImage(std::min(i, sourceImage.width - 1), std::min(j, sourceImage.height - 1), k);
            }
        }
    }
    sourceImage = std::move(tempImage);
}

Image MergeImages(const Image& image1, const std::string& filename2) {
    Image image2(filename2);
    Image tempImage1 = image1;
    float largw = std::max(tempImage1.width, image2.width);
    float largh = std::max(tempImage1.height, image2.height);
    if (tempImage1.width != largw || tempImage1.height != largh) {
        expandImage(tempImage1, largw, largh);
    }
    if (image2.width != largw || image2.height != largh) {
        expandImage(image2, largw, largh);
    }
    Image mergedImage(largw, largh);
    for (int i = 0; i < largw; ++i) {
        for (int j = 0; j < largh; ++j) {
            for (int k = 0; k < 3; ++k) {
                mergedImage(i, j, k) = (tempImage1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
    return mergedImage;
}