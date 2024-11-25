#include "netmemorywindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QRandomGenerator>

NetMemoryWindow::NetMemoryWindow(QWidget *parent)
    : QWidget(parent), currentIndex(0)
{
    setWindowTitle("Net Memory Training");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Метка для отображения последовательности
    QLabel *instructionLabel = new QLabel("Запомните последовательность:", this);
    layout->addWidget(instructionLabel);

    sequenceLabel = new QLabel(this);
    layout->addWidget(sequenceLabel);

    // Поле ввода для пользователя
    inputField = new QLineEdit(this);
    layout->addWidget(inputField);

    // Кнопка "Проверить"
    QPushButton *checkButton = new QPushButton("Проверить", this);
    layout->addWidget(checkButton);

    // Соединяем кнопку с проверкой
    connect(checkButton, &QPushButton::clicked, this, &NetMemoryWindow::on_checkButton_clicked);

    // Генерация последовательности
    generateSequence();
    updateSequenceLabel();
}

NetMemoryWindow::~NetMemoryWindow()
{
}

void NetMemoryWindow::generateSequence()
{
    // Генерация последовательности из 10 символов
    sequence.clear();
    for (int i = 0; i < 10; ++i)
    {
        int randomChar = QRandomGenerator::global()->bounded(0, 10); // Числа от 0 до 9
        sequence.append(QString::number(randomChar));
    }
}

void NetMemoryWindow::updateSequenceLabel()
{
    // Показываем последовательность
    sequenceLabel->setText(sequence);
}

void NetMemoryWindow::on_checkButton_clicked()
{
    QString userInput = inputField->text();

    if (userInput == sequence)
    {
        QMessageBox::information(this, "Результат", "Вы правильно запомнили последовательность!");
    }
    else
    {
        QMessageBox::warning(this, "Результат", "Вы ошиблись. Попробуйте ещё раз.");
    }

    // Сбрасываем поле ввода
    inputField->clear();
    // Генерируем новую последовательность
    generateSequence();
    updateSequenceLabel();
}

void NetMemoryWindow::closeEvent(QCloseEvent *event)
{
    emit windowClosed(); // Уведомляем главное окно
    QWidget::closeEvent(event);
}
