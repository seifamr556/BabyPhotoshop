#include "mainwindow.h"
#include "Image_Class.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QProgressBar>
#include <QPixmap>
#include <Windows.h>
#include <QFileDialog>
#include <QColorDialog>
#include <random>
#include <QDir>

using namespace std;


bool isShow = false;
bool isSkew = false;
bool isResize = false;
bool isFrame = false;
bool isRotate = false;
bool isBright = false;
bool isBlur = false;
bool isFlip = false;
bool isOil = false;
bool isMerge = false;
bool isCrop = false;
bool isSmoke = false;
int Angle = 0;
Image image, copy_Image, merge_image;
QString file_name, file_merge;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->FiltersGroup_1->hide();
    ui->skewFrame->hide();
    ui->cropFrame->hide();
    ui->oilFrame->hide();
    ui->smokeFrame->hide();
    ui->progressBar->setVisible(false);
    ui->ResizeFrame->hide();
    ui->BlurFrame->hide();
    ui->FrameFrame->hide();
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
    try {
        file_name = QFileDialog::getOpenFileName(this, "Select image", QDir::homePath(), "Image Files (*.jpg *.tga *.png *.bmp)");
        QPixmap pix(file_name);
        image.loadNewImage(file_name.toStdString());
        int w = ui->Beforelabel->width();
        int h = ui->Beforelabel->height();
        ui->Beforelabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->AfterLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    } catch (...) {

    }

}


void MainWindow::on_grayButton_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
}


void MainWindow::on_BaWButton_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->brightFrame->hide();
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
    try {
        file_merge = QFileDialog::getOpenFileName(nullptr, "Select image", QDir::homePath(), "Image Files (*.jpg *.tga *.png *.bmp)");
        QPixmap pix(file_merge);
        newImg.loadNewImage(file_merge.toStdString());
    } catch (...) {
    }
    return newImg;

}


void MainWindow::on_mergeLoadBtn_clicked()
{
    merge_image = newImage();
}


void MainWindow::on_applyMergeBtn_clicked()
{
    if(file_merge != nullptr){
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
}


void MainWindow::on_detectButton_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
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

    try {
        int row = 0, column = 0;
        for (int i = 0; i < cropWidth; ++i) {
            for (int j = 0; j < cropHeight; ++j) {
                for (int k = 0; k < 3; ++k) {
                    cropped(i, j, k) = crop(i + x, j + y, k);
                }
            }
        }
        copy_Image = cropped;
        QImage qImage(cropped.imageData, cropped.width, cropped.height, cropped.width * 3, QImage::Format_RGB888);
        QPixmap img = QPixmap::fromImage(qImage);
        int w = ui->AfterLabel->width();
        int h = ui->AfterLabel->height();
        ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
    } catch (...) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Please Enter valid region.");
        msgBox.exec();
    }

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
    ui->progressBar->setVisible(true);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    Image blur = image;
    int blurRadius = value;
    for( int i = 0; i <50; ++i ) {
        ui->progressBar->setValue(i);
    }

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
    for( int i = 50; i <100; ++i ) {
        ui->progressBar->setValue(i);
    }

    ui->progressBar->setVisible(false);

}


void MainWindow::on_blurBtn_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
    if(isBlur){
        ui->BlurFrame->hide();
        isBlur = false;
    }else{
        ui->BlurFrame->show();
        isBlur = true;
    }
}


void MainWindow::on_oilButton_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
    if(isOil){
        ui->oilFrame->hide();
        isOil = false;
    }else{
        ui->oilFrame->show();
        isOil = true;
    }
}


