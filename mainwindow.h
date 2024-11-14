#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trainingselectionwindow.h"  // Подключаем заголовок нового окна


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_registerButton_clicked();   // слот для обработки нажатия на кнопку "Регистрация"

    void on_rgBtn_clicked();

    void on_enterButton_clicked();

    void on_etrBtn_clicked();

private:
    Ui::MainWindow *ui;
    TrainingSelectionWindow *trainingWindow;  // Указатель на новое окно

};

#endif // MAINWINDOW_H
