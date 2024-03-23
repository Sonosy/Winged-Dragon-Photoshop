#include <iostream>
#include "image_class.h"
using namespace std;

// Function to invert the colors of an image
Image invert(Image img, string imgName)
{
    Image imgg(img); // Create a copy of the input image
    for (int i = 0; i < imgg.width; i++)
    { // Loop through the width of the image
        for (int j = 0; j < imgg.height; j++)
        { // Loop through the height of the image
            for (int s = 0; s < 3; s++)
            {                                        // Loop through the color channels (assuming RGB)
                imgg(i, j, s) = 255 - imgg(i, j, s); // Invert the color value
            }
        }
    }
    imgg.saveImage("1" + imgName); // Save the inverted image with a prefix '1' added to its name
}

// Main function
int main()
{
    string img, imgName;
    cin >> img;
    imgName = img;
    invert(img, imgName);
}