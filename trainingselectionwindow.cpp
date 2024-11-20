#include "trainingselectionwindow.h"
#include "ui_trainingselectionwindow.h"
#include "mathtrainingwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>

TrainingSelectionWindow::TrainingSelectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingSelectionWindow)
{
    ui->setupUi(this);

    QFile styleFile(":/style/styles.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    connect(ui->viewProfileButton, &QPushButton::clicked, this, &TrainingSelectionWindow::on_viewProfileButton_clicked);
}

TrainingSelectionWindow::~TrainingSelectionWindow()
{
    delete ui;
}

void TrainingSelectionWindow::setUserProfile(const QString &username, const QString &name, const QPixmap &image)
{
    currentUsername = username;
    currentName = name;
    currentImage = image;
}

void TrainingSelectionWindow::on_mathTrainingButton_clicked()
{
    MathTrainingWindow *mathTraining = new MathTrainingWindow(this);
    mathTraining->setAttribute(Qt::WA_DeleteOnClose); // Удалить окно при закрытии
    mathTraining->show(); // Открыть окно
}

void TrainingSelectionWindow::on_speedTrainingButton_clicked()
{
    // Логика для тренировки 2
    QMessageBox::information(this, "Тренировка", "Вы выбрали тренировку 2");
    // Здесь можно открыть окно с подробной информацией о тренировке или начать тренировку
}

void TrainingSelectionWindow::on_offButton_clicked()
{
    // Закрыть текущее окно и вернуться назад
    this->close();
}

void TrainingSelectionWindow::on_viewProfileButton_clicked()
{
    // Создаем всплывающее окно для отображения профиля
    QDialog *profileDialog = new QDialog(this);
    profileDialog->setWindowTitle("Профиль пользователя");
    profileDialog->setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(profileDialog);

    QLabel *usernameLabel = new QLabel("Логин: " + currentUsername, profileDialog);
    QLabel *nameLabel = new QLabel("Имя: " + currentName, profileDialog);

    QLabel *imageLabel = new QLabel(profileDialog);
    if (!currentImage.isNull()) {
        imageLabel->setPixmap(currentImage.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageLabel->setAlignment(Qt::AlignCenter);
    } else {
        imageLabel->setText("Изображение отсутствует");
        imageLabel->setAlignment(Qt::AlignCenter);
    }

    layout->addWidget(imageLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(nameLabel);

    QPushButton *closeButton = new QPushButton("Закрыть", profileDialog);
    connect(closeButton, &QPushButton::clicked, profileDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    profileDialog->setLayout(layout);
    profileDialog->exec();
}
