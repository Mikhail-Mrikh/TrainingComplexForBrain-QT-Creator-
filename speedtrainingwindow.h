#ifndef SPEEDTRAININGWINDOW_H
#define SPEEDTRAININGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QLineEdit>
#include <QVBoxLayout>

class SpeedTrainingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SpeedTrainingWindow(QWidget *parent = nullptr);
    ~SpeedTrainingWindow();

private slots:
    void onStartButtonClicked();
    void onTimerTimeout();
    void onCheckAnswerButtonClicked();

private:
    void generateTask();
    void resetTask();

    QLabel *taskLabel;
    QLineEdit *answerInput;
    QPushButton *startButton;
    QPushButton *checkAnswerButton;
    QTimer *timer;
    int currentTime;
    int correctAnswer;
    int maxTime;
};

#endif // SPEEDTRAININGWINDOW_H
