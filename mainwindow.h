#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_FiltersButton_clicked();

    void on_loadImageButton_clicked();

    void on_grayButton_clicked();

    void on_doneBtn_clicked();

    void on_BaWButton_clicked();

    void on_invertButton_clicked();

    void on_sunButton_clicked();

    void on_infraredButton_clicked();

    void on_TVButton_clicked();

    void on_skewButton_clicked();

    void on_applySkewBtn_clicked();

    void on_resizeButton_clicked();

    void on_applyResizeBtn_clicked();

    void on_purpleButton_clicked();

    void on_rotateButton_clicked();

    void on_add90Btn_clicked();

    void on_brightnessButton_clicked();

    void on_applyBrightnessBtn_clicked();

    void on_flipButton_clicked();

    void on_VFlipBtn_clicked();

    void on_HFlipBtn_clicked();

    void on_mergeButton_clicked();

    void on_mergeLoadBtn_clicked();

    void on_applyMergeBtn_clicked();

    void on_detectButton_clicked();

    void on_cropButton_clicked();

    void on_applyCropBtn_clicked();

    void on_brightValue_valueChanged(int value);

    void on_blurSlider_valueChanged(int value);

    void on_blurButton_clicked();

    void on_oilButton_clicked();

    void on_blursButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
