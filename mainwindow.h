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
    void on_Oil_panting_clicked();

    void on_Flip_clicked();

    void on_Flip_v_clicked();

    void on_Rotate_90_clicked();

    void on_Rotate_180_clicked();

    void on_Rotate_270_clicked();

    void on_Crop_clicked();

    void on_noise_clicked();

    void on_resize_clicked();

    void on_skew40_clicked();

    void on_extra1_clicked();

    void on_Merge_clicked();

    void on_InvertBtn_clicked();

    void on_GrayScale_clicked();

    void on_Frame_clicked();

    void on_FancyFarme_clicked();

    void on_Rotate180Btn_clicked();

    void on_Rotate180Btn_5_clicked();

    void on_yellow_clicked();

    void on_purple_clicked();

    void on_balck_white_clicked();

    void on_edge_detect_clicked();

    void on_brightness_clicked();

    void on_Darkness_clicked();

    void on_path_2_editingFinished();

    void on_extra2_clicked();

    void on_path_cursorPositionChanged(int arg1, int arg2);

    void on_load_clicked();

    void on_clear_clicked();

    void on_path_editingFinished();

    void on_Save_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
