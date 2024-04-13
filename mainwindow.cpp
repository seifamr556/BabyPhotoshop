#include "mainwindow.h"
#include "Image_Class.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <Windows.h>
#include <QFileDialog>
#include <random>
#include <QDir>

using namespace std;


bool isShow = false;
bool isSkew = false;
bool isResize = false;
bool isRotate = false;
bool isBright = false;
bool isBlur = false;
bool isFlip = false;
bool isMerge = false;
bool isCrop = false;
int Angle = 0;
Image image, copy_Image, merge_image;
QString file_name;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->FiltersGroup_1->hide();
    ui->skewFrame->hide();
    ui->cropFrame->hide();
    ui->ResizeFrame->hide();
    ui->BlurFrame->show();
    ui->rotateFrame->hide();
    ui->brightFrame->hide();
    ui->mergeFrame->hide();
    ui->flipFrame->hide();
    ui->FiltersGroup_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FiltersButton_clicked()
{
    if (isShow){
        ui->FiltersGroup_1->hide();
        ui->FiltersGroup_2->hide();
        isShow = false;
    } else{
        ui->FiltersGroup_1->show();
        ui->FiltersGroup_2->show();
        isShow = true;
    }

}


void MainWindow::on_loadImageButton_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, "Select image", QDir::homePath(), "Image Files (*.jpg *.tga *.png *.bmp)");
    QPixmap pix(file_name);
    image.loadNewImage(file_name.toStdString());
    int w = ui->Beforelabel->width();
    int h = ui->Beforelabel->height();
    ui->Beforelabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->AfterLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}


void MainWindow::on_grayButton_clicked()
{
    Image grayImage = image;
    for (int width = 0; width < grayImage.width; ++width) {
        for (int height = 0; height < grayImage.height; ++height) {
            int avg = 0;
            for (int channel = 0; channel < 3; ++channel) {
                avg += grayImage(width, height, channel);
            }
            avg /= 3;
            for (int k = 0; k < 3; ++k) {
                grayImage(width, height, k) = avg;
            }
        }
    }
    copy_Image = grayImage;
    QImage qImage(grayImage.imageData, grayImage.width, grayImage.height, grayImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio)); }

void MainWindow::on_doneBtn_clicked()
{
    image = copy_Image;
    Angle = 0;
    isSkew = false;
    isResize = false;
    isBlur = false;
    isBright = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->ResizeFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
}


void MainWindow::on_BaWButton_clicked()
{
    Image blackAwhite = image;
    for (int i = 0; i < blackAwhite.width; ++i) {
        for (int j = 0; j < blackAwhite.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += blackAwhite(i, j, k);
            }
            avg /= 3;
            unsigned int color = 127;
            if (avg <= color) {
                for (int k = 0; k < 3; ++k) {
                    blackAwhite(i, j, k) = 0;
                }
            } else {
                for (int k = 0; k < 3; ++k) {
                    blackAwhite(i, j, k) = 255;
                }
            }
        }
    }
    copy_Image = blackAwhite;
    QImage qImage(blackAwhite.imageData, blackAwhite.width, blackAwhite.height, blackAwhite.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_invertButton_clicked()
{
    Image invertImage = image;
    for (int i = 0; i < invertImage.width; ++i) {
        for (int j = 0; j < invertImage.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                invertImage(i, j, k) = 255 - invertImage(i, j, k);
            }
        }
    }

    copy_Image = invertImage;
    QImage qImage(invertImage.imageData, invertImage.width, invertImage.height, invertImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));

}


void MainWindow::on_sunButton_clicked()
{
    Image sunImage = image;
    for (int i = 0; i < sunImage.width; ++i) {
        for (int j = 0; j < sunImage.height; ++j) {
            sunImage(i, j, 0) = fmin(255, sunImage(i, j, 0) + 25);
            sunImage(i, j, 1) = fmin(255, sunImage(i, j, 1) + 25);
            sunImage(i, j, 2) = fmax(0, sunImage(i, j, 2) - 25);
        }
    }

    copy_Image = sunImage;
    QImage qImage(sunImage.imageData, sunImage.width, sunImage.height, sunImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));

}


