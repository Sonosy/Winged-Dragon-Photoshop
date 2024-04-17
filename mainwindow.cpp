#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Image_Class.h"
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}






Image save;
string name;

string result ;
string result2;

void MainWindow::on_path_editingFinished()
{
    QString Qpath = ui->path->text();

    string path = Qpath.toStdString();
    for (char c : path) {
        if (c == '\\') {
            result += "\\\\";
        } else {
            result += c;
        }

    }

    // result = '\\' + result +'\\';
    // cout << result.substr(1,result.length()-1);



    // Load the image using QPixmap


    // Set the pixmap on the QLabel



}


void MainWindow::on_Rotate180Btn_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    int radius = 5; // Half of the diameter
    int diameter = radius * 2 + 1;
    const int area = diameter * diameter;

    Image blurredImg(img.width - diameter + 1, img.height - diameter + 1);

    for (int y = radius; y < img.height - radius; ++y) {
        for (int x = radius; x < img.width - radius; ++x) {
            int RR = 0, GG = 0, BB = 0;

            // Calculate sum for the initial window
            for (int j = -radius; j <= radius; ++j) {
                for (int i = -radius; i <= radius; ++i) {
                    RR += img(x + i, y + j, 0);
                    GG += img(x + i, y + j, 1);
                    BB += img(x + i, y + j, 2);
                }
            }

            // Set the average color value for the pixel
            blurredImg(x - radius, y - radius, 0) = RR / area;
            blurredImg(x - radius, y - radius, 1) = GG / area;
            blurredImg(x - radius, y - radius, 2) = BB / area;
        }
    }


    blurredImg.saveImage("blur.jpg");


    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("blur.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layout->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layout);



}


void MainWindow::on_InvertBtn_clicked()
{


    Image imgSource(result);
    Image imgg(imgSource);
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
    imgg.saveImage("Invert.jpg"); // Save the inverted image with a prefix '1' added to its name


    // Set alignment of the label

    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Invert.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_clear_clicked()
{
    QLayout* layout = ui->widget->layout();
    if (layout != 0)
    {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != 0)
            layout->removeItem (item);
        delete layout;
    }

}





