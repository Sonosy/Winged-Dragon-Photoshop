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




Image invert(Image img, string imgName)
{
    Image imgg(img); 
    for (int i = 0; i < imgg.width; i++)
    { // Loop through the width of the image
        for (int j = 0; j < imgg.height; j++)
        { // Loop through the height of the image
            for (int s = 0; s < 3; s++)
            {                                       
                imgg(i, j, s) = 255 - imgg(i, j, s); // Invert the color value
            }
        }
    }
    imgg.saveImage("1" + imgName);
}






// Function to rotate the image 180 degrees
Image Rotate180(Image img, string imgName)
{
    // Create copies of the input image with different dimensions
    Image imgg(img);
    Image imgg2(imgg.height, imgg.width);
    Image imgg3(imgg.width, imgg.height);
    Image imgg4(imgg3.height, imgg3.width);
    Image imgg5(imgg3.width, imgg3.height);

    // Rotate the image 180 degrees
    for (int i = 0; i < imgg.width; i++)
    {
        for (int j = 0; j < imgg.height; j++)
        {
            for (int s = 0; s < imgg.channels; s++)
            {
                imgg2(j, i, s) = imgg(i, j, s); // Perform rotation
            }
        }
    }

    // Reflect the rotated image horizontally
    for (int i = 0; i < imgg2.height; i++)
    {
        for (int j = 0; j < imgg2.width; j++)
        {
            for (int s = 0; s < imgg2.channels; s++)
            {
                imgg3(i, j, s) = imgg(i, imgg2.width - j - 1, s); // Reflect horizontally
            }
        }
    }

    // Rotate the reflected image 180 degrees again
    for (int i = 0; i < imgg.width; i++)
    {
        for (int j = 0; j < imgg.height; j++)
        {
            for (int s = 0; s < imgg.channels; s++)
            {
                imgg4(j, i, s) = imgg3(i, j, s); // Perform rotation
            }
        }
    }

    // Reflect the twice-rotated image horizontally
    for (int i = 0; i < imgg2.height; i++)
    {
        for (int j = 0; j < imgg2.width; j++)
        {
            for (int s = 0; s < imgg2.channels; s++)
            {
                imgg5(i, j, s) = imgg3(imgg2.height - i - 1, j, s); // Reflect horizontally
            }
        }
    }

    // Save the final rotated image
    imgg5.saveImage("1" + imgName);
}

// Function to rotate the image 90 degrees
Image Rotate90(Image img, string imgName)
{
    // Create copies of the input image with different dimensions
    Image img1(img);
    Image img77(img1.height, img1.width);
    Image img88(img1.width, img1.height);

    // Rotate the image 90 degrees
    for (int i = 0; i < img1.width; i++)
    {
        for (int j = 0; j < img1.height; j++)
        {
            for (int s = 0; s < img1.channels; s++)
            {
                img77(j, i, s) = img1(i, j, s); // Perform rotation
            }
        }
    }

    // Reflect the rotated image horizontally
    for (int i = 0; i < img77.height; i++)
    {
        for (int j = 0; j < img77.width; j++)
        {
            for (int s = 0; s < img77.channels; s++)
            {
                img88(i, j, s) = img1(img77.height - i - 1, j, s); // Reflect horizontally
            }
        }
    }

    // Rotate the reflected image 90 degrees again
    Image img22(img1.height, img1.width);
    for (int i = 0; i < img88.width; i++)
    {
        for (int j = 0; j < img88.height; j++)
        {
            for (int s = 0; s < img88.channels; s++)
            {
                img22(j, i, s) = img88(i, j, s); // Perform rotation
            }
        }
    }

    // Create another copy of the twice-rotated image
    Image img2(img22.height, img22.width);
    Image img3(img22.width, img22.height);

    // Rotate the twice-rotated image 90 degrees
    for (int i = 0; i < img22.width; i++)
    {
        for (int j = 0; j < img22.height; j++)
        {
            for (int s = 0; s < img22.channels; s++)
            {
                img2(j, i, s) = img22(i, j, s); // Perform rotation
            }
        }
    }

    // Reflect the twice-rotated image horizontally
    for (int i = 0; i < img2.height; i++)
    {
        for (int j = 0; j < img2.width; j++)
        {
            for (int s = 0; s < img2.channels; s++)
            {
                img3(i, j, s) = img22(i, img2.width - j - 1, s); // Reflect horizontally
            }
        }
    }

    // Create copies of the reflected image
    Image img4(img3.height, img3.width);
    Image img5(img3.width, img3.height);

    // Reflect the reflected image vertically
    for (int i = 0; i < img3.width; i++)
    {
        for (int j = 0; j < img3.height; j++)
        {
            for (int s = 0; s < img3.channels; s++)
            {
                img4(j, i, s) = img3(i, j, s); // Reflect vertically
            }
        }
    }

    // Rotate the vertically reflected image 90 degrees
    for (int i = 0; i < img4.height; i++)
    {
        for (int j = 0; j < img4.width; j++)
        {
            for (int s = 0; s < img4.channels; s++)
            {
                img5(i, j, s) = img22(img4.height - i - 1, j, s); // Perform rotation
            }
        }
    }

    // Create copies of the twice-reflected image
    Image img6(img5.height, img5.width);
    Image img7(img5.width, img5.height);

    // Reflect the twice-reflected image vertically
    for (int i = 0; i < img5.width; i++)
    {
        for (int j = 0; j < img5.height; j++)
        {
            for (int s = 0; s < img5.channels; s++)
            {
                img6(j, i, s) = img5(i, j, s); // Reflect vertically
            }
        }
    }

    // Rotate the twice-reflected image 90 degrees

    for (int i = 0; i < img6.height; i++)
    {
        for (int j = 0; j < img6.width; j++)
        {
            for (int s = 0; s < img6.channels; s++)
            {
                img7(i, j, s) = img5(i, img2.width - j - 1, s);
            }
        }
    }

    // Save the final rotated image
    img7.saveImage("1" + imgName);
}



