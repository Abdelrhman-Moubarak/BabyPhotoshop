// CS112_A3_Part1_S7,8_20230205_20230179_20230616
// some image filters
// Abdelrhman Amgad Ali(S7)_Nariman Sayed(S)_Somaya Amr Abd El-ghfour(S8)
// Abdelrhman Amgad Ali(abdelrhmanwork589@gmail.com)_Nariman Sayed(narimansayed28@gmail.com)_Somaya Amr Abd El-ghfour(Somayaamr857@gmail.com)
// ID1: 20230205 - Black & White filter and flipping the image
// ID2: 20230616 - Inverting filter
// ID3: 20230179 - Grayscale filter and Darken & Lighten filters


#include "Image_Class.h"
#include <iostream>
#include <string>

using namespace std;

// Function to invert colors of an image
void Inverted(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

// Function to lighten colors of an image
void lighten(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if (image(i,j,k) <= 170) {
                    image(i, j, k) *= 1.5;
                } else {
                    image(i,j,k) = 255;
                }
            }
        }
    }
}

// Function to darken colors of an image
void Darken(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image(i,j,k) /= 2;
            }
        }
    }
}

// Function to convert image to grayscale
void Grayscale(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = avg;
            }
        }
    }
}

// Function to convert image to black and white
void Black_White(Image& image){
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            unsigned int avg = 0;
            for(int k = 0; k < image.channels; k++){
                avg += image(i,j,k);
            }
            avg = avg/3;
            for(int k = 0; k < image.channels; k++){
                if(avg > 118){
                    image(i,j,k) = 255;
                } else {
                    image(i,j,k) = 0;
                }
            }
        }
    }
}

// Function to flip image horizontally
void Flip_Horizontally(Image& image) {
    for (int i = 0; i < image.width / 2; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                swap(image(i, j, k), image(image.width - 1 -i, j, k));
            }
        }
    }
}

// Function to flip image vertically
void Flip_Vertically(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                swap(image(i, j, k), image(i, image.height - 1 - j, k));
            }
        }
    }
}

int main() {
    Image image; // Declare an instance of the Image class
    bool imageLoaded = false; // Flag to track if an image is loaded

    // Menu-driven program loop
    while (true) {
        // Display menu options
        cout << "Menu Options:" << endl;
        cout << "1. Load a new image" << endl;
        cout << "2. Filter 1 // Grayscale" << endl;
        cout << "3. Filter 2 // Black & White" << endl;
        cout << "4. Filter 3 // Flip" << endl;
        cout << "5. Filter 4 // Darken & Lighten" << endl;
        cout << "6. Filter 5 // Invert" << endl;
        cout << "7. Save the image" << endl;
        cout << "8. Exit" << endl;

        int choice; // Variable to store user's choice
        cout << "Enter your choice: ";
        cin >> choice; // Read user's choice

        // Handling user's choice
        if (choice == 1) {
            string imagename;
            cout << "Enter the imagename of the image to load: ";
            cin >> imagename;
            Image currentimage;
            bool success = image.loadNewImage(imagename); // Attempt to load image
            if (success) {
                imageLoaded = true; // Mark image as loaded
                cout << "Image loaded successfully." << endl;
            } else {
                cout << "Failed to load the image! Please try again." << endl;
            }
        } else if (choice >= 2 && choice <= 6) { // Apply filters if an image is loaded
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                switch(choice) {
                    case 2:
                        Grayscale(image);
                        cout << "Grayscale filter has been applied." << endl;
                        break;
                    case 3:
                        Black_White(image);
                        cout << "Black & White filter has been applied." << endl;
                        break;
                    case 4:
                        cout << "1. Flip vertically" << endl;
                        cout << "2. Flip horizontally" << endl;
                        char x;
                        cin >> x;
                        if(x == '1'){
                            Flip_Vertically(image);
                            cout << "The image has been flipped vertically." << endl;
                        } else if(x == '2') {
                            Flip_Horizontally(image);
                            cout << "The image has been flipped horizontally." << endl;
                        }
                        break;
                    case 5:
                        cout << "1. Darken the image" << endl;
                        cout << "2. Lighten the image" << endl;
                        char y;
                        cin >> y;
                        if(y == '1'){
                            Darken(image);
                            cout << "The image has been darkened successfully." << endl;
                        } else if(y == '2') {
                            lighten(image);
                            cout << "The image has been lightened successfully." << endl;
                        }
                        break;
                    case 6:
                        Inverted(image);
                        cout << "The image colors have been inverted." << endl;
                        break;
                }
            }
        } else if (choice == 7) {
            if (!imageLoaded) {
                cout << "No image is loaded" << endl;
            } else {
                string newimagename;
                cout << "Enter the filename to save the image: ";
                cin >> newimagename;

                bool success = image.saveImage(newimagename); // Attempt to save the image
                if (success) {
                    cout << "Image saved successfully." << endl;
                } else {
                    cerr << "Failed to save the image! Please try again." << endl;
                }
            }
        } else if (choice == 8) {
            cout << "Exiting..." << endl;
            return 0; // Exit the program
        } else {
            cout << "Please enter a valid input" << endl; // Invalid input
        }
    }
}