void MainWindow::on_load_clicked()
{
    Image defImg(result);
    QLabel *imageLabel = new QLabel(this);

    defImg.saveImage("l.jpg");
    // Load the image using QPixmap
    QPixmap pixmap("l.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layout->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget_2->setLayout(layout);

}


void MainWindow::on_GrayScale_clicked()
{
    Image GreyScale(result);
    for (int i = 0, width = GreyScale.width; i < width; ++i){
        for (int j = 0, height = GreyScale.height; j < height; ++j){
            unsigned int avg = 0;
            for (int k = 0, channels = GreyScale.channels; k < channels; ++k){
                avg += GreyScale(i, j, k);
            }
            avg /= 3;
            for (int k = 0, channels = GreyScale.channels; k < channels; ++k){
                GreyScale(i, j, k) = avg;
            }
        }
    }

    GreyScale.saveImage("Gray.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Gray.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_FancyFarme_clicked()
{
    int frameSize = 50;
    int dotSpacing = 5;
    Image imgSource(result);
    Image img(imgSource);


    Image framedImg(img.width + 100, img.height + 100);

    // Draw the frame
    for (int i = 0; i < framedImg.width; i++)
    {
        for (int j = 0; j < framedImg.height; j++)
        {
            // Check if current pixel is within the frame border
            if (i < frameSize || i >= framedImg.width - frameSize || j < frameSize || j >= framedImg.height - frameSize)
            {
                // Make the frame pixels dotted
                if ((i + j) % (2 * dotSpacing) == 0 || (i - j) % (2 * dotSpacing) == 0)
                {
                    for (int s = 0; s < img.channels; s++)
                    {
                        framedImg(i, j, s) = 0; // Set this value to change the color of the dots
                    }
                }
                else
                {
                    for (int s = 0; s < img.channels; s++)
                    {
                        framedImg(i, j, s) = 255; // Set this value to change the background color of the frame
                    }
                }
            }
            else
            {
                // Set the original image pixels
                for (int s = 0; s < img.channels; s++)
                {
                    framedImg(i, j, s) = img(i - frameSize, j - frameSize, s);
                }
            }
        }
    }


    framedImg.saveImage("FramedImg.jpg");


    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("FramedImg.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);

}


void MainWindow::on_Frame_clicked()
{

    Image imgSource(result);
    Image img(imgSource);
    int frameSize = 50;



    Image framedImg(img.width + 100, img.height + 100);

    // Draw the frame
    for (int i = 0; i < framedImg.width; i++)
    {
        for (int j = 0; j < framedImg.height; j++)
        {
            // Check if current pixel is within the frame border
            if (i < frameSize || i >= framedImg.width - frameSize || j < frameSize || j >= framedImg.height - frameSize)
            {
                for (int s = 0; s <= 1; s++)
                {
                    framedImg(i, j, s) = 0; // Set this value to change the background color of the frame
                }
                for (int s = 2; s <=2 ; s++)
                {
                    framedImg(i, j, s) = 255; // Set this value to change the background color of the frame
                }


            }
            else
            {
                // Set the original image pixels
                for (int s = 0; s < img.channels; s++)
                {
                    framedImg(i, j, s) = img(i - frameSize, j - frameSize, s);
                }
            }
        }
    }

    // Save the framed image


    framedImg.saveImage("Frame.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Frame.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);

}


void MainWindow::on_Rotate180Btn_5_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
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
    Image infra(imgg);
    for (int i = 0, width = infra.width; i < width; ++i){
        for (int j = 0, height = infra.height; j < height; ++j){


            infra(i, j, 0) = 255;

        }
    }


    infra.saveImage("Infra.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Infra.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);

}





void MainWindow::on_purple_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image purple(img);


    for (int i = 0, width = purple.width; i < width; ++i){
        for (int j = 0, height = purple.height; j < height; ++j){


            purple(i, j, 0) = min(255,  purple(i, j, 0) + 30);

            purple(i, j, 2) = min(255,  purple(i, j, 2) + 50);

        }
    }


    purple.saveImage("purple.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("purple.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);

}


void MainWindow::on_yellow_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image yellow(img);


    for (int i = 0, width = yellow.width; i < width; ++i){
        for (int j = 0, height = yellow.height; j < height; ++j){



            yellow(i, j, 0) = min(255, yellow(i, j, 0)  + 30); // Increase red for warmth and brightness
            yellow(i, j, 1) = min(255, yellow(i, j, 1) + 20); // Increase green for warmth and brightness
            yellow(i, j, 2) = max(0, yellow(i, j, 2) - 10);

        }
    }


    yellow.saveImage("yellow.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("yellow.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_Oil_panting_clicked()

{
    Image imgSource(result);
    Image img(imgSource);
    Image newImg(img.width, img.height);

    const int RADIUS = 2;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; ++j) {
            int cColor[3];
            int maxCount[3] = {0, 0, 0};
            for (int ii = i - RADIUS; ii < i + RADIUS; ++ii) {
                if (ii >= 0 && ii < img.width) {
                    for (int jj = j - RADIUS; jj < j + RADIUS; ++jj) {
                        // Checking if the pixel is within the image
                        if (jj >= 0 && jj < img.height) {
                            int countColor[3] = {0, 0, 0};
                            for (int iii = i - RADIUS; iii < i + RADIUS; ++iii) {
                                if (iii >= 0 && iii < img.width) {
                                    for (int jjj = j - RADIUS; jjj < j + RADIUS; ++jjj) {
                                        // Checking if the pixel is within the image
                                        if (jjj >= 0 && jjj < img.height) {
                                            for (int k = 0; k < 3; k++) {
                                                if (img(ii, jj, k) == img(iii, jjj, k)) {
                                                    countColor[k]++;
                                                }

                                                if (countColor[k] > maxCount[k]) {
                                                    maxCount[k] = countColor[k];
                                                    cColor[k] = img(ii, jj, k);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            newImg(i, j, 0) = cColor[0];
            newImg(i, j, 1) = cColor[1];
            newImg(i, j, 2) = cColor[2];
        }
    }

    //    cout << "Pls enter image name to store new image\n";
    //    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    //    cin >> filename;
    newImg.saveImage("Oil.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Oil.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_balck_white_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
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

    img.saveImage("blackwhite.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("blackwhite.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}





void MainWindow::on_Flip_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image newImg(img.width, img.height);



    // Flip the image Horizontally
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                newImg(i, j, k) = img(img.width - 1 - i , j, k); // Flip the image
            }
        }
    }

    newImg.saveImage("flipHorizontally.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("flipHorizontally.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);


}


void MainWindow::on_Flip_v_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image newImg(img.width, img.height);
    // Flip the image Vertically
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                newImg(i, j, k) = img(i , img.height - 1 - j, k); // Flip the image
            }
        }
    }
    newImg.saveImage("flipVertically.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("flipVertically.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);

}




void MainWindow::on_Rotate_90_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image newImg(img.height, img.width);

    // Rotate the image 90 degrees
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                newImg(j, i, k) = img(i , img.height - 1 - j, k); // Perform rotation
            }
        }
    }
    newImg.saveImage("Rotate_90.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Rotate_90.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}



void MainWindow::on_Rotate_180_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image newImg(img.width, img.height);

    // Rotate the image 180 degrees
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                newImg(i, j, k) = img(img.width - 1 - i , img.height - 1 - j, k); // Perform rotation
            }
        }
    }
    newImg.saveImage("Rotate_180.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Rotate_180.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_Rotate_270_clicked()
{
    Image imgSource(result);
    Image img(imgSource);

    Image newImg(img.height, img.width);

    // Rotate the image 270 degrees
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                newImg(j, i, k) = img(img.width - 1 - i , j, k); // Perform rotation
            }
        }
    }

    newImg.saveImage("Rotate_270.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Rotate_270.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}
int X , Y , W , H;

void MainWindow::on_Crop_clicked()
{
    int x, y, w, h;
    x = 100;
    y = 100;
    w = 100;
    h = 100;

    Image imgSource(result);
    Image img(imgSource);

    Image newImg(w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                newImg(i, j, k) = img(i + x, j + y, k);
            }
        }
    }


    newImg.saveImage("Crop.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Crop.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}





void MainWindow::on_Merge_clicked()
{
    Image imgSource(result);
    Image image1(imgSource);
    Image imgSource2(result2);
    Image image2(imgSource2);
    int greaterWidth = 0;
    int greaterHeight = 0;

    if ((image1.height >= image2.height)){  // TO CHECK WHICH IMAGE IS LARGER
        greaterHeight = image1.height;
    }
    else{
        greaterHeight = image2.height;
    }
    if (image1.width >= image2.width){
        greaterWidth = image1.width;
    }
    else{
        greaterWidth = image2.width;
    }

    //Resize the 2 images in different variables of object Image

    Image image1Resized(greaterWidth, greaterHeight);
    double widthCoefficient = (double) image1.width / greaterWidth; // Resizing Variables for Image 1
    double heightCoefficient = (double) image1.height / greaterHeight; // Resizing Variables for Image 1
    for (int i = 0; i < greaterWidth; ++i){
        for (int j = 0; j < greaterHeight; ++j){
            int originalX = round(i * widthCoefficient);
            int originalY = round(j * heightCoefficient);
            for (int k = 0, channels = image1.channels; k < channels; ++k){
                image1Resized(i, j, k) = image1(originalX, originalY, k);
            }
        }
    }

    Image image2Resized(greaterWidth, greaterHeight);
    widthCoefficient = (double) image2.width / greaterWidth; // Resizing Variables for Image 1
    heightCoefficient = (double) image2.height / greaterHeight; // Resizing Variables for Image 1
    for (int i = 0; i < greaterWidth; ++i){
        for (int j = 0; j < greaterHeight; ++j){
            int originalX = round(i * widthCoefficient);
            int originalY = round(j * heightCoefficient);
            for (int k = 0, channels = image2.channels; k < channels; ++k){
                image2Resized(i, j, k) = image2(originalX, originalY, k);
            }
        }
    }


    Image result(greaterWidth, greaterHeight);
    for (int i = 0; i < greaterWidth; ++i){
        for (int j = 0; j < greaterHeight; ++j){
            for (int k = 0, channels = image1.channels; k < channels; ++k){
                unsigned int averagePixelColor = (image1Resized(i, j, k) + image2Resized(i, j, k)) / 2;
                result(i, j, k) = averagePixelColor;
            }
        }
    }


    result.saveImage("merge.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("merge.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_resize_clicked()
{


    Image imgSource(result);
    Image img(imgSource);
    Image resizedImage(1000, 1000);
    double widthCoefficient = (double) img.width / 1000; // Resizing Variables for Image 1
    double heightCoefficient = (double) img.height / 1000; // Resizing Variables for Image 1
    for (int i = 0; i < 1000; ++i){
        for (int j = 0; j < 1000; ++j){
            int originalX = round(i * widthCoefficient);
            int originalY = round(j * heightCoefficient);
            for (int k = 0, channels = img.channels; k < channels; ++k){
                resizedImage(i, j, k) = img(originalX, originalY, k);
            }
        }
    }
    resizedImage.saveImage("resized.jpg");

    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("resized.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);

}



void MainWindow::on_path_2_editingFinished()
{
    QString Qpath = ui->path_2->text();

    string path = Qpath.toStdString();
    for (char c : path) {
        if (c == '\\') {
            result2 += "\\\\";
        } else {
            result2 += c;
        }

    }
}


void MainWindow::on_edge_detect_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    Image BlackAndWhite = img;
    const int THRESHOLD = 127;
    for (int i = 0; i < BlackAndWhite.width; ++i) {
        for (int j = 0; j < BlackAndWhite.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += BlackAndWhite(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // If the average is greater than or equal the THRESHOLD(127) turn the pixel black else turn the pixel white
            if (avg <= THRESHOLD) {
                BlackAndWhite(i, j, 0) = 0;
                BlackAndWhite(i, j, 1) = 0;
                BlackAndWhite(i, j, 2) = 0;
            }
            else {
                BlackAndWhite(i, j, 0) = 255;
                BlackAndWhite(i, j, 1) = 255;
                BlackAndWhite(i, j, 2) = 255;
            }
        }
    }
    int width = BlackAndWhite.width;
    int height = BlackAndWhite.height;

    // Loop through each pixel
    for (int i = 0; i < width; ++i) {
        bool inEdge = false; // Flag to track if we're inside an edge
        for (int j = 0; j < height - 1; ++j) { // Adjusted loop boundary
            // Check if current pixel is black
            if (BlackAndWhite(i, j, 0) == 0 && BlackAndWhite(i, j, 1) == 0 && BlackAndWhite(i, j, 2) == 0) {
                if (!inEdge) {
                    inEdge = true; // Start of a new edge
                } else {
                    // Continue the edge, make next pixel white
                    BlackAndWhite(i, j, 0) = 255;
                    BlackAndWhite(i, j, 1) = 255;
                    BlackAndWhite(i, j, 2) = 255;
                }
            } else { // Current pixel is white
                if (inEdge) {
                    // End of the edge, make previous pixel black
                    BlackAndWhite(i, j-1, 0) = 0;
                    BlackAndWhite(i, j-1, 1) = 0;
                    BlackAndWhite(i, j-1, 2) = 0;
                    inEdge = false; // Reset the flag
                }
            }
        }

        // Handle edge case: if the last pixel in the row is black
        if (inEdge) {
            BlackAndWhite(i, height-1, 0) = 0;
            BlackAndWhite(i, height-1, 1) = 0;
            BlackAndWhite(i, height-1, 2) = 0;
        }
    }

    BlackAndWhite.saveImage("Edge_detection.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Edge_detection.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}

int choice;
void MainWindow::on_brightness_clicked()
{
    // QString Qpath = ui->path_2->text();

    // choice = Qpath.toInt();

    Image imgSource(result);
    Image img(imgSource);
    for (int i = 0, width = img.width; i < width; ++i){
        for (int j = 0, height = img.height; j < height; ++j){
            for (int k = 0; k < 3; ++k){
                int newValue = img(i, j, k) + (double)(70) * (double)img(i, j, k) / (double)100;
                img(i, j, k) = (newValue > 255)? 255: newValue;
            }
        }
    }


    img.saveImage("brightness.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("brightness.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_Darkness_clicked()
{

    Image imgSource(result);
    Image img(imgSource);



    for (int i = 0, width = img.width; i < width; ++i){
        for (int j = 0, height = img.height; j < height; ++j){
            for (int k = 0; k < 3; ++k){
                img(i, j, k) -= (double)(50) * (double)img(i, j, k) / (double)100;
            }
        }
    }

    //    cout << "Pls enter image name to store new image\n";
    //    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    //    cin >> filename;


    img.saveImage("Darkness.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Darkness.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_skew40_clicked()
{

    Image imgSource(result);
    Image img(imgSource);
    double skewRadians = 40 * M_PI / 180.0;

    // Calculate dimensions of output image
    int newWidth = static_cast<int>(img.width + abs(img.height * tan(skewRadians)));
    int newHeight = img.height;
    Image output(newWidth, newHeight);

    // Loop through each pixel in the output image
    for (int j = 0; j < newHeight; j++) {
        for (int i = 0; i < newWidth; i++) {
            // Calculate corresponding position in the input image
            double ximg = i - (newHeight - j) * tan(skewRadians);
            int x0 = static_cast<int>(floor(ximg));
            int x1 = x0 + 1;
            double alpha = ximg - x0;

            // Initialize pixel value to transparent
            double top[3] = {0}; // Assuming 3 channels for simplicity

            // Check if pixel position is within input image boundaries
            if (x0 >= 0 && x0 < img.width && x1 >= 0 && x1 < img.width) {
                // Perform bilinear interpolation to get pixel value
                for (int k = 0; k < 3; k++) {
                    top[k] = (1 - alpha) * img(min(x0, img.width - 1), j, k)
                             + alpha * img(min(x1, img.width - 1), j, k);
                }
            } else {
                // Set pixel value to transparent
                for (int k = 0; k < 3; k++) {
                    top[k] = 0; // Transparent
                }
            }

            // Assign pixel value to output image
            for (int k = 0; k < 3; k++) {
                output(i, j, k) = top[k];
            }
        }
    }
    output.saveImage("skew.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("skew.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_noise_clicked()
{
    Image imgSource(result);
    Image img(imgSource);
    int INTENSITY = 25;
    srand(unsigned(time(0)));
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int newValue = img(i, j, k) + (rand() % (INTENSITY * 2 + 1)) - INTENSITY;
                if(newValue > 255) {
                    newValue = 255;
                } else if(newValue < 0) {
                    newValue = 0;
                }
                img(i, j, k) = newValue;
            }
        }
    }

    //    cout << "Pls enter image name to store new image\n";
    //    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    //    cin >> filename;
    img.saveImage("Noise.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("Noise.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_extra1_clicked()
{
    Image imgSource(result);
    Image img(imgSource);

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
                img(i, j, 2) = 0;
            }
            else {
                img(i, j, 0) = 255;
            }
        }
    }


    img.saveImage("extra.jpg");
    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("extra.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_extra2_clicked()
{
    Image imgSource(result);
    Image img(imgSource);


    Image infra(img);
    for (int i = 0, width = infra.width; i < width; ++i){
        for (int j = 0, height = infra.height; j < height; ++j){


            infra(i, j, 2) = 255;

        }
    }

    infra.saveImage("winter.jpg");



    QLabel *imageLabel = new QLabel(this);

    // Load the image using QPixmap
    QPixmap pixmap("winter.jpg");

    // Set the pixmap on the QLabel

    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    // Create a QVBoxLayout
    QVBoxLayout *layoutt = new QVBoxLayout(this);

    // Add the QLabel to the layout
    layoutt->addWidget(imageLabel);

    // Set the layout for your widget
    ui->widget->setLayout(layoutt);
}


void MainWindow::on_path_cursorPositionChanged(int arg1, int arg2)
{

}


void MainWindow::on_Save_clicked()
{
    // save.saveImage(name);
}

