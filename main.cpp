
/*
================================================================================
 A1
Program: Baby Photoshop - Image Processing Tool (Part 1)
Course: CS213 - Object Oriented Programming (OOP)
Year: 2025-2026, First Semester
Section: 7
 Cairo University
Faculty of Computer and Artificial Intelligence - FCAI
================================================================================
Team Members:

1. Name: Ibrahim Eltahir Ibrahim
   ID: 20230738
   Filters: 1 (Grayscale), 4 (Merge)

2. Name: Maab Elfadil musa
   ID: 20243034
   Filters: 2 (Black & White), 5 (Flip)

3. Name: Mozn Elfadil musa
   ID: 20243036
   Filters: 3 (Invert), 6 (Rotate)
=================================================================================
File Information:
- Version: 1.0 (Part 1 - 6 Filters)
- Last Modified: 1 of October
- Instructor: Dr. Mohammad El-Ramly
================================================================================
*/

#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

 // Functions :

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool hasValidExtension(const string& filename) {
    size_t dotPos = filename.find_last_of(".");
    if (dotPos == string::npos) return false;

    string ext = filename.substr(dotPos);
    return (ext == ".jpg" || ext == ".jpeg" || ext == ".png" ||
            ext == ".bmp" || ext == ".JPG"  || ext == ".JPEG" ||
            ext == ".PNG" || ext == ".BMP");
}

bool askToSave() {
    char choice;
    cout << "\nDo you want to save the current image? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

// Filters :

//  1: Grayscale (IBRAHIM)
void applyGrayscale(Image &image) {
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            int gray = (r + g + b) / 3;
            image(x, y, 0) = gray;
            image(x, y, 1) = gray;
            image(x, y, 2) = gray;
        }
    }
    cout << "Grayscale filter applied successfully!\n";
}


//  Black & White (MAAB) - UPDATED

void applyBlackWhite(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg /= 3;
            unsigned char value = (avg > 127) ? 255 : 0;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = value;
            }
        }
    }
    cout << "Black & White filter applied successfully!\n";
}

//  Invert Colors (MOZN)

void applyInvert(Image &image) {
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            image(x, y, 0) = 255 - image(x, y, 0);
            image(x, y, 1) = 255 - image(x, y, 1);
            image(x, y, 2) = 255 - image(x, y, 2);
        }
    }
    cout << "Invert filter applied successfully!\n";
}

//  Merge Images (IBRAHIM)
void applyMerge(Image &image) {
    string secondFile;
    cout << "Enter second image filename: ";
    cin >> secondFile;

    if (!fileExists(secondFile)) {
        cout << "Error: Second image file does not exist!\n";
        return;
    }

    Image img2(secondFile);

    int newWidth = min(image.width, img2.width);
    int newHeight = min(image.height, img2.height);

    for (int x = 0; x < newWidth; x++) {
        for (int y = 0; y < newHeight; y++) {
            image(x, y, 0) = (image(x, y, 0) + img2(x, y, 0)) / 2;
            image(x, y, 1) = (image(x, y, 1) + img2(x, y, 1)) / 2;
            image(x, y, 2) = (image(x, y, 2) + img2(x, y, 2)) / 2;
        }
    }
    cout << "Merge filter applied successfully!\n";
}

//  : Flip Image (MAAB) - UPDATED
void applyFlip(Image &image) {
    char direction;

    cout << "If you want to Flip Horizontal Press ( H ) or ( V ) If you want Vertical? ";
    cin >> direction;

    Image flippedImage(image.width, image.height);

    if (direction == 'h' || direction == 'H') {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    flippedImage(image.width - 1 - i, j, k) = image(i, j, k);
                }
            }
        }
        cout << "Image flipped horizontally!\n";

    } else if (direction == 'v' || direction == 'V') {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    flippedImage(i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
        cout << "Image flipped vertically!\n";
    } else {
        cout << "Invalid flip direction!\n";
    }

    image = flippedImage;
}

// Rotate Image (MOZN)
void applyRotate(Image &image){
    int angle;
    cout << "Rotate Options: 90 / 180 / 270\nEnter angle: ";
    cin >> angle;

    if (angle == 90) {
        Image rotated(image.height, image.width);
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int c = 0; c < 3; c++) {
                    rotated(image.height - 1 - y, x, c) = image(x, y, c);
                }
            }
        }
        image = rotated;
        cout << "Rotated 90 degrees!\n";
    }

    else if (angle == 180) {
        Image rotated(image.width, image.height);
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int c = 0; c < 3; c++) {
                    rotated(image.width - 1 - x, image.height - 1 - y, c) = image(x, y, c);
                }
            }
        }
        image = rotated;
        cout << "Rotated 180 degrees!\n";
    }
    else if (angle == 270) {
        Image rotated(image.height, image.width);
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int c = 0; c < 3; c++) {
                    rotated(y, image.width - 1 - x, c) = image(x, y, c);
                }
            }
        }
        image = rotated;
        cout << "Rotated 270 degrees!\n";
    }
    else {
        cout << "Invalid rotation angle!\n";
    }
}

