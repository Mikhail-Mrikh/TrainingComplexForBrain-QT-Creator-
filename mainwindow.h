#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trainingselectionwindow.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void checkAndCreateTable();

private slots:

    // Кнопки стартового окна (Первого)
    void on_questButtonFirstWindow_clicked();
    void on_enterButton_clicked();
    void on_registerButton_clicked();
    void on_exitButton_clicked();

    // Кнопки второго окна (Регистрация)
    void on_questButtonSecondWindow_clicked();
    void on_loadImgButton_clicked();
    void on_rgBtn_clicked();
    void on_backButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    TrainingSelectionWindow *trainingWindow;
    QPixmap loadedImage;

};

#endif // MAINWINDOW_H
