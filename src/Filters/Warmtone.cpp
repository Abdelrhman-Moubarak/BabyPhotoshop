#include "../filters.h"

Image WarmTone(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int red   = std::min(255, (int)image(i, j, 0) + 50);
            int green = std::min(255, (int)image(i, j, 1) + 30);
            int blue  = image(i, j, 2);
            if (blue <= 100) {
                blue = std::min(255, blue + 20);
            } else {
                blue = std::max(0, blue - 20);
            }
            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }
    return image;
}