#include <iostream>
#include <Image_Class.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string getChoice(vector <string> choices,const string &menu, const string &errorMsg);
Image grayscale(Image img);
Image BlacknWhite(Image img);
Image invert(Image img);
Image flip(Image img, const string &flipChoice);
Image rotate(Image img, const string &rotateChoice);
Image blur(Image& img);

int main() {
    string imgName;
    cout << "Enter Image name with extension\n";
    cin >> imgName;

    // Store the image
    Image img(imgName);
    Image newImg;


    string choice;
    vector <string> choices{"0", "1", "2", "3", "4", "5", "6", "7"};


    bool exit = false;
    while (!exit) {
        string menu = "Menu:\n1. Grayscale.\n2. Black and White.\n3. Invert Colors.\n4. Flip Image.\n5. Rotate Image.\n"
        "6. Blur\n0. Exit\nEnter your choice: ";
        choice = getChoice(choices, menu, "");

        if (choice == "1") {
            newImg = grayscale(img);
            cout << "Image turned into grayscale successfully!" << endl;
        } else if (choice == "2") {
            newImg = BlacknWhite(img);
            cout << "Image turned into Black and White successfully!" << endl;
        } else if (choice == "3") {
            newImg = invert(img);
            cout << "Image inverted successfully." << endl;
        } else if (choice == "4") {
            vector <string> flipChoices{"1", "2"};
            string flipMenu = "1. Flip image Horizontally.\n2. Flip image Vertically\nEnter your choice: ";
            string flipChoice = getChoice(flipChoices, flipMenu, "");
            newImg = flip(img, flipChoice);
            cout << "Image flipped successfully." << endl;
        } else if (choice == "5") {
            vector <string> rotateChoices{"90", "180", "270"};
            string rotateMenu = "Enter the degree of rotation(90, 180, 270): ";
            string rotateChoice = getChoice(rotateChoices, rotateMenu , "Please enter 90 or 180 or 270.");
            newImg = rotate(img, rotateChoice);
            cout << "Image rotated successfully." << endl;
        }else if (choice == "6") {
            newImg = blur(img);
            cout << "Image blurred successfully." << endl;
        } else if (choice == "0") {
            cout << "Exiting...\n";
            exit = true;
        }

    cout << "Enter new image name to be stored with it and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> imgName;
    newImg.saveImage(imgName);
    }

    return 0;
}

string getChoice(vector <string> choices,const string &menu, const string &errorMsg) {
    string choice;
    while (true) {
        cout << menu;
        getline(cin, choice);
        if (find(choices.begin(), choices.end(), choice) != choices.end()) {
            return choice;
        }
        else {
            if (!errorMsg.empty()) {
                cout << errorMsg << endl;
            } else {
                cout << "Invalid choice. Please enter a number between " + choices[0] + "and " + choices[choices.size() - 1] << endl;
            }
        }
    }
}

Image grayscale(Image img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            img(i, j, 0) = avg;
            img(i, j, 1) = avg;
            img(i, j, 2) = avg;
        }
    }

    return img;
}

Image BlacknWhite(Image img) {
    const int THRESHOLD = 127;
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // If the average is greater than or equal the THRESHOLD(127) turn the pixel black else turn the pixel white
            if (avg <= THRESHOLD) {
                img(i, j, 0) = 0;
                img(i, j, 1) = 0;
                img(i, j, 2) = 0;
            }
            else {
                img(i, j, 0) = 255;
                img(i, j, 1) = 255;
                img(i, j, 2) = 255;
            }
        }
    }

    return img;
}

Image invert(Image img)
{
    for (int i = 0; i < img.width; i++)
    { // Loop through the width of the image
        for (int j = 0; j < img.height; j++)
        { // Loop through the height of the image
            for (int s = 0; s < 3; s++)
            {                                       
                img(i, j, s) = 255 - img(i, j, s); // Invert the color value
            }
        }
    }

    return img;
}

Image flip(Image img, const string &flipChoice) {
    Image newImg;
    if (flipChoice == "1") {
        for (int i = 0; i < img.height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                for (int k = 0; k < 3; ++k)
                {
                    newImg(i, j, k) = img(i, img.width - j - 1, k); // flip horizontally
                }
            }
        }
    }
    else if (flipChoice == "2") {
        for (int i = 0; i < img.height; i++)
        {
            for (int j = 0; j < img.width; j++)
            {
                for (int k = 0; k < 3; ++k)
                {
                    newImg(i, j, k) = img(img.height - i - 1, j, k); // flip vertically
                }
            }
        }
    }
    return newImg;
}

Image rotate(const Image &img, const string &rotateChoice) {
    Image newImg;
    if (rotateChoice == "90") {
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
        img88 = flip(img1, "1");

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
        img3 = flip(img22, "1");

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
        newImg = img7;
    } else if (rotateChoice == "180") {
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
        newImg = imgg5;
    } else if (rotateChoice == "270") {
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
        newImg = imgg2;
    }

    return newImg;
}

// Function to blur the image
Image blur(Image& img) {
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

    // returning the blurred image
    return imgg3;
}