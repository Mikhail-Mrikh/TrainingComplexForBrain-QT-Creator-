#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Подключаем слот для нажатия на кнопку "Регистрация"
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_registerButton_clicked() {
    // Переключаемся на страницу регистрации в QStackedWidget
    ui->stackedWidget->setCurrentIndex(1);  // Устанавливаем индекс второй страницы (экран регистрации)
}

void MainWindow::on_enterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_rgBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_etrBtn_clicked()
{
    // Создаем новое окно
    trainingWindow = new TrainingSelectionWindow();

    // Показываем окно выбора тренировок и закрываем текущее окно
    trainingWindow->show();
    this->close();  // Закрываем текущее окно
}
