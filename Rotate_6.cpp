#include <iostream>
#include "image_class.h"
using namespace std;

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
                imgg2(j, i, s) = imgg(i, j, s);
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
                imgg3(i, j, s) = imgg(i, imgg2.width - j - 1, s);
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
                imgg4(j, i, s) = imgg3(i, j, s);
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
                imgg5(i, j, s) = imgg3(imgg2.height - i - 1, j, s);
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
                img77(j, i, s) = img1(i, j, s);
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
                img88(i, j, s) = img1(img77.height - i - 1, j, s);
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
                img22(j, i, s) = img88(i, j, s);
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
                img2(j, i, s) = img22(i, j, s);
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
                img3(i, j, s) = img22(i, img2.width - j - 1, s);
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
                img4(j, i, s) = img3(i, j, s);
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
                img5(i, j, s) = img22(img4.height - i - 1, j, s);
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
                img6(j, i, s) = img5(i, j, s);
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

    // This code to get the reflection of the Image

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
                imgg7(j, i, s) = imgg(i, j, s);
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
                imgg2(j, i, s) = imgg8(i, j, s);
            }
        }
    }

    // Save the final rotated image
    imgg2.saveImage("1" + imgName);
}

int main()
{
    string img, imgName;
    cout << "enter image name";
    cin >> img;
    imgName = img;
    char cho;
    cout << "enter the degree you want\n1)Rotate 90 2)Rotate 180 3)Rotate 270\n";
    if (cho == '1')
    {
        Rotate90(img, imgName);
    }
    else if (cho == '2')
    {
        Rotate180(img, imgName);
    }
    else if (cho == '3')
    {
        Rotate270(img, imgName);
    }
}