void MainWindow::on_infraredButton_clicked()
{
    Image infraredImage = image;
    for (int i = 0; i < infraredImage.width; ++i) {
        for (int j = 0; j < infraredImage.height; ++j) {
            infraredImage(i, j, 0) = 255;
            infraredImage(i, j, 1) = 255 - infraredImage(i, j, 1);
            infraredImage(i, j, 2) = 255 - infraredImage(i, j, 2);
        }
    }

    copy_Image = infraredImage;
    QImage qImage(infraredImage.imageData, infraredImage.width, infraredImage.height, infraredImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_TVButton_clicked()
{
    Image TVImage = image;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-30, 30);

    for (int i = 0; i < TVImage.width; ++i) {
        for (int j = 0; j < TVImage.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int noise = int(dis(gen));
                TVImage(i, j, k) = max(0, min(255, TVImage(i, j, k) + noise));
            }
        }
    }

    for (int i = 0; i < TVImage.width; ++i) {
        for (int j = 0; j < TVImage.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                TVImage(i, j, k) = int(TVImage(i, j, k) / 10) * 10;
            }
        }
    }

    for (int j = 0; j < TVImage.height; ++j) {
        if (j % 2 == 0) {
            for (int i = 0; i < TVImage.width; ++i) {
                for (int k = 0; k < 3; ++k) {
                    TVImage(i, j, k) = int(TVImage(i, j, k) * 0.8);
                }
            }
        }
    }

    copy_Image = TVImage;
    QImage qImage(TVImage.imageData, TVImage.width, TVImage.height, TVImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_skewButton_clicked()
{
    if (isSkew){
        ui->skewFrame->hide();
        isSkew = false;
    }else{
        ui->skewFrame->show();
        isSkew = true;
    }
}


void MainWindow::on_applySkewBtn_clicked()
{
    Image skew = image;
    if(ui->leftSkew->isChecked()){
        float angle;
        angle = ui->angle->value();
        double radian = abs(angle) * M_PI / 180.0;
        double sine = sin(radian);

        int width = skew.width + int(skew.height * abs(sine));
        int height = skew.height;

        Image skewedImage(width, height);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                double X = i + sine * (j - height);
                double Y = j;

                if (X >= 0 && X < skew.width && Y >= 0 && Y < skew.height) {
                    int x0 = floor(X);
                    int x1 = ceil(X);
                    int y0 = floor(Y);
                    int y1 = ceil(Y);

                    double deltaX = X - x0;
                    double deltaY = Y - y0;

                    for (int k = 0; k < 3; ++k) {
                        double channel = (1.0 - deltaX) * (1.0 - deltaY) * skew(x0, y0, k) +
                                         deltaX * (1.0 - deltaY) * skew(x1, y0, k) +
                                         (1.0 - deltaX) * deltaY * skew(x0, y1, k) +
                                         deltaX * deltaY * skew(x1, y1, k);
                        skewedImage(i, j, k) = channel;
                    }
                }
            }
        }
        copy_Image = skewedImage;
        QImage qImage(skewedImage.imageData, skewedImage.width, skewedImage.height, skewedImage.width * 3, QImage::Format_RGB888);
        QPixmap img = QPixmap::fromImage(qImage);
        int w = ui->AfterLabel->width();
        int h = ui->AfterLabel->height();
        ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
        ui->skewFrame->hide();
        isSkew = false;
    }
    else if (ui->rightSkew->isChecked()){
        float angle;
        angle = ui->angle->value();
        double radian = abs(angle) * M_PI / 180.0;
        double sine = sin(radian);

        int width = skew.width + int(skew.height * abs(sine));
        int height = skew.height;

        Image skewedImage(width, height);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                double X = i - sine * j;
                double Y = j;

                if (X >= 0 && X < skew.width && Y >= 0 && Y < skew.height) {
                    int x0 = floor(X);
                    int x1 = ceil(X);
                    int y0 = floor(Y);
                    int y1 = ceil(Y);

                    double deltaX = X - x0;
                    double deltaY = Y - y0;

                    for (int k = 0; k < 3; ++k) {
                        double channel = (1.0 - deltaX) * (1.0 - deltaY) * skew(x0, y0, k) +
                                         deltaX * (1.0 - deltaY) * skew(x1, y0, k) +
                                         (1.0 - deltaX) * deltaY * skew(x0, y1, k) +
                                         deltaX * deltaY * skew(x1, y1, k);
                        skewedImage(i, j, k) = channel;
                    }
                }
            }
        }
        copy_Image = skewedImage;
        QImage qImage(skewedImage.imageData, skewedImage.width, skewedImage.height, skewedImage.width * 3, QImage::Format_RGB888);
        QPixmap img = QPixmap::fromImage(qImage);
        int w = ui->AfterLabel->width();
        int h = ui->AfterLabel->height();
        ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
        ui->skewFrame->hide();
        isSkew = false;
    }
}


