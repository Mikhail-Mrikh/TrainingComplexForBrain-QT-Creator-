#include "speedtrainingwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QComboBox>

SpeedTrainingWindow::SpeedTrainingWindow(QWidget *parent) :
    QDialog(parent),
    taskLabel(new QLabel(this)),
    answerInput(new QLineEdit(this)),
    startButton(new QPushButton("Начать тренировку", this)),
    checkAnswerButton(new QPushButton("Проверить ответ", this)),
    timerLabel(new QLabel("Время: 0", this)),
    streakLabel(new QLabel("Стрик: 0", this)),
    difficultyComboBox(new QComboBox(this)),
    categoryComboBox(new QComboBox(this)), // Инициализация нового QComboBox
    timer(new QTimer(this)),
    currentTime(0),
    correctAnswer(0),
    maxTime(10),
    remainingTime(10),
    currentStreak(0),
    maxStreak(0),
    difficultyLevel(1),
    categoryLevel(0),
    taskType(Addition)
{
    setWindowTitle("Тренировка на скорость");
    setFixedSize(400, 350);

    difficultyComboBox->addItem("Легкий");
    difficultyComboBox->addItem("Средний");
    difficultyComboBox->addItem("Сложный");

    categoryComboBox->addItem("Математика");
    categoryComboBox->addItem("Чтение");
    categoryComboBox->addItem("Логика");
    categoryComboBox->addItem("Внимание");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Выберите категорию задачи:", this));
    layout->addWidget(categoryComboBox);
    layout->addWidget(new QLabel("Выберите уровень сложности:", this));
    layout->addWidget(difficultyComboBox);
    layout->addWidget(taskLabel);
    layout->addWidget(timerLabel);
    layout->addWidget(streakLabel);
    layout->addWidget(answerInput);
    layout->addWidget(startButton);
    layout->addWidget(checkAnswerButton);

    connect(startButton, &QPushButton::clicked, this, &SpeedTrainingWindow::onStartButtonClicked);
    connect(checkAnswerButton, &QPushButton::clicked, this, &SpeedTrainingWindow::onCheckAnswerButtonClicked);
    connect(timer, &QTimer::timeout, this, &SpeedTrainingWindow::onTimerTimeout);
    connect(difficultyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SpeedTrainingWindow::onDifficultyChanged);
    connect(categoryComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SpeedTrainingWindow::onCategoryChanged);

    checkAnswerButton->setEnabled(false);
}

SpeedTrainingWindow::~SpeedTrainingWindow()
{
    delete timer;
    delete categoryComboBox;
    delete difficultyComboBox;
    delete streakLabel;
    delete timerLabel;
    delete checkAnswerButton;
    delete startButton;
    delete answerInput;
    delete taskLabel;
}

void SpeedTrainingWindow::generateTask()
{
    int maxNumber = difficultyLevel * 50;
    int num1 = QRandomGenerator::global()->bounded(1, maxNumber);
    int num2 = QRandomGenerator::global()->bounded(1, maxNumber);

    switch (taskType) {
    case Addition:
        correctAnswer = num1 + num2;
        taskLabel->setText(QString("Сколько будет %1 + %2?").arg(num1).arg(num2));
        break;
    case Subtraction:
        correctAnswer = num1 - num2;
        taskLabel->setText(QString("Сколько будет %1 - %2?").arg(num1).arg(num2));
        break;
    case Multiplication:
        correctAnswer = num1 * num2;
        taskLabel->setText(QString("Сколько будет %1 * %2?").arg(num1).arg(num2));
        break;
    case Division:
        if (num2 == 0) num2 = 1;
        correctAnswer = num1 / num2;
        taskLabel->setText(QString("Сколько будет %1 / %2?").arg(num1).arg(num2));
        break;
    case Reading:
        generateReadingTask();
        break;
    case Logic:
        generateLogicTask();
        break;
    case Attention:
        generateAttentionTask();
        break;
    }

    remainingTime = maxTime;
    timerLabel->setText(QString("Время: %1").arg(remainingTime));
    timer->start(1000);
}

void SpeedTrainingWindow::generateReadingTask()
{
    readingText = "Внимание! Это пример текста для задачи на скорость чтения.";
    taskLabel->setText(readingText);
    correctAnswer = 1;
}

void SpeedTrainingWindow::generateLogicTask()
{
    QString question = "Что будет следующим числом в последовательности: 2, 4, 6, ?";
    taskLabel->setText(question);
    correctAnswer = 8;
}

void SpeedTrainingWindow::generateAttentionTask()
{
    taskLabel->setText("Найдите отличия на изображении.");
    correctAnswer = 3;
}

void SpeedTrainingWindow::generateMathTask()
{
}

void SpeedTrainingWindow::onStartButtonClicked()
{
    generateTask();
    startButton->setEnabled(false);
    checkAnswerButton->setEnabled(true);
}

void SpeedTrainingWindow::onTimerTimeout()
{
    if (remainingTime > 0) {
        remainingTime--;
        timerLabel->setText(QString("Время: %1").arg(remainingTime));
    }

    if (remainingTime <= 0) {
        timer->stop();
        QMessageBox::information(this, "Время вышло", "Вы не успели ответить!");
        currentStreak = 0;
        streakLabel->setText(QString("Стрик: %1").arg(currentStreak));
        resetTask();
    }
}

void SpeedTrainingWindow::onCheckAnswerButtonClicked()
{
    int userAnswer = answerInput->text().toInt();
    if (userAnswer == correctAnswer) {
        QMessageBox::information(this, "Правильный ответ", "Ответ правильный!");
        currentStreak++;
        streakLabel->setText(QString("Стрик: %1").arg(currentStreak));
    } else {
        QMessageBox::warning(this, "Неправильный ответ", "Ответ неправильный!");
        currentStreak = 0;
        streakLabel->setText(QString("Стрик: %1").arg(currentStreak));
    }
    resetTask();
}

void SpeedTrainingWindow::onDifficultyChanged(int index)
{
    difficultyLevel = index + 1; // Уровень сложности от 1 до 3
}

void SpeedTrainingWindow::onCategoryChanged(int index)
{
    categoryLevel = index;
    switch (categoryLevel) {
    case 0: // Математика
        taskType = Addition;
        break;
    case 1: // Чтение
        taskType = Reading;
        break;
    case 2: // Логика
        taskType = Logic;
        break;
    case 3: // Внимание
        taskType = Attention;
        break;
    }
}

void SpeedTrainingWindow::resetTask()
{
    answerInput->clear();
    startButton->setEnabled(true);
    checkAnswerButton->setEnabled(false);
}
