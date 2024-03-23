#include <iostream>
#include "image_class.h"
using namespace std;

Image FancyFrame(Image img, string imgName)
{
    for (int i = 50; i < 90; i++)
    {
        for (int j = 50; j < img.height - 50; j++)
        {

            img(i, j, 0) = 255;
            img(i, j, 1) = 255;
            img(i, j, 2) = 255;
        }
    }

    for (int i = 50; i < img.width - 50; i++)
    {
        for (int j = 50; j < 90; j++)
        {

            img(i, j, 0) = 255;
            img(i, j, 1) = 255;
            img(i, j, 2) = 255;
        }
    }

    for (int i = img.width - 50; i > (img.width - 50) - 40; --i)
    {
        for (int j = 50; j < img.height - 50; j++)
        {

            img(i, j, 0) = 255;
            img(i, j, 1) = 255;
            img(i, j, 2) = 255;
        }
    }

    for (int i = 50; i < img.width - 50; i++)
    {
        for (int j = img.height - 50; j > (img.height - 50) - 40; --j)
        {

            img(i, j, 0) = 255;
            img(i, j, 1) = 255;
            img(i, j, 2) = 255;
        }
    }

    img.saveImage("1" + imgName);
}

Image Frame(Image img, string imgName)
{

    Image imgg1(img.width + 50, img.height + 50);
    for (int i = 0; i < imgg1.width; i++)
    {
        for (int j = 0; j < imgg1.height; j++)
        {
            for (int s = 0; s < 1; s++)
            {
                imgg1(i, j, s) = 0;
            }
            for (int s = 2; s < 3; s++)
            {
                imgg1(i, j, s) = 255;
            }
        }
    }

    for (int i = 50; i < img.width; i++)
    {
        for (int j = 50; j < img.height; j++)
        {
            for (int s = 0; s < img.channels; s++)
            {
                imgg1(i, j, s) = img(i, j, s);
            }
        }
    }

    imgg1.saveImage("1" + imgName);

    return imgg1;
}
int main()
{
    string img, imgName;
    cin >> img;
    imgName = img;
    char cho;
    cout << "choose 1)Normal Frame 2)Fancy Farme\n";
    cin >> cho;
    if (cho == '1')
    {
        Frame(img, imgName);
    }
    else if (cho == '2')
    {
        Image FancyImg = Frame(img, imgName);
        FancyFrame(FancyImg, imgName);
    }
}
