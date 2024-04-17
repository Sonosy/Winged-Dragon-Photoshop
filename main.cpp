#include "mainwindow.h"
#include <QGuiApplication>
#include <QApplication>
#include "ui_mainwindow.h"


// FCAI – Structured Programming – 2024 - Assignment 3
// Program Name: CS112_A3_Part3_S5_20230045_20230207_20231137.cpp
// Last Modification Date: 18/04/2024
// Author1: Adham Ghallab  ID: 20230045
// Author2: Abdelrahman Sonosy  ID: 20230207
// Author3: Mohamed Ayman Fayz  ID: 20231137
// Who did what: Adham Ghallab (20230045) -> GreryScale ,Edge detection , Skew 40 , brightness , Darkness , Merge .
//               Abdelrahman Sonosy (20230207) -> Black and White , Winter , Oil panting , mageneta , Resize , Flip , Crop , Noise .
//               Mohamed Ayman Fayz (20231137) -> Blur, Rotate, Invert , purple , yellow , infrared , Frame .

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Photo_Photoshop");


    w.show();
    return a.exec();
}