// البرنامج

int main() {
    string filename;
    string currentFilename;
    int choice;
    Image image;
    bool imageLoaded = false;
    bool imageModified = false;

    cout << "===============================================\n";
    cout << "     Baby Photoshop - Image Processing Tool   \n";
    cout << "           CS213 - Section 7                  \n";
    cout << "===============================================\n\n";

    // Initial image loading
    while (!imageLoaded) {
        cout << "Enter image filename to load: ";
        cin >> filename;

        if (!fileExists(filename)) {
            cout << "Error: File does not exist! Please try again.\n\n";
            continue;
        }

        if (!hasValidExtension(filename)) {
            cout << "Error: Invalid file format! Supported formats: jpg, jpeg, png, bmp\n\n";
            continue;
        }

        try {
            image = Image(filename);
            currentFilename = filename;
            imageLoaded = true;
            imageModified = false;
            cout << "\nImage loaded successfully!\n";
            cout << "Size: " << image.width << "x" << image.height << " pixels\n\n";
        } catch (const exception& e) {
            cout << "Error loading image: " << e.what() << "\n\n";
        }
    }

// Main menu loop
    do {
        cout << "\n============= MAIN MENU =============\n";
        cout << "1. Load new image\n";
        cout << "2. Grayscale Filter\n";
        cout << "3. Black & White Filter\n";
        cout << "4. Invert Filter\n";
        cout << "5. Merge Filter\n";
        cout << "6. Flip Filter\n";
        cout << "7. Rotate Filter\n";
        cout << "8. Save current image\n";
        cout << "9. Exit\n";
        cout << "=====================================\n";
        cout << "Choose option (1-9): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Ask to save before loading new image
                if (imageModified && askToSave()) {
                    cout << "Enter filename to save: ";
                    cin >> filename;
                    image.saveImage(filename);
                    cout << "Image saved successfully!\n";
                }

                cout << "Enter new image filename: ";
                cin >> filename;

                if (!fileExists(filename)) {
                    cout << "Error: File does not exist!\n";
                    break;
                }

                if (!hasValidExtension(filename)) {
                    cout << "Error: Invalid file format!\n";
                    break;
                }

                image = Image(filename);
                currentFilename = filename;
                imageModified = false;
                cout << "New image loaded successfully!\n";
                cout << "Size: " << image.width << "x" << image.height << " pixels\n";
                break;
            }

            case 2:
                applyGrayscale(image);
                imageModified = true;
                break;

            case 3:
                applyBlackWhite(image);
                imageModified = true;
                break;

            case 4:
                applyInvert(image);
                imageModified = true;
                break;

            case 5:
                applyMerge(image);
                imageModified = true;
                break;

            case 6:
                applyFlip(image);
                imageModified = true;
                break;

            case 7:
                applyRotate(image);
                imageModified = true;
                break;

            case 8: {
                int saveOption;
                cout << "\nSave Options:\n";
                cout << "1. Save with current filename (" << currentFilename << ")\n";
                cout << "2. Save with new filename\n";
                cout << "Choose: ";
                cin >> saveOption;

                if (saveOption == 2) {
                    cout << "Enter new filename: ";
                    cin >> filename;
                    currentFilename = filename;
                } else {
                    filename = currentFilename;
                }

                if (!hasValidExtension(filename)) {
                    cout << "Error: Invalid file format! Use .jpg, .jpeg, .png, or .bmp\n";
                    break;
                }

                image.saveImage(filename);
                imageModified = false;
                cout << "Image saved successfully as: " << filename << "\n";
                break;
            }

            case 9:
                // Ask to save before exit
                if (imageModified && askToSave()) {
                    cout << "Enter filename to save: ";
                    cin >> filename;
                    if (hasValidExtension(filename)) {
                        image.saveImage(filename);
                        cout << "Image saved successfully!\n";
                    }
                }
                cout << "\nThank you for using Baby Photoshop!\n";
                cout << "Developed by Section 7 Team\n";
                cout << "CS213 - FCAI Cairo University\n";
                break;

            default:
                cout << "Invalid choice! Please choose 1-9.\n";
                break;
        }

    } while (choice != 9);

return 0;
}
