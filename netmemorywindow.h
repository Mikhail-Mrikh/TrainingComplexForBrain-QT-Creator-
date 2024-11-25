#ifndef NETMEMORYWINDOW_H
#define NETMEMORYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class NetMemoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NetMemoryWindow(QWidget *parent = nullptr);
    ~NetMemoryWindow();

signals:
    void windowClosed(); // Сигнал для уведомления о закрытии окна

private slots:
    void on_checkButton_clicked();

private:
    QString sequence;
    int currentIndex;
    QLabel *sequenceLabel;    // Метка для отображения последовательности
    QLineEdit *inputField;    // Поле ввода для пользователя

    void generateSequence();  // Метод для генерации последовательности
    void updateSequenceLabel(); // Метод для обновления отображения последовательности

protected:
    void closeEvent(QCloseEvent *event) override; // Обрабатываем событие закрытия

};

#endif // NETMEMORYWINDOW_H