void MainWindow::on_resizeButton_clicked()
{
    if (isResize){
        ui->ResizeFrame->hide();
        isResize = false;
    } else{
        ui->ResizeFrame->show();
        isResize = true;
    }
}


void MainWindow::on_applyResizeBtn_clicked()
{
    Image resizeImage = image;
    int height, width;
    width = ui->widthBox->value();
    height = ui->heightBox->value();
    Image resize(width, height);
    double ratioW, ratioH;
    ratioH = double (resizeImage.height)/height;
    ratioW = double (resizeImage.width)/width;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int x = round(i * ratioW);
            int y = round(j * ratioH);

            for (int k = 0; k < 3; ++k) {
                resize(i, j, k) = resizeImage(x, y, k);
            }
        }
    }

    copy_Image = resize;
    QImage qImage(resize.imageData, resize.width, resize.height, resize.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
    ui->ResizeFrame->hide();
    isResize = false;
}


void MainWindow::on_purpleButton_clicked()
{
    Image purpleImage = image;
    for (int i = 0; i < purpleImage.width; ++i) {
        for (int j = 0; j < purpleImage.height; ++j) {
            purpleImage(i, j, 0) = min(255, purpleImage(i, j, 0) + 10);
            purpleImage(i, j, 1) = max(0, purpleImage(i, j, 1) - 38);
            purpleImage(i, j, 2) = min(255, purpleImage(i, j, 2) + 10);
        }
    }

    copy_Image = purpleImage;
    QImage qImage(purpleImage.imageData, purpleImage.width, purpleImage.height, purpleImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));

}


void MainWindow::on_rotateButton_clicked()
{
    if (isRotate){
        ui->rotateFrame->hide();
        isRotate = false;
    } else{
        ui->rotateFrame->show();
        isRotate = true;
    }
}


