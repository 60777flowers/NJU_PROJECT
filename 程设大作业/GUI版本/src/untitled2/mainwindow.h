#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_reboot_button_clicked();

    void on_getdieres_button_clicked();

    void on_newchess_clicked();

    void on_move_A_clicked();

    void on_pushButton_clicked();

    void on_move_B_clicked();

    void on_move_C_clicked();

    void on_move_D_clicked();

private:
    Ui::MainWindow *ui;
    //QTextEdit *Board;  // 声明QTextEdit的指针
    //QTextEdit *message;  // 声明QTextEdit的指针
};
#endif // MAINWINDOW_H
