#ifndef MATHTRAININGWINDOW_H
#define MATHTRAININGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QTimer>

class MathTrainingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MathTrainingWindow(QWidget *parent = nullptr);
    ~MathTrainingWindow();

signals:
    void maxMathStreakUpdated(int maxStreak);


private slots:
    void onStartButtonClicked();
    void onCheckAnswerButtonClicked();
    void onTimerTimeout();
    void onDifficultyChanged(int index);
    void onOperationChanged(int index);

private:
    enum MathOperation {
        Addition,
        Subtraction,
        Multiplication,
        Division,
        Complex
    };

    void generateTask();
    void resetTask();
    void endTraining();

    QLabel *taskLabel;
    QLineEdit *answerInput;
    QPushButton *startButton;
    QPushButton *checkAnswerButton;
    QLabel *timerLabel;
    QLabel *streakLabel;
    QComboBox *difficultyComboBox;
    QComboBox *operationComboBox;
    QTimer *timer;

    int correctAnswer;
    int currentTime;
    int remainingTime;
    int currentStreak;
    int maxStreak;
    int difficultyLevel;
    MathOperation currentOperation;
};

#endif // MATHTRAININGWINDOW_H
