#include "../filters.h"

Image Frame(const Image& image) {
    Image framed_image = image;
    int border_width = 200;
    for (int i = 0; i < framed_image.width; ++i) {
        for (int j = 0; j < framed_image.height; ++j) {
            if (i < border_width || i >= framed_image.width - border_width ||
                j < border_width || j >= framed_image.height - border_width) {
                framed_image(i, j, 0) = 0;
                framed_image(i, j, 1) = 255;
                framed_image(i, j, 2) = 0;
            }
        }
    }
    for (int i = 0; i < framed_image.width; ++i) {
        for (int j = 0; j < framed_image.height; ++j) {
            int distance_to_edge_x = std::min(i, framed_image.width - 1 - i);
            int distance_to_edge_y = std::min(j, framed_image.height - 1 - j);
            int distance_to_edge = std::min(distance_to_edge_x, distance_to_edge_y);
            int intensity = (80 - distance_to_edge) * 255 / 80;
            if (distance_to_edge < 10) {
                framed_image(i, j, 0) = intensity;
                framed_image(i, j, 1) = intensity;
                framed_image(i, j, 2) = intensity;
            }
        }
    }
    return framed_image;
}