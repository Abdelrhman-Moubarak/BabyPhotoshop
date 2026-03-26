#include "Image_Class.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include<cmath>

using namespace std;

void expandImage(Image& sourceImage, int largw, int largh) {
    Image tempImage(largw, largh);
    for (int i = 0; i < largw; ++i) {
        for (int j = 0; j < largh; ++j) {
            for (int k = 0; k < 3; ++k) {
                tempImage(i, j, k) = sourceImage(std::min(i, sourceImage.width - 1), std::min(j, sourceImage.height - 1), k);
            }
        }
    }
    sourceImage = move(tempImage);
}

Image MergeImages(const Image& image1, const std::string& filename2) {
    Image image2(filename2);
    Image tempImage1 = image1; // Make a copy of image1 to avoid modifying the original
    float largw = max(tempImage1.width, image2.width);
    float largh = max(tempImage1.height, image2.height);
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


Image Wano_sunlight(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Adjust each pixel
            int red_value = image(i, j, 0);
            int green_value = image(i, j, 1);
            int blue_value = image(i, j, 2);

            // Increase red_value and green_value channels to make it warmer
            red_value = min(255, red_value + 50); // Increase red_value
            green_value = min(255, green_value + 30); // Increase green_value

            // Adjust blue_value channel to avoid bright blues
            if (blue_value <= 100) {
                blue_value = min(255, blue_value + 20); // Increase blue_value
            } else {
                blue_value = max(0, blue_value - 20); // Decrease blue_value
            }

            // Set the new RGB values
            image(i, j, 0) = red_value;
            image(i, j, 1) = green_value;
            image(i, j, 2) = blue_value;
        }
    }
    return image;
}

Image TV_lines(Image& image) {
    int scan_line_Intensity = 320;

    // Loop through each row of pixels in the image
    for (int y = 0; y < image.height; ++y) {
        // Darken every other row of pixels
        if (y % 2 == 0) {
            for (int x = 0; x < image.width; ++x) {
                // Darken each pixel's intensity based on scanline intensity
                for (int c = 0; c < image.channels; ++c) {
                    int pixelValue = image.getPixel(x, y, c);
                    int darkenedValue = pixelValue - scan_line_Intensity;
                    // Ensure the pixel value is within the valid range [0, 255]
                    if (darkenedValue < 0) {
                        darkenedValue = 0;
                    }
                    image.setPixel(x, y, c, darkenedValue);
                }
            }
        }
    }
    return image;
}

Image Blur(Image& image) {
    for (int i = 6; i < image.height - 6; ++i) { // Adjusted for a 12x12 kernel
        for (int j = 6; j < image.width - 6; ++j) { // Adjusted for a 12x12 kernel
            for (int k = 0; k < 3; ++k) { // Assuming RGB channels
                int sum = 0;
                // Iterate over neighboring pixels
                for (int di = -6; di <= 6; ++di) { // Adjusted for a 12x12 kernel
                    for (int dj = -6; dj <= 6; ++dj) { // Adjusted for a 12x12 kernel
                        // Accumulate pixel values
                        sum += image.getPixel(j + dj, i + di, k);
                    }
                }
                // Calculate the average pixel value
                int avg = sum / 200;
                // Set the pixel value in the result image
                image.setPixel(j, i, k, avg);
            }
        }
    }
    return image;
}