void MainWindow::on_add90Btn_clicked()
{
    if (Angle == 360){
        Angle = 0;
    }
    Angle += 90;
    Image rotate = image;
    int width, height;
    if (Angle == 90 || Angle == 270){
        width = rotate.height;
        height = rotate.width;
    } else{
        width = rotate.width;
        height = rotate.height;
    }

    Image rotatedImage(width, height);

    for (int i = 0; i < rotate.width; i++) {
        for (int j = 0; j < rotate.height; j++) {
            int new_i, new_j;
            if (Angle == 270) {
                new_i = j;
                new_j = height - 1 - i;
            } else if (Angle == 180) {
                new_i = width - 1 - i;
                new_j = height - 1 - j;
            } else if (Angle == 90) {
                new_i = width - 1 - j;
                new_j = i;
            } else if (Angle == 360){
                new_i = i;
                new_j = j;
            }
            for (int k = 0; k < 3; k++) {
                rotatedImage(new_i, new_j, k) = rotate(i, j, k);
            }
        }
    }

    copy_Image = rotatedImage;
    QImage qImage(rotatedImage.imageData, rotatedImage.width, rotatedImage.height, rotatedImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_brightnessButton_clicked()
{
    if (isBright){
        ui->brightFrame->hide();
        isBright = false;
    }else{
        ui->brightFrame->show();
        isBright = true;
    }
}


void MainWindow::on_applyBrightnessBtn_clicked()
{
    float value = (ui->brightValue->value())*0.5;
    Image bright = image;
    for (int i = 0; i < bright.width; ++i) {
        for (int j = 0; j < bright.height; ++j) {
            bright(i, j, 0) = min(int(bright(i, j, 0) * value), 255);
            bright(i, j, 1) = min(int(bright(i, j, 1) * value), 255);
            bright(i, j, 2) = min(int(bright(i, j, 2) * value), 255);
        }
    }
    copy_Image = bright;
    QImage qImage(bright.imageData, bright.width, bright.height, bright.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_flipButton_clicked()
{
    if(isFlip){
        ui->flipFrame->hide();
        isFlip = false;
    }else{
        ui->flipFrame->show();
        isFlip = true;
    }
}


void MainWindow::on_VFlipBtn_clicked()
{
    int new_i, new_j;
    Image flip = image;
    Image flippedImage(flip.width, flip.height);
    for (int i = 0; i < flip.width; i++)
    {
        for (int j = 0; j < flip.height; j++)
        {
            new_j = image.height - 1 - j;
            for (int k = 0; k < 3; k++)
            {
                flippedImage(i, j, k) = flip(i, new_j, k);
            }
        }
    }
    copy_Image = flippedImage;
    QImage qImage(flippedImage.imageData, flippedImage.width, flippedImage.height, flippedImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_HFlipBtn_clicked()
{
    int new_i, new_j;
    Image flip = image;
    Image flippedImage(flip.width, flip.height);
    for (int i = 0; i < flip.width; i++)
    {
        for (int j = 0; j < flip.height; j++)
        {
            new_i = flip.width - i;

            for (int k = 0; k < 3; k++)
            {
                flippedImage(i, j, k) = flip(new_i, j, k);
            }
        }
    }
    copy_Image = flippedImage;
    QImage qImage(flippedImage.imageData, flippedImage.width, flippedImage.height, flippedImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_mergeButton_clicked()
{
    if(isMerge){
        ui->mergeFrame->hide();
        isMerge = false;
    }else{
        ui->mergeFrame->show();
        isMerge = true;
    }
}


Image newImage(){
    Image newImg;
    file_name = QFileDialog::getOpenFileName(nullptr, "Select image", QDir::homePath(), "Image Files (*.jpg *.tga *.png *.bmp)");
    QPixmap pix(file_name);
    newImg.loadNewImage(file_name.toStdString());
    return newImg;
}

void MainWindow::on_mergeLoadBtn_clicked()
{
    merge_image = newImage();
}


void MainWindow::on_applyMergeBtn_clicked()
{
    Image mainImage = image;
    if(ui->resizeMergeButton->isChecked()){
        int width, height;
        width = max(merge_image.width, mainImage.width);
        height = max(mainImage.height, merge_image.height);
        Image resize1(width, height);
        Image resize2(width, height);
        double ratioW, ratioH;
        ratioH = double (merge_image.height)/height;
        ratioW = double (merge_image.width)/width;

        double ratioW1, ratioH1;
        ratioH1 = double (mainImage.height)/height;
        ratioW1 = double (mainImage.width)/width;

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int x = round(i * ratioW);
                int y = round(j * ratioH);
                int x1 = round(i * ratioW1);
                int y1 = round(j * ratioH1);
                for (int k = 0; k < 3; ++k) {
                    resize1(i, j, k) = merge_image(x, y, k);
                    resize2(i, j, k) = mainImage(x1, y1, k);
                }
            }
        }
        Image merged(width, height);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int avg = (resize1(i, j , k) + resize2(i, j, k))/2;
                    merged(i, j, k) = avg;
                }
            }
        }
        copy_Image = merged;
        QImage qImage(merged.imageData, merged.width, merged.height, merged.width * 3, QImage::Format_RGB888);
        QPixmap img = QPixmap::fromImage(qImage);
        int w = ui->AfterLabel->width();
        int h = ui->AfterLabel->height();
        ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
    }
    else if (ui->cropMergeButton->isChecked()){
        int width, height, cropHeight, cropWidth;
        width = min(mainImage.width, merge_image.width);
        height = min(mainImage.height, merge_image.height);

        Image merged(width, height);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int avg = (mainImage(i, j , k) + merge_image(i, j, k))/2;
                    merged(i, j, k) = avg;
                }
            }
        }
        copy_Image = merged;
        QImage qImage(merged.imageData, merged.width, merged.height, merged.width * 3, QImage::Format_RGB888);
        QPixmap img = QPixmap::fromImage(qImage);
        int w = ui->AfterLabel->width();
        int h = ui->AfterLabel->height();
        ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
    }
}