void MainWindow::on_applyOilBtn_clicked()
{
    ui->progressBar->setVisible(true);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    Image oil = image;
    int radius = ui->radiusOilSlider->value();
    int intensityLevels = ui->intensitySlider->value();
    int intensityCount[intensityLevels];
    int averageR[intensityLevels];
    int averageG[intensityLevels];
    int averageB[intensityLevels];
    for (int i = 0; i < oil.width; ++i) {
        for (int j = 0; j < oil.height; ++j) {

            fill(intensityCount, intensityCount + intensityLevels, 0);
            fill(averageR, averageR + intensityLevels, 0);
            fill(averageG, averageG + intensityLevels, 0);
            fill(averageB, averageB + intensityLevels, 0);

            for (int k = max(0, i - radius); k <= min(oil.width -1, i + radius); ++k) {
                for (int l = max(0, j - radius); l <= min(oil.height - 1, j + radius) ; ++l) {

                    int r = oil(k, l, 0);
                    int g = oil(k, l, 1);
                    int b = oil(k, l, 2);

                    int curIntensity = (int)((double)((r+g+b)/3)*intensityLevels)/255.0f;
                    intensityCount[curIntensity]++;
                    averageR[curIntensity] += r;
                    averageG[curIntensity] += g;
                    averageB[curIntensity] += b;
                }
            }
            int curMax = 0;
            int maxIndex = 0;
            for (int k = 0; k < intensityLevels; ++k) {
                if (intensityCount[k] > curMax){
                    curMax = intensityCount[k];
                    maxIndex = k;
                }
            }
            try {
                oil(i, j, 0) = int(averageR[maxIndex] / curMax);
                oil(i, j, 1) = int(averageG[maxIndex] / curMax);
                oil(i, j, 2) = int(averageB[maxIndex] / curMax);
            } catch (...) {
            }

        }
    }
    copy_Image = oil;
    QImage qImage(oil.imageData, oil.width, oil.height, oil.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
    for( int i = 50; i <100; ++i ) {
        ui->progressBar->setValue(i);
    }

    ui->progressBar->setVisible(false);
}


void MainWindow::on_frameButton_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
    if(isFrame){
        ui->FrameFrame->hide();
        isFrame= false;
    }else{
        ui->FrameFrame->show();
        isFrame = true;
    }
}


