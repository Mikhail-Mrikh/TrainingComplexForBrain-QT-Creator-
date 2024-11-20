#include "mathtrainingwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

MathTrainingWindow::MathTrainingWindow(QWidget *parent) :
    QDialog(parent),
    questionLabel(new QLabel(this)),
    answerInput(new QLineEdit(this)),
    submitAnswerButton(new QPushButton("Проверить", this)),
    nextQuestionButton(new QPushButton("Следующее задание", this)),
    currentStreak(0),   // Начальное значение текущего стрика
    maxStreak(0)        // Начальное значение максимального стрика
{
    setWindowTitle("Математическая тренировка");

    // Создаем основной вертикальный layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Настройка элементов интерфейса
    questionLabel->setAlignment(Qt::AlignCenter);
    questionLabel->setStyleSheet("font-size: 2em; font-weight: bold;"); // Пропорциональный размер шрифта
    questionLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    answerInput->setPlaceholderText("Введите ваш ответ");
    answerInput->setStyleSheet("font-size: 1.5em;"); // Пропорциональный размер шрифта
    answerInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    submitAnswerButton->setStyleSheet("font-size: 1.5em;");
    submitAnswerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    nextQuestionButton->setStyleSheet("font-size: 1.5em;");
    nextQuestionButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Счетчики
    currentStreakLabel = new QLabel("Текущий стрик: 0", this);
    maxStreakLabel = new QLabel("Максимальный стрик: 0", this);
    currentStreakLabel->setStyleSheet("font-size: 1.2em;");
    maxStreakLabel->setStyleSheet("font-size: 1.2em;");

    // Горизонтальный layout для строки ввода ответа
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(answerInput);
    inputLayout->setAlignment(Qt::AlignCenter);

    // Горизонтальный layout для кнопок
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(submitAnswerButton);
    buttonsLayout->addWidget(nextQuestionButton);
    buttonsLayout->setSpacing(20); // Отступ между кнопками
    buttonsLayout->setAlignment(Qt::AlignCenter);

    // Добавляем элементы в основной layout
    mainLayout->addWidget(questionLabel, 1);       // Вопрос с весом 1
    mainLayout->addLayout(inputLayout);            // Поле ввода
    mainLayout->addLayout(buttonsLayout);          // Кнопки
    mainLayout->addWidget(currentStreakLabel);     // Счетчик текущего стрика
    mainLayout->addWidget(maxStreakLabel);         // Счетчик максимального стрика

    // Подключение сигналов к слотам
    connect(submitAnswerButton, &QPushButton::clicked, this, &MathTrainingWindow::onSubmitAnswer);
    connect(nextQuestionButton, &QPushButton::clicked, this, &MathTrainingWindow::onNextQuestion);

    // Генерация первого задания
    generateQuestion();
}

MathTrainingWindow::~MathTrainingWindow()
{
    // Все элементы будут автоматически удалены, так как их родителем является окно
}

void MathTrainingWindow::generateQuestion()
{
    // Генерируем два случайных числа
    int num1 = QRandomGenerator::global()->bounded(1, 100);
    int num2 = QRandomGenerator::global()->bounded(1, 100);

    // Вычисляем правильный ответ
    correctAnswer = num1 + num2;

    // Устанавливаем текст задания
    questionLabel->setText(QString("%1 + %2 = ?").arg(num1).arg(num2));
}

void MathTrainingWindow::onSubmitAnswer()
{
    QString userAnswer = answerInput->text();

    if (userAnswer.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ваш ответ.");
        return;
    }

    if (userAnswer.toInt() == correctAnswer) {
        QMessageBox::information(this, "Правильно", "Ответ верный!");

        // Увеличиваем текущий стрик
        currentStreak++;
        if (currentStreak > maxStreak) {
            maxStreak = currentStreak; // Обновляем максимальный стрик
        }

        // Обновляем отображение стриков
        updateStreakLabels();

        // Генерируем следующее задание
        generateQuestion();
        answerInput->clear();
    } else {
        QMessageBox::critical(this, "Неправильно", "Ответ неверный. Попробуйте снова.");

        // Сбрасываем текущий стрик
        currentStreak = 0;
        updateStreakLabels();
    }
}

void MathTrainingWindow::onNextQuestion()
{
    generateQuestion();
    answerInput->clear();
}

void MathTrainingWindow::updateStreakLabels()
{
    // Обновляем текст на счетчиках
    currentStreakLabel->setText(QString("Текущий стрик: %1").arg(currentStreak));
    maxStreakLabel->setText(QString("Максимальный стрик: %1").arg(maxStreak));
}