Image Frame(const Image& image) {
    Image framed_image = image; // Create a copy of the original image to modify

    // Add the solid border
    int border_width = 200; // Width of the frame border
    for (int i = 0; i < framed_image.width; ++i) {
        for (int j = 0; j < framed_image.height; ++j) {
            if (i < border_width || i >= framed_image.width - border_width ||
                j < border_width || j >= framed_image.height - border_width) {
                // Set border color to green
                framed_image(i, j, 0) = 0; // Red component
                framed_image(i, j, 1) = 255; // Green component
                framed_image(i, j, 2) = 0; // Blue component
            }
        }
    }

    // Add the fancy frame
    for (int i = 0; i < framed_image.width; ++i) {
        for (int j = 0; j < framed_image.height; ++j) {
            int distance_to_edge_x = std::min(i, framed_image.width - 1 - i);
            int distance_to_edge_y = std::min(j, framed_image.height - 1 - j);
            int distance_to_edge = std::min(distance_to_edge_x, distance_to_edge_y);
            int intensity = (80 - distance_to_edge) * 255 / 80; // Adjust intensity based on distance to the edge
            if (distance_to_edge < 10) { // Add the fancy frame only within 10 pixels from the edge
                framed_image(i, j, 0) = intensity; // Red component
                framed_image(i, j, 1) = intensity; // Green component
                framed_image(i, j, 2) = intensity; // Blue component
            }
        }
    }

    return framed_image;
}



Image Rotate270(const Image& image) {
    Image rotated_image(image.height, image.width); // Rotated dimensions are swapped

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Access pixel from original image and assign it to the rotated image
                rotated_image(j, rotated_image.height - 1 - i, k) = image(i, j, k);
            }
        }
    }
    return rotated_image;
}

Image Rotate180(Image& image) {
    Image rotated_image(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; ++k) {
                rotated_image(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
            }
        }
    }

    return rotated_image;
}

Image Rotate90(Image& image) {
    Image rotated_image(image.height, image.width);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; ++k) {
                rotated_image(j, i, k) = image(i, j, k);
            }
        }
    }
    for (int i = 0; i < rotated_image.width / 2; i++) {
        for (int j = 0; j < rotated_image.height; j++) {
            for (int k = 0; k < rotated_image.channels; ++k) {
                swap(rotated_image(i, j, k), rotated_image(rotated_image.width - 1 - i, j, k));
            }
        }
    }
    return rotated_image;
}

Image Edges(const Image& image) {
    Image result_image = image; // Create a copy of the original image to modify

    // Convert image to grayscale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            // Set each channel to the average value to convert to grayscale
            result_image(i, j, 0) = avg;
            result_image(i, j, 1) = avg;
            result_image(i, j, 2) = avg;
        }
    }

    // Calculate edge intensity
    for (int i = 0; i < image.width - 1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {
            for (int k = 0; k < 3; ++k) {
                int diff1 = abs(result_image(i, j, k) - result_image(i + 1, j + 1, k));
                int diff2 = abs(result_image(i, j + 1, k) - result_image(i + 1, j, k));
                // Compute edge intensity using the sum of absolute differences
                result_image(i, j, k) = std::min(diff1 + diff2, 255);
            }
        }
    }

    // Invert colors
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                result_image(i, j, k) = 255 - result_image(i, j, k);
            }
        }
    }

    return result_image;
}


Image Purple_luffy(Image image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 1) = image(i,j,1) * 0.8;


            }
        }
    }
    return image;
}

Image Crop(Image image){
    cin.ignore();
    int x, y;
    string input1, input2, x_co, y_co, width, height;
    cout << "Enter the (x , y) Coordinates of the cropped area: ";
    getline(cin, input1);
    input1.erase(0,1);
    istringstream v1(input1);
    getline(v1, x_co, ' ');
    input1.erase(0, x_co.length() + 3);
    istringstream v2(input1);
    getline(v2, y_co, ')');
    x = stoi(x_co);
    y = stoi(y_co);
    cout << "Enter the dimensions of the cropped area:";
    getline(cin, input2);
    istringstream v3(input2);
    getline(v3, width, ' ');
    input2.erase(0, width.length() + 3);
    istringstream v4(input2);
    getline(v4, height, ' ');
    // Create a new image to store the cropped area
    Image cropped_image(stoi(width), stoi(height));
    // Copy the cropped area from the original image to the new image
    for (int i = 0; i < stoi(width); i++) {
        for (int j = 0; j < stoi(height); j++) {
            for (int k = 0; k < image.channels; k++) {
                // Ensure the pixel coordinates are within bounds
                if (x + i >= 0 and x + i < image.width and y + j >= 0 and y + j < image.height) {
                    cropped_image(i, j, k) = image(x + i, y + j, k);
                }
            }
        }
    }
    return cropped_image;
}

