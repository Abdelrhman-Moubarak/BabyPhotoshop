#include "../filters.h"

Image PurpleTint(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 1) = image(i, j, 1) * 0.8;
        }
    }
    return image;
}
