#include "speedtrainingwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVBoxLayout>

SpeedTrainingWindow::SpeedTrainingWindow(QWidget *parent) :
    QDialog(parent),
    taskLabel(new QLabel(this)),
    answerInput(new QLineEdit(this)),
    startButton(new QPushButton("Начать тренировку", this)),
    checkAnswerButton(new QPushButton("Проверить ответ", this)),
    timer(new QTimer(this)),
    currentTime(0),
    correctAnswer(0),
    maxTime(0)
{
    setWindowTitle("Тренировка на скорость");
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(taskLabel);
    layout->addWidget(answerInput);
    layout->addWidget(startButton);
    layout->addWidget(checkAnswerButton);

    connect(startButton, &QPushButton::clicked, this, &SpeedTrainingWindow::onStartButtonClicked);
    connect(checkAnswerButton, &QPushButton::clicked, this, &SpeedTrainingWindow::onCheckAnswerButtonClicked);
    connect(timer, &QTimer::timeout, this, &SpeedTrainingWindow::onTimerTimeout);

    checkAnswerButton->setEnabled(false);  // Сначала кнопка проверки ответа неактивна
}

SpeedTrainingWindow::~SpeedTrainingWindow()
{
}

void SpeedTrainingWindow::generateTask()
{
    // Генерируем задание (например, простое вычисление)
    int num1 = QRandomGenerator::global()->bounded(1, 100);
    int num2 = QRandomGenerator::global()->bounded(1, 100);

    correctAnswer = num1 + num2;
    taskLabel->setText(QString("Сколько будет %1 + %2?").arg(num1).arg(num2));

    currentTime = 0;  // Сбрасываем время
    timer->start(1000);  // Запускаем таймер (каждую секунду)
}

void SpeedTrainingWindow::onStartButtonClicked()
{
    // Запускаем тренировку, генерируем первое задание
    generateTask();
    startButton->setEnabled(false);  // Отключаем кнопку старта
    checkAnswerButton->setEnabled(true);  // Включаем кнопку для проверки ответа
}

void SpeedTrainingWindow::onTimerTimeout()
{
    currentTime++;  // Увеличиваем счетчик времени
    if (currentTime > maxTime) {
        maxTime = currentTime;  // Обновляем максимальное время
    }
}

void SpeedTrainingWindow::onCheckAnswerButtonClicked()
{
    bool isCorrect = answerInput->text().toInt() == correctAnswer;

    if (isCorrect) {
        QMessageBox::information(this, "Правильный ответ", "Вы дали правильный ответ!");
        timer->stop();  // Останавливаем таймер
        startButton->setEnabled(true);  // Включаем кнопку старта для следующего задания
        answerInput->clear();  // Очищаем поле ввода
    } else {
        QMessageBox::warning(this, "Неправильный ответ", "Попробуйте снова.");
    }
}

void SpeedTrainingWindow::resetTask()
{
    taskLabel->clear();
    answerInput->clear();
    startButton->setEnabled(true);
    checkAnswerButton->setEnabled(false);
    timer->stop();
}
