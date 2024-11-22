#include "mathtrainingwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

MathTrainingWindow::MathTrainingWindow(QWidget *parent) :
    QDialog(parent),
    taskLabel(new QLabel(this)),
    answerInput(new QLineEdit(this)),
    startButton(new QPushButton("Начать тренировку", this)),
    checkAnswerButton(new QPushButton("Проверить ответ", this)),
    timerLabel(new QLabel("Время: 0", this)),
    streakLabel(new QLabel("Счет: 0", this)),
    difficultyComboBox(new QComboBox(this)),
    operationComboBox(new QComboBox(this)),
    timer(new QTimer(this)),
    correctAnswer(0),
    currentTime(0),
    remainingTime(10),
    currentStreak(0),
    maxStreak(0),
    difficultyLevel(1),
    currentOperation(Addition)
{
    setWindowTitle("Тренировка по математике");

    difficultyComboBox->addItem("Легкий");
    difficultyComboBox->addItem("Средний");
    difficultyComboBox->addItem("Сложный");

    operationComboBox->addItem("Сложение");
    operationComboBox->addItem("Вычитание");
    operationComboBox->addItem("Умножение");
    operationComboBox->addItem("Деление");
    operationComboBox->addItem("Сложные выражения");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Выберите уровень сложности:", this));
    layout->addWidget(difficultyComboBox);
    layout->addWidget(new QLabel("Выберите тип операции:", this));
    layout->addWidget(operationComboBox);
    layout->addWidget(taskLabel);
    layout->addWidget(answerInput);
    layout->addWidget(timerLabel);
    layout->addWidget(streakLabel);
    layout->addWidget(startButton);
    layout->addWidget(checkAnswerButton);

    connect(startButton, &QPushButton::clicked, this, &MathTrainingWindow::onStartButtonClicked);
    connect(checkAnswerButton, &QPushButton::clicked, this, &MathTrainingWindow::onCheckAnswerButtonClicked);
    connect(timer, &QTimer::timeout, this, &MathTrainingWindow::onTimerTimeout);
    connect(difficultyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MathTrainingWindow::onDifficultyChanged);
    connect(operationComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MathTrainingWindow::onOperationChanged);

    checkAnswerButton->setEnabled(false);
}

MathTrainingWindow::~MathTrainingWindow() {}

void MathTrainingWindow::generateTask()
{
    int maxNumber = difficultyLevel * 50;
    int num1 = QRandomGenerator::global()->bounded(1, maxNumber);
    int num2 = QRandomGenerator::global()->bounded(1, maxNumber);

    switch (currentOperation) {
    case Addition:
        correctAnswer = num1 + num2;
        taskLabel->setText(QString("%1 + %2 = ?").arg(num1).arg(num2));
        break;

    case Subtraction:
        correctAnswer = num1 - num2;
        taskLabel->setText(QString("%1 - %2 = ?").arg(num1).arg(num2));
        break;

    case Multiplication:
        correctAnswer = num1 * num2;
        taskLabel->setText(QString("%1 * %2 = ?").arg(num1).arg(num2));
        break;

    case Division:
        if (num2 == 0) num2 = 1; // Защита от деления на ноль
        correctAnswer = num1 / num2;
        taskLabel->setText(QString("%1 / %2 = ? (целое)").arg(num1).arg(num2));
        break;

    case Complex:
        int num3 = QRandomGenerator::global()->bounded(1, maxNumber);
        correctAnswer = (num1 + num2) * num3;
        taskLabel->setText(QString("(%1 + %2) * %3 = ?").arg(num1).arg(num2).arg(num3));
        break;
    }

    remainingTime = 10;
    timerLabel->setText(QString("Время: %1").arg(remainingTime));
    timer->start(1000);
}

void MathTrainingWindow::onStartButtonClicked()
{
    generateTask();
    startButton->setEnabled(false);
    checkAnswerButton->setEnabled(true);
}

void MathTrainingWindow::onCheckAnswerButtonClicked()
{
    bool isCorrect = answerInput->text().toInt() == correctAnswer;

    if (isCorrect) {
        QMessageBox::information(this, "Правильно!", "Ответ верный!");
        currentStreak++;
        streakLabel->setText(QString("Счет: %1").arg(currentStreak));

        if (currentStreak > maxStreak) {
            maxStreak = currentStreak;
            emit maxMathStreakUpdated(maxStreak); // Отправляем сигнал
        }

        generateTask();
    } else {
        QMessageBox::warning(this, "Неправильно", "Попробуйте снова.");
        currentStreak = 0;
        streakLabel->setText(QString("Счет: %1").arg(currentStreak));
    }
    answerInput->clear();
}

void MathTrainingWindow::onTimerTimeout()
{
    remainingTime--;
    timerLabel->setText(QString("Время: %1").arg(remainingTime));

    if (remainingTime == 0) {
        timer->stop();
        QMessageBox::information(this, "Время вышло", "Вы не успели дать ответ!");
        resetTask();
    }
}

void MathTrainingWindow::resetTask()
{
    taskLabel->clear();
    answerInput->clear();
    startButton->setEnabled(true);
    checkAnswerButton->setEnabled(false);
}

void MathTrainingWindow::onDifficultyChanged(int index)
{
    difficultyLevel = index + 1;
    QMessageBox::information(this, "Сложность изменена", QString("Вы выбрали: %1").arg(difficultyComboBox->currentText()));
    resetTask();
}

void MathTrainingWindow::onOperationChanged(int index)
{
    currentOperation = static_cast<MathOperation>(index);
    resetTask();
}