void MainWindow::on_detectButton_clicked()
{
    bool isEdge = false;
    Image detect = image;
    for (int i = 0; i < detect.width; ++i) {
        for (int j = 0; j < detect.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += detect(i, j, k);
            }
            avg /= 3;
            unsigned int color = 127;
            if (avg <= color) {
                for (int k = 0; k < 3; ++k) {
                    detect(i, j, k) = 0;
                }
            } else {
                for (int k = 0; k < 3; ++k) {
                    detect(i, j, k) = 255;
                }
            }
        }
    }
    for (int i = 0; i < detect.width; ++i) {
        isEdge = false;
        for (int j = 0; j < detect.height; ++j) {
            if (detect(i, j, 0) == 0 && !isEdge){
                isEdge = true;
                continue;
            }else if (detect(i, j, 0) == 255 && isEdge){
                for (int k = 0; k < 3; ++k) {
                    detect(i, j, k) = 0;
                    isEdge = false;
                }
            }
            if (isEdge){
                for (int k = 0; k < 3; ++k) {
                    detect(i, j, k) = 255;
                }
            }
        }
    }

    copy_Image = detect;
    QImage qImage(detect.imageData, detect.width, detect.height, detect.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_cropButton_clicked()
{
    if(isCrop){
        ui->cropFrame->hide();
        isCrop = false;
    }else{
        ui->cropFrame->show();
        isCrop = true;
    }
}


void MainWindow::on_applyCropBtn_clicked()
{
    Image crop = image;
    int x, y;
    x = ui->Xspin->value();;
    y = ui->Yspin->value();
    int cropWidth = ui->Wspin->value();
    int cropHeight = ui->Hspin->value();
    Image cropped(cropWidth, cropHeight);
    if (x < 0 || y < 0 || x > crop.width || y > crop.height){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Please Enter valid region.");
        msgBox.exec();
    } else {
        int row = 0, column = 0;
        for (int i = 0; i < cropWidth; ++i) {
            for (int j = 0; j < cropHeight; ++j) {
                for (int k = 0; k < 3; ++k) {
                    cropped(i, j, k) = crop(i + x, j + y, k);
                }
            }
        }
    }
    copy_Image = cropped;
    QImage qImage(cropped.imageData, cropped.width, cropped.height, cropped.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_brightValue_valueChanged(int values)
{
    float value = (values)*0.5;
    Image bright = image;
    for (int i = 0; i < bright.width; ++i) {
        for (int j = 0; j < bright.height; ++j) {
            bright(i, j, 0) = min(int(bright(i, j, 0) * value), 255);
            bright(i, j, 1) = min(int(bright(i, j, 1) * value), 255);
            bright(i, j, 2) = min(int(bright(i, j, 2) * value), 255);
        }
    }
    copy_Image = bright;
    QImage qImage(bright.imageData, bright.width, bright.height, bright.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_blurSlider_valueChanged(int value)
{
    Image blur = image;
    int blurRadius = value;

    vector < vector <int> > tRed(blur.width, vector <int> (blur.height));
    vector < vector <int> > tGreen(blur.width, vector <int> (blur.height));
    vector < vector <int> > tBlue(blur.width, vector <int> (blur.height));

    for (int i = 0; i < blur.width; ++i) {
        for (int j = 0; j < blur.height; ++j) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int k = -blurRadius; k <= blurRadius; ++k) {
                int x = i + k;
                if (x >= 0 && x < blur.width) {
                    sumR += blur(x, j, 0);
                    sumG += blur(x, j, 1);
                    sumB += blur(x, j, 2);
                }
            }
            tRed[i][j] = sumR;
            tGreen[i][j] = sumG;
            tBlue[i][j] = sumB;
        }
    }

    for (int i = 0; i < blur.width; ++i) {
        for (int j = 0; j < blur.height; ++j) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int k = -blurRadius; k <= blurRadius; ++k) {
                int y = j + k;
                if (y >= 0 && y < blur.height) {
                    sumR += tRed[i][y];
                    sumG += tGreen[i][y];
                    sumB += tBlue[i][y];
                }
            }
            int avgR = sumR / ((2 * blurRadius + 1) * (2 * blurRadius + 1));
            int avgG = sumG / ((2 * blurRadius + 1) * (2 * blurRadius + 1));
            int avgB = sumB / ((2 * blurRadius + 1) * (2 * blurRadius + 1));

            blur(i, j, 0) = avgR;
            blur(i, j, 1) = avgG;
            blur(i, j, 2) = avgB;
        }
    }

    copy_Image = blur;
    QImage qImage(blur.imageData, blur.width, blur.height, blur.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::on_blurButton_clicked()
{

}


void MainWindow::on_oilButton_clicked()
{

}


void MainWindow::on_blursButton_clicked()
{
    if(isBlur){
        ui->BlurFrame->hide();
        isBlur = false;
    }else{
        ui->BlurFrame->show();
        isBlur = true;
    }
}