// Function to rotate the image 270 degrees
Image Rotate270(Image img, string imgName)
{
    // Create copies of the input image with different dimensions
    Image imgg(img);
    Image imgg7(imgg.height, imgg.width);
    Image imgg8(imgg.width, imgg.height);

    // Rotate the image 90 degrees
    for (int i = 0; i < imgg.width; i++)
    {
        for (int j = 0; j < imgg.height; j++)
        {
            for (int s = 0; s < imgg.channels; s++)
            {
                imgg7(j, i, s) = imgg(i, j, s); // Rotate
            }
        }
    }

    // Reflect the rotated image horizontally
    for (int i = 0; i < imgg7.height; i++)
    {
        for (int j = 0; j < imgg7.width; j++)
        {
            for (int s = 0; s < imgg7.channels; s++)
            {
                imgg8(i, j, s) = imgg(imgg7.height - i - 1, j, s); 
            }
        }
    }

    // Create a copy of the reflected image
    Image imgg2(imgg.height, imgg.width);

    // Rotate the reflected image 90 degrees
    for (int i = 0; i < imgg8.width; i++)
    {
        for (int j = 0; j < imgg8.height; j++)
        {
            for (int s = 0; s < imgg8.channels; s++)
            {
                imgg2(j, i, s) = imgg8(i, j, s); // Rotate
            }
        }
    }

    // Save the final rotated image
    imgg2.saveImage("1" + imgName);
}




int main() {
    string imgName;
    cout << "Enter Image name with extention\n";
    cin >> imgName;

    // Store the image
    Image img(imgName);


    int choice , s;
    s = 0;
    while ( s == 0) {
        cout << "Menu:\n";
        cout << "1. Rotate 90 degrees\n";
        cout << "2. Rotate 180 degrees\n";
        cout << "3. Rotate 270 degrees\n";
        cout << "4. Invert\n";
        cout << "5. Blur\n";
        cout << "6. Exit\n"; 
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
             Rotate90(img, imgName);
            cout << "Image rotated 90 degrees successfully.\n";
        } else if (choice == 2) {
            Rotate180(img, imgName);
            cout << "Image rotated 180 degrees successfully.\n";
        } else if (choice == 3) {
            Rotate270(img, imgName);
            cout << "Image rotated 270 degrees successfully.\n";
        } else if (choice == 4) {
            invert(img, imgName);
            cout << "Image inverted successfully.\n";
        } else if (choice == 5) {
            blur(img, imgName);
            cout << "Image blurred successfully.\n";
        } else if (choice == 6) {
            cout << "Exiting...\n";
            s = 1;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
    return 0;
}


