#ifndef SPEEDTRAININGWINDOW_H
#define SPEEDTRAININGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QList>

class SpeedTrainingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SpeedTrainingWindow(QWidget *parent = nullptr);
    ~SpeedTrainingWindow();

private slots:
    void onStartButtonClicked();
    void onCheckAnswerButtonClicked();
    void onTimerTimeout();
    void onDifficultyChanged(int index);
    void onCategoryChanged(int index);

private:
    void generateTask();
    void resetTask();
    void generateReadingTask();
    void generateLogicTask();
    void generateAttentionTask();
    void generateMathTask();

    QLabel *taskLabel;
    QLineEdit *answerInput;
    QPushButton *startButton;
    QPushButton *checkAnswerButton;
    QLabel *timerLabel;
    QLabel *streakLabel;
    QComboBox *difficultyComboBox;
    QComboBox *categoryComboBox;
    QTimer *timer;

    int currentTime;
    int correctAnswer;
    int maxTime;
    int remainingTime;
    int currentStreak;
    int maxStreak;
    int difficultyLevel;
    int categoryLevel; // Уровень категории

    enum TaskType {
        Addition,
        Subtraction,
        Multiplication,
        Division,
        Reading,
        Logic,
        Attention
    };

    TaskType taskType;
    QString readingText;
    QList<int> memorySequence;
};

#endif // SPEEDTRAININGWINDOW_H