Image Resize(Image image) {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Please Enter the desired dimensions: ";
    string input, new_width, new_height;
    getline(cin, input);
    istringstream v1(input);
    getline(v1, new_width, ' ');
    input.erase(0, (new_width.length() + 3));
    istringstream v2(input);
    getline(v2, new_height, ' ');
    int x , y;
    x = stoi(new_width);
    y = stoi(new_height);
    double ratio_wide = static_cast<double>(image.width) / x;
    double ratio_height = static_cast<double>(image.height) / y;
    Image resized_image(x, y);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int old_x = static_cast<int>(round(i * ratio_wide));
                int old_y = static_cast<int>(round(j * ratio_height));
                resized_image(i, j, k) = image(old_x, old_y, k);
            }
        }
    }
    return resized_image;
}


// Function to invert colors of an image
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

// Function to lighten colors of an image
Image lighten(Image image){
    Image lightened_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (image(i,j,k) <= 170) {
                    lightened_image(i, j, k) *= 1.5;
                } else {
                    lightened_image(i,j,k) = 255;
                }
            }
        }
    }
    return lightened_image;
}

// Function to darken colors of an image
Image Darken(const Image& image){
    Image darkened_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                darkened_image(i,j,k) /= 2;
            }
        }
    }
    return darkened_image;
}

// Function to convert image to grayscale
Image Grayscale(Image image){
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

// Function to convert image to black and white
Image Black_White(Image image){
    Image bw_image = image;
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            unsigned int avg = 0;
            for(int k = 0; k < image.channels; k++){
                avg += image(i,j,k);
            }
            avg = avg/3;
            for(int k = 0; k < image.channels; k++){
                if(avg > 118){
                    bw_image(i,j,k) = 255;
                } else {
                    bw_image(i,j,k) = 0;
                }
            }
        }
    }
    return bw_image;
}

// Function to flip image horizontally
Image Flip_Horizontally(const Image& image) {
    Image flipped_image = image;
    for (int i = 0; i < image.width / 2; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                swap(flipped_image(i, j, k), flipped_image(image.width - i - 1, j, k));
            }
        }
    }
    return flipped_image;
}

// Function to flip image vertically
Image Flip_Vertically(Image image) {
    Image flipped_image = image;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                swap(flipped_image(i, j, k), flipped_image(i, image.height - j - 1, k));
            }
        }
    }
    return flipped_image;
}

