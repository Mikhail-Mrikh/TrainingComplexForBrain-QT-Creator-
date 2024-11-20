#ifndef MATHTRAININGWINDOW_H
#define MATHTRAININGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MathTrainingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MathTrainingWindow(QWidget *parent = nullptr);
    ~MathTrainingWindow();

private slots:
    void onSubmitAnswer();
    void onNextQuestion();

private:
    void generateQuestion();
    void updateStreakLabels();

    QLabel *questionLabel;          // Метка для задания
    QLineEdit *answerInput;         // Поле ввода ответа
    QPushButton *submitAnswerButton; // Кнопка "Проверить"
    QPushButton *nextQuestionButton; // Кнопка "Следующее задание"

    QLabel *currentStreakLabel;     // Метка текущего стрика
    QLabel *maxStreakLabel;         // Метка максимального стрика

    int correctAnswer;              // Правильный ответ
    int currentStreak;              // Текущий стрик
    int maxStreak;                  // Максимальный стрик
};

#endif // MATHTRAININGWINDOW_H
