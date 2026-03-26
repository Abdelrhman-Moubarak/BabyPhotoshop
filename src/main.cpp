#include "filters.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Image image;
    Image filtered_image;
    bool imageLoaded = false;

    while (true) {
        cout << "\nMenu Options:" << endl;
        cout << "A.  Load a new image" << endl;
        cout << "1.  Grayscale" << endl;
        cout << "2.  Black & White" << endl;
        cout << "3.  Invert" << endl;
        cout << "4.  Merge" << endl;
        cout << "5.  Flip" << endl;
        cout << "6.  Rotate" << endl;
        cout << "7.  Darken & Lighten" << endl;
        cout << "8.  Crop" << endl;
        cout << "9.  Frame" << endl;
        cout << "10. Detect Edges" << endl;
        cout << "11. Resize" << endl;
        cout << "12. Blur" << endl;
        cout << "13. Warm Tone" << endl;
        cout << "14. Purple Tint" << endl;
        cout << "15. Scan Lines" << endl;
        cout << "16. Save the image" << endl;
        cout << "17. Exit" << endl;
        cout << "Enter your choice: ";

        string choice;
        cin >> choice;

        if (choice == "A") {
            string image_name;
            cout << "Enter the name of the image to load: ";
            cin >> image_name;
            if (image.loadNewImage(image_name)) {
                filtered_image = image;
                imageLoaded = true;
                cout << "Image loaded successfully." << endl;
            } else {
                cout << "Failed to load the image. Please try again." << endl;
            }

        } else if (choice == "1") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Grayscale(image); cout << "Grayscale applied." << endl; }

        } else if (choice == "2") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Black_White(image); cout << "Black & White applied." << endl; }

        } else if (choice == "3") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Inverted(image); cout << "Invert applied." << endl; }

        } else if (choice == "4") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else {
                string filename2;
                cout << "Enter the name of the second image: ";
                cin >> filename2;
                filtered_image = MergeImages(image, filename2);
                cout << "Images merged." << endl;
            }

        } else if (choice == "5") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else {
                cout << "1. Flip Vertically" << endl;
                cout << "2. Flip Horizontally" << endl;
                char x; cin >> x;
                if (x == '1') { filtered_image = Flip_Vertically(image); cout << "Flipped vertically." << endl; }
                else if (x == '2') { filtered_image = Flip_Horizontally(image); cout << "Flipped horizontally." << endl; }
            }

        } else if (choice == "6") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else {
                cout << "1. Rotate 90" << endl;
                cout << "2. Rotate 180" << endl;
                cout << "3. Rotate 270" << endl;
                char x; cin >> x;
                if (x == '1') { filtered_image = Rotate90(image); cout << "Rotated 90 degrees." << endl; }
                else if (x == '2') { filtered_image = Rotate180(image); cout << "Rotated 180 degrees." << endl; }
                else if (x == '3') { filtered_image = Rotate270(image); cout << "Rotated 270 degrees." << endl; }
            }

        } else if (choice == "7") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else {
                cout << "1. Darken" << endl;
                cout << "2. Lighten" << endl;
                char y; cin >> y;
                if (y == '1') { filtered_image = Darken(image); cout << "Image darkened." << endl; }
                else if (y == '2') { filtered_image = lighten(image); cout << "Image lightened." << endl; }
            }

        } else if (choice == "8") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Crop(image); cout << "Image cropped." << endl; }

        } else if (choice == "9") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Frame(image); cout << "Frame added." << endl; }

        } else if (choice == "10") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Edges(image); cout << "Edge detection applied." << endl; }

        } else if (choice == "11") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Resize(image); cout << "Image resized." << endl; }

        } else if (choice == "12") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = Blur(image); cout << "Blur applied." << endl; }

        } else if (choice == "13") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = WarmTone(image); cout << "Warm Tone applied." << endl; }

        } else if (choice == "14") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = PurpleTint(image); cout << "Purple Tint applied." << endl; }

        } else if (choice == "15") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else { filtered_image = ScanLines(image); cout << "Scan Lines applied." << endl; }

        } else if (choice == "16") {
            if (!imageLoaded) { cout << "No image loaded." << endl; }
            else {
                string filename;
                cout << "Enter filename to save (e.g. output.jpg): ";
                cin >> filename;
                if (filtered_image.saveImage(filename)) {
                    cout << "Image saved successfully." << endl;
                } else {
                    cerr << "Failed to save the image." << endl;
                }
            }

        } else if (choice == "17") {
            cout << "Exiting..." << endl;
            return 0;

        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}