int main() {
    Image image;
    Image filtered_image;
    bool imageLoaded = false; // Flag to track if an image is loaded

    // Menu-driven program loop
    while (true) {
        // Display menu options
        cout << "Menu Options:" << endl;
        cout << "A. Load a new image" << endl;
        cout << "1. Filter 1 // Grayscale" << endl;
        cout << "2. Filter 2 // Black & White" << endl;
        cout << "3. Filter 3 // Invert" << endl;
        cout << "4. Filter 4 // Merge" << endl;
        cout << "5. Filter 5 // Flip" << endl;
        cout << "6. Filter 6 // Rotate" << endl;
        cout << "7. Filter 7 // Darken & Lighten" << endl;
        cout << "8. Filter 8 // Crop" << endl;
        cout << "9. Filter 9 // Adding frame" << endl;
        cout << "10. Filter 10 // Detect edges" << endl;
        cout << "11. Filter 11 // Resizing" << endl;
        cout << "12. Filter 12 // Blur" << endl;
        cout << "13. Filter 13 // Wano Sunlight" << endl;
        cout << "14. Filter 16 // Purple luffy" << endl;
        cout << "15. Filter 15 // TV lines" << endl;
        cout << "16. Save the image" << endl;
        cout << "17. Exit" << endl;

        string choice; // Variable to store user's choice
        cout << "Enter your choice: ";
        cin >> choice; // Read user's choice

        // Handling user's choice
        if (choice == "A") {
            string image_name;
            cout << "Enter the name of the image to load: ";
            cin >> image_name;
            bool success = image.loadNewImage(image_name); // Attempt to load image
            if (success) {
                imageLoaded = true; // Mark image as loaded
                cout << "Image loaded successfully." << endl;
            } else {
                cout << "Failed to load the image! Please try again." << endl;
            }
        } else if (choice  == "1") { // Apply filters if an image is loaded
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Grayscale(image);
                cout << "Grayscale filter has been applied." << endl;
            }
        } else if (choice == "2"){
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Black_White(image);
                cout << "Black & White filter has been applied." << endl;
            }
        } else if (choice == "3"){
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Inverted(image);
                cout << "The Invert filter has been applied." << endl;
            }
        } else if (choice == "4"){
            if (!imageLoaded){
                cout << "No image is loaded" << endl;
            } else {
                string filename2;
                cin >> filename2;
                filtered_image = MergeImages(image, filename2);
            }
        } else if (choice == "5") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                cout << "1. Flip vertically" << endl;
                cout << "2. Flip horizontally" << endl;
                char x;
                cin >> x;
                if (x == '1') {
                    filtered_image = Flip_Vertically(image);
                    cout << "The image has been flipped vertically." << endl;
                } else if (x == '2') {
                    filtered_image = Flip_Horizontally(image);
                    cout << "The image has been flipped horizontally." << endl;
                }
            }
        } else if (choice == "6") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                cout << "1. Rotate 90" << endl;
                cout << "2. Rotate 180" << endl;
                cout << "3. Rotate 270" << endl;
                char x;
                cin >> x;
                if (x == '1') {
                    filtered_image = Rotate90(image);
                    cout << "The image has been Rotated 90 degrees." << endl;
                } else if (x == '2') {
                    filtered_image = Rotate180(image);
                    cout << "The image has been Rotated 180 degrees." << endl;
                } else if (x == '3') {
                    filtered_image = Rotate270(image);
                    cout << "The image has been Rotated 270 degrees." << endl;
                }
            }
        } else if (choice == "7") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                cout << "1. Darken the image" << endl;
                cout << "2. Lighten the image" << endl;
                char y;
                cin >> y;
                if(y == '1'){
                    filtered_image = Darken(image);
                    cout << "The image has been darkened successfully." << endl;
                } else if(y == '2') {
                    filtered_image = lighten(image);
                    cout << "The image has been lightened successfully." << endl;
                }
            }
        } else if (choice == "8") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Crop(image);
                cout << "The image has been Cropped successfully." << endl;
            }
        } else if (choice == "9") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Frame(image);
                cout << "The Frame has been successfully added." << endl;
            }
        } else if (choice == "10") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Edges(image);
                cout << "The Edges filter has been applied." << endl;
            }
        } else if (choice == "11") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Resize(image);
                //filtered_image.saveImage("resized_image.jpg"); // Save the resized image
                cout << "The Resize filter has been applied." << endl;
            }
        } else if (choice == "12") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Blur(image);
                cout << "The Blur filter has been applied." << endl;
            }
        } else if (choice == "13") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Wano_sunlight(image);
                cout << "Wano sunlight has been fixed." << endl;
            }
        } else if (choice == "14") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = Purple_luffy(image);
                cout << "The Purple filter has been applied." << endl;
            }
        } else if (choice == "15") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                filtered_image = TV_lines(image);
                cout << "The TV_lines filter has been applied." << endl;
            }
        } else if (choice == "16") {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                string new_image_name;
                cout << "Enter the filename to save the image: ";
                cin >> new_image_name;
                bool good = filtered_image.saveImage(new_image_name); // Save the original image
                if (good) {
                    cout << "Image saved successfully." << endl;
                } else {
                    cerr << "Failed to save the image! Please try again." << endl;
                }
            }
        } else if (choice == "17") {
            cout << "Exiting..." << endl;
            return 0; // Exit the program
        } else {
            cout << "Please enter a valid input" << endl; // Invalid input
        }
    }
}
