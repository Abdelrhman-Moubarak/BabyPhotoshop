#include "../filters.h"

Image ScanLines(Image& image) {
    int scan_line_intensity = 320;
    for (int y = 0; y < image.height; ++y) {
        if (y % 2 == 0) {
            for (int x = 0; x < image.width; ++x) {
                for (int c = 0; c < image.channels; ++c) {
                    int val = image.getPixel(x, y, c) - scan_line_intensity;
                    if (val < 0) val = 0;
                    image.setPixel(x, y, c, val);
                }
            }
        }
    }
    return image;
}