void MainWindow::on_simpleTwoFrameBtn_clicked()
{
    Image frame = image;
    QColor color  = QColorDialog::getColor("Select color 1");
    QColor color2  = QColorDialog::getColor("Select color 2");
    for (int i = 0; i < frame.width; ++i) {
        for (int j = 0; j < frame.width/50; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = 0; i < frame.width/50; ++i) {
        for (int j = 0; j < frame.height; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width-1; i > frame.width - frame.width/50; --i) {
        for (int j = 0; j < frame.height; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = 0; i < frame.width; ++i) {
        for (int j = frame.height - 1; j > frame.height - frame.width/50; --j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }


    for (int i = frame.width/50; i < frame.width-frame.width/50; ++i) {
        for (int j = frame.width/50; j < (frame.width/50*2); ++j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }
    for (int i = frame.width/50; i < frame.width/50 + frame.width/50; ++i) {
        for (int j = frame.width/50; j < frame.height-frame.width/50; ++j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }
    for (int i = frame.width-frame.width/50; i > frame.width - (frame.width/50)*2; --i) {
        for (int j = frame.width/50; j < frame.height-frame.width/50; ++j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }
    for (int i = frame.width/50; i < frame.width-frame.width/50; ++i) {
        for (int j = frame.height - frame.width/50; j > frame.height - (frame.width/50*2); --j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }

    copy_Image = frame;
    QImage qImage(frame.imageData, frame.width, frame.height, frame.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_simpleOneFrameBtn_clicked()
{
    QColor color  = QColorDialog::getColor("Select color");
    Image frame = image;
    for (int i = 0; i < frame.width; ++i) {
        for (int j = 0; j < frame.width/30; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = 0; i < frame.width/30; ++i) {
        for (int j = 0; j < frame.height; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width-1; i > frame.width - frame.width/30; --i) {
        for (int j = 0; j < frame.height; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = 0; i < frame.width; ++i) {
        for (int j = frame.height - 1; j > frame.height - frame.width/30; --j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }

    copy_Image = frame;
    QImage qImage(frame.imageData, frame.width, frame.height, frame.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_designTwoFrameBtn_clicked()
{
    QColor color  = QColorDialog::getColor("Select color 1");
    QColor color2  = QColorDialog::getColor("Select color 2");
    Image frame = image;
    int frameWidth = frame.width/70;
    int frameHeight = frame.width/70;
    for (int i = frameWidth*3; i < frame.width/2 - frameWidth; ++i) {
        for (int j = frameHeight*2; j < frameHeight*3; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frameWidth*3; i < frameWidth*4; ++i) {
        for (int j = frameHeight*3; j < frame.height/2 - frameHeight; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width-frameWidth*3; i > frame.width - frameWidth*4; --i) {
        for (int j = frame.height/2 + frameHeight; j < frame.height - frameHeight*2; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width/2 + frameWidth ; i < frame.width-frameWidth*3; ++i) {
        for (int j = frame.height - frameHeight*2; j > frame.height - frameHeight*3; --j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }



    for (int i = frameWidth; i < frame.width/2 - frameWidth*4; ++i) {
        for (int j = frameWidth*4; j < frameWidth*5; ++j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }
    for (int i = frameWidth; i < frameWidth*2; ++i) {
        for (int j = frameWidth*4; j < frame.height/2; ++j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }
    for (int i = frame.width-frameWidth; i > frame.width - frameWidth*2; --i) {
        for (int j = frame.height/2 + frameWidth*2; j < frame.height-frameWidth*4; ++j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }
    for (int i = frame.width/2 + frameWidth*4; i < frame.width-frameWidth; ++i) {
        for (int j = frame.height - frameWidth*4; j > frame.height - frameWidth*5; --j) {
            frame(i, j , 0) = color2.red();
            frame(i, j , 1) = color2.green();
            frame(i, j , 2) = color2.blue();
        }
    }

    copy_Image = frame;
    QImage qImage(frame.imageData, frame.width, frame.height, frame.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_designOneFrameBtn_clicked()
{
    QColor color  = QColorDialog::getColor("Select color 1");
    Image frame = image;
    int frameWidth = frame.width/70;
    int frameHeight = frame.width/70;
    for (int i = frameWidth*3; i < frame.width/2 - frameWidth; ++i) {
        for (int j = frameHeight*2; j < frameHeight*3; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frameWidth*3; i < frameWidth*4; ++i) {
        for (int j = frameHeight*3; j < frame.height/2 - frameHeight; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width-frameWidth*3; i > frame.width - frameWidth*4; --i) {
        for (int j = frame.height/2 + frameHeight; j < frame.height - frameHeight*2; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width/2 + frameWidth ; i < frame.width-frameWidth*3; ++i) {
        for (int j = frame.height - frameHeight*2; j > frame.height - frameHeight*3; --j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }



    for (int i = frameWidth; i < frame.width/2 - frameWidth*4; ++i) {
        for (int j = frameWidth*4; j < frameWidth*5; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frameWidth; i < frameWidth*2; ++i) {
        for (int j = frameWidth*4; j < frame.height/2; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width-frameWidth; i > frame.width - frameWidth*2; --i) {
        for (int j = frame.height/2 + frameWidth*2; j < frame.height-frameWidth*4; ++j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }
    for (int i = frame.width/2 + frameWidth*4; i < frame.width-frameWidth; ++i) {
        for (int j = frame.height - frameWidth*4; j > frame.height - frameWidth*5; --j) {
            frame(i, j , 0) = color.red();
            frame(i, j , 1) = color.green();
            frame(i, j , 2) = color.blue();
        }
    }

    copy_Image = frame;
    QImage qImage(frame.imageData, frame.width, frame.height, frame.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_fancyFrameBtn_clicked()
{
    Image frame = image;
    QColor color  = QColorDialog::getColor("Select color 1");
    QColor color2  = QColorDialog::getColor("Select color 2");

    for (int i = frame.width/70; i < frame.width - frame.width/70; ++i) {
        for (int j = frame.width/70; j < (frame.width/70)*2.5; ++j) {
            if (j%2==0 && i%2==0){
                frame(i, j , 0) = color.red();
                frame(i, j , 1) = color.green();
                frame(i, j , 2) = color.blue();
            }else{
                frame(i, j , 0) = color2.red();
                frame(i, j , 1) = color2.green();
                frame(i, j , 2) = color2.blue();
            }
        }
    }
    for (int i = frame.width/70; i < (frame.width/70)*2.5; ++i) {
        for (int j = frame.width/70; j < frame.height - frame.width/70; ++j) {
            if (j%2==0 && i%2==0){
                frame(i, j , 0) = color.red();
                frame(i, j , 1) = color.green();
                frame(i, j , 2) = color.blue();
            }else{
                frame(i, j , 0) = color2.red();
                frame(i, j , 1) = color2.green();
                frame(i, j , 2) = color2.blue();
            }
        }
    }
    for (int i = frame.width-frame.width/70-1; i > frame.width - (frame.width/70)*2.5; --i) {
        for (int j = frame.width/70; j < frame.height - (frame.width/70)*2; ++j) {
            if (j%2==0 && i%2==0){
                frame(i, j , 0) = color.red();
                frame(i, j , 1) = color.green();
                frame(i, j , 2) = color.blue();
            }else{
                frame(i, j , 0) = color2.red();
                frame(i, j , 1) = color2.green();
                frame(i, j , 2) = color2.blue();
            }
        }
    }
    for (int i = frame.width/70; i < frame.width - (frame.width/70); ++i) {
        for (int j = frame.height - (frame.width/70) -1; j > frame.height - (frame.width/70)*2.5; --j) {
            if (j%2==0 && i%2==0){
                frame(i, j , 0) = color.red();
                frame(i, j , 1) = color.green();
                frame(i, j , 2) = color.blue();
            }else{
                frame(i, j , 0) = color2.red();
                frame(i, j , 1) = color2.green();
                frame(i, j , 2) = color2.blue();
            }
        }
    }

    copy_Image = frame;
    QImage qImage(frame.imageData, frame.width, frame.height, frame.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_clearButton_clicked()
{
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
    QImage qImage(image.imageData, image.width, image.height, image.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_smokeButton_clicked()
{
    isSkew = false;
    isResize = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
    if(isSmoke){
        ui->smokeFrame->hide();
        isSmoke = false;
    }else{
        ui->smokeFrame->show();
        isSmoke = true;
    }
}


void MainWindow::on_smokeSlider_valueChanged(int value)
{
    Image smokeImage = image;
    double smoke = value*0.1;


    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < smokeImage.width; ++i) {
        for (int j = 0; j < smokeImage.height; ++j) {
            double values = dis(gen);
            if (values < smoke) {
                smokeImage(i, j, 0) = min(255, smokeImage(i, j, 0) + 50);
                smokeImage(i, j, 1) = min(255, smokeImage(i, j, 1) + 50);
                smokeImage(i, j, 2) = min(255, smokeImage(i, j, 2) + 50);
            }
        }
    }

    copy_Image = smokeImage;
    QImage qImage(smokeImage.imageData, smokeImage.width, smokeImage.height, smokeImage.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_glitchButton_clicked()
{
    isSkew = false;
    isResize = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isSmoke = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->smokeFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
    Image glitch = image;
    for (int i = 0; i < glitch.width-glitch.width/50; ++i) {
        for (int j = 0; j < glitch.height-glitch.height/50; ++j) {
            for (int k = 0; k < 3; ++k) {
                glitch(i, j, k) = (glitch(i, j, k)+glitch(i+glitch.width/50, j+glitch.height/50, k))/2;
            }
        }
    }
    copy_Image = glitch;
    QImage qImage(glitch.imageData, glitch.width, glitch.height, glitch.width * 3, QImage::Format_RGB888);
    QPixmap img = QPixmap::fromImage(qImage);
    int w = ui->AfterLabel->width();
    int h = ui->AfterLabel->height();
    ui->AfterLabel->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}


void MainWindow::on_saveImageButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Image", "", "JPG Files (*.jpg);;TGA Files (*.tga);;PNG Files (*.png);;BMP Files (*.bmp)");
    image.saveImage(filePath.toStdString());
    QPixmap pix1;
    ui->AfterLabel->setText("Image");
    ui->Beforelabel->setText("Image");
    // Check if user canceled or selected a file
    if (!filePath.isEmpty()) {
        // User selected a file, filePath contains the selected file path

    } else {
        // User canceled the operation
        qDebug() << "Operation canceled by user.";
    }
    Angle = 0;
    isSkew = false;
    isResize = false;
    isSmoke = false;
    isOil = false;
    isBlur = false;
    isBright = false;
    isFrame = false;
    isRotate = false;
    isFlip = false;
    isMerge = false;
    isCrop = false;
    ui->oilFrame->hide();
    ui->BlurFrame->hide();
    ui->cropFrame->hide();
    ui->skewFrame->hide();
    ui->smokeFrame->hide();
    ui->ResizeFrame->hide();
    ui->FrameFrame->hide();
    ui->rotateFrame->hide();
    ui->flipFrame->hide();
    ui->mergeFrame->hide();
    ui->brightFrame->hide();
}

