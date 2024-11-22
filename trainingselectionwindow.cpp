#include "mainwindow.h"
#include "trainingselectionwindow.h"
#include "ui_trainingselectionwindow.h"
#include "mathtrainingwindow.h"
#include "speedtrainingwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QTabWidget>

TrainingSelectionWindow::TrainingSelectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingSelectionWindow),
    profileDialog(nullptr) // Инициализация указателя
{
    ui->setupUi(this);

    QFile styleFile(":/style/styles.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QPixmap questionbuttonPixmap("C:/Users/Mikhail/Documents/question.png");
    QIcon questionbuttonIcon(questionbuttonPixmap);
    ui->questButtonThirdWindow->setIcon(questionbuttonIcon);
    ui->questButtonThirdWindow->setIconSize(questionbuttonPixmap.rect().size());

    QPixmap rightBackbuttonPixmap("C:/Users/Mikhail/Documents/rightBack.png");
    QIcon rightBackbuttonIcon(rightBackbuttonPixmap);
    ui->backButtonToo->setIcon(rightBackbuttonIcon);
    ui->backButtonToo->setIconSize(rightBackbuttonPixmap.rect().size());

    connect(ui->viewProfileButton, &QPushButton::clicked, this, &TrainingSelectionWindow::on_viewProfileButton_clicked);


}

TrainingSelectionWindow::~TrainingSelectionWindow()
{
    delete ui;
}

void TrainingSelectionWindow::setUserProfile(const QString &username, const QString &name, const QPixmap &image, int maxMathStreak)
{
    currentUsername = username;
    currentName = name;
    currentImage = image;
    currentMaxMathStreak = maxMathStreak;
}


void TrainingSelectionWindow::on_mathTrainingButton_clicked()
{
    MathTrainingWindow *mathTraining = new MathTrainingWindow(this);
    mathTraining->setAttribute(Qt::WA_DeleteOnClose);

    connect(mathTraining, &MathTrainingWindow::maxMathStreakUpdated, this, &TrainingSelectionWindow::updateMaxMathStreak);
    connect(mathTraining, &QWidget::destroyed, this, [this]() {
        setUserProfile(currentUsername, currentName, currentImage, currentMaxMathStreak);
    });

    mathTraining->show();
}


void TrainingSelectionWindow::on_speedTrainingButton_clicked()
{
    SpeedTrainingWindow *speedTraining = new SpeedTrainingWindow(this);
    speedTraining->setAttribute(Qt::WA_DeleteOnClose);
    speedTraining->show();
}

void TrainingSelectionWindow::on_backButton_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

    this->close();
}

void TrainingSelectionWindow::on_viewProfileButton_clicked()
{
    if (!profileDialog) {
        profileDialog = new QDialog(this);
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

        QLabel *streakLabel = new QLabel("Максимальный стрик (математика): " + QString::number(currentMaxMathStreak), profileDialog);

        layout->addWidget(imageLabel);
        layout->addWidget(usernameLabel);
        layout->addWidget(nameLabel);
        layout->addWidget(streakLabel);

        QPushButton *closeButton = new QPushButton("Закрыть", profileDialog);
        connect(closeButton, &QPushButton::clicked, profileDialog, &QDialog::accept);

        layout->addWidget(closeButton);

        profileDialog->setLayout(layout);

        connect(profileDialog, &QDialog::finished, this, [this]() {
            delete profileDialog;
            profileDialog = nullptr;
        });
    }

    profileDialog->show();
    profileDialog->raise();
    profileDialog->activateWindow();
}

void TrainingSelectionWindow::on_questButtonThirdWindow_clicked()
{
    QDialog *helpDialog = new QDialog(this);
    helpDialog->setWindowTitle("Справочная информация");
    helpDialog->setFixedSize(800, 700);

    QTabWidget *tabWidget = new QTabWidget(helpDialog);

    QWidget *mathTab = new QWidget(tabWidget);
    QVBoxLayout *mathLayout = new QVBoxLayout(mathTab);

    QLabel *mathImage = new QLabel(mathTab);
    mathImage->setPixmap(QPixmap("C:/Users/Mikhail/Documents/math.jpg").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mathImage->setAlignment(Qt::AlignCenter);

    mathLayout->addWidget(mathImage);
    mathLayout->addWidget(new QLabel(
      "Добро пожаловать в тренировку по математике!\n\n"
              "Задачи:\n"
              "1. Выберите уровень сложности: Легкий, Средний, Сложный. Сложность влияет на диапазон чисел для вычислений.\n"
              "2. Выберите тип операции: Сложение, Вычитание, Умножение, Деление или Сложные выражения (например, (a + b) * c).\n"
              "3. Каждый вопрос будет отображаться на экране, и вам нужно ввести правильный ответ в поле ввода.\n"
              "4. После ввода ответа нажмите 'Проверить ответ'.\n"
              "5. Если вы ответите правильно, ваш счет увеличится. Если ответ неверный, счет сбрасывается.\n"
              "6. У вас будет ограниченное время (10 секунд) для ответа на каждый вопрос.\n\n"
              "Удачи в тренировке!",
        mathTab));
    tabWidget->addTab(mathTab, "Математика");

    // Вкладка "Тренировка на скорость"
    QWidget *speedTab = new QWidget(tabWidget);
    QVBoxLayout *speedLayout = new QVBoxLayout(speedTab);

    QLabel *speedImage = new QLabel(speedTab);
    speedImage->setPixmap(QPixmap("C:/Users/Mikhail/Documents/speed.jpg").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    speedImage->setAlignment(Qt::AlignCenter);

    speedLayout->addWidget(speedImage);
    speedLayout->addWidget(new QLabel(
        "<h3>Тренировка на скорость</h3>"
        "<p><b>Цель:</b> Развитие реакции и внимания.</p>"
        "<ul>"
        "<li>Отвечайте на задания за ограниченное время.</li>"
        "<li>Задания включают вычисления и выбор правильного ответа.</li>"
        "</ul>",
        speedTab));
    tabWidget->addTab(speedTab, "Скорость");

    // Вкладка "Тренировка памяти"
    QWidget *memoryTab = new QWidget(tabWidget);
    QVBoxLayout *memoryLayout = new QVBoxLayout(memoryTab);

    QLabel *memoryImage = new QLabel(memoryTab);
    memoryImage->setPixmap(QPixmap("C:/Users/Mikhail/Documents/memory.jpg").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    memoryImage->setAlignment(Qt::AlignCenter);

    memoryLayout->addWidget(memoryImage);
    memoryLayout->addWidget(new QLabel(
        "<h3>Тренировка памяти</h3>"
        "<p><b>Цель:</b> Улучшение кратковременной памяти и способности к запоминанию.</p>"
        "<ul>"
        "<li>Запоминайте последовательности чисел, слов или изображений.</li>"
        "<li>Сложность растет с увеличением количества элементов.</li>"
        "</ul>",
        memoryTab));
    tabWidget->addTab(memoryTab, "Память");

    // Добавляем кнопки
    QVBoxLayout *mainLayout = new QVBoxLayout(helpDialog);
    mainLayout->addWidget(tabWidget);

    QPushButton *closeButton = new QPushButton("Закрыть", helpDialog);
    connect(closeButton, &QPushButton::clicked, helpDialog, &QDialog::accept);
    mainLayout->addWidget(closeButton);

    helpDialog->setLayout(mainLayout);
    helpDialog->exec();
}

void TrainingSelectionWindow::updateMaxMathStreak(int newMaxMathStreak)
{
    if (newMaxMathStreak > currentMaxMathStreak) {
        currentMaxMathStreak = newMaxMathStreak;
    }
}

