#include <iostream>
#include "image_class.h" 
using namespace std;

// Function to blur the image
void blur(Image& img, const string& imgName) {
    // Creating a copy of the original image
    Image imgg2(img);

    // Creating a new image with smaller dimensions
    Image imgg3(imgg2.width - 50, imgg2.height - 50);

    // Setting the diameter of the blur filter
    int diameter = 25 * 2 + 1;
    const int area = diameter * diameter; // Calculating the area of the filter

    // Looping through the pixels of the image
    for (int i = 25; i < imgg2.width - 25; ++i) {
        for (int j = 25; j < imgg2.height - 25; ++j) {
            int RR = 0, GG = 0, BB = 0;

            // Applying the blur filter to each pixel
            for (int MI = -25; MI <= 25; ++MI) {
                for (int MJ = -25; MJ <= 25; ++MJ) {
                    int R = i + MI;
                    int C = j + MJ;
                    // Checking if the pixel is within the image 
                    if (R >= 0 && R < imgg2.width && C >= 0 && C < imgg2.height) {
                        RR += imgg2(R, C, 0);
                        GG += imgg2(R, C, 1);
                        BB += imgg2(R, C, 2);
                    }
                }
            }

            // Calculating the average color value for the pixel
            imgg2(i, j, 0) = RR / area;
            imgg2(i, j, 1) = GG / area;
            imgg2(i, j, 2) = BB / area;
        }
    }

    // Set the blurred region to a smaller image
    for (int i = 25; i < imgg2.width - 25; i++) {
        for (int j = 25; j < imgg2.height - 25; j++) {
            for (int s = 0; s < imgg2.channels; s++) {
                imgg3(i - 25, j - 25, s) = imgg2(i, j, s);
            }
        }
    }

    // Saving the blurred image with a modified name
    imgg3.saveImage("1" + imgName);
}


int main() {
    string img, imgName;
    cin >> img; // Taking input for the image file name
    imgName = img;
    Image image(img); // Creating an instance of the Image class with the given file name
    blur(image, imgName); // Blurring the image
    return 0;
}
