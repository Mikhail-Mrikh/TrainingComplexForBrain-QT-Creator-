#ifndef LANGUAGETRAININGWINDOW_H
#define LANGUAGETRAININGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QStringList>
#include <QSqlDatabase>

class LanguageTrainingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageTrainingWindow(QWidget *parent = nullptr);
    ~LanguageTrainingWindow();

private:
    QLabel *taskLabel;
    QLineEdit *answerInput;
    QPushButton *startButton;
    QPushButton *checkAnswerButton;
    QLabel *timerLabel;
    QTimer *timer;

    int remainingTime;
    QString currentWord;
    QString correctTranslation;

    QSqlDatabase db;

    bool initializeDatabase();
    bool addWord(const QString &word, const QString &translation);
    bool addUser(const QString &username, const QString &password);

    QStringList getWords();

    void generateTask();
    void resetTask();

private slots:
    void onStartButtonClicked();
    void onCheckAnswerButtonClicked();
    void onTimerTimeout();
};

#endif // LANGUAGETRAININGWINDOW_H
