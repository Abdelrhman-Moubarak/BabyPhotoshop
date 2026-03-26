#ifndef FILTERS_H
#define FILTERS_H

#include "../lib/Image_Class.h"

Image Grayscale(Image image);
Image Black_White(Image image);
Image Inverted(Image image);
Image MergeImages(const Image& image1, const std::string& filename2);
Image Flip_Horizontally(const Image& image);
Image Flip_Vertically(Image image);
Image Rotate90(Image& image);
Image Rotate180(Image& image);
Image Rotate270(const Image& image);
Image Darken(const Image& image);
Image lighten(Image image);
Image Crop(Image image);
Image Frame(const Image& image);
Image Edges(const Image& image);
Image Resize(Image image);
Image Blur(Image& image);
Image WarmTone(Image image);
Image PurpleTint(Image image);
Image ScanLines(Image& image);

#endif