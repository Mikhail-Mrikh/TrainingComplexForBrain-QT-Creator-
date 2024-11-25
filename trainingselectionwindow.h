#ifndef TRAININGSELECTIONWINDOW_H
#define TRAININGSELECTIONWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QWidget>
#include <QPushButton>
#include "ui_trainingselectionwindow.h"

class NetMemoryWindow;  // Добавляем объявление класса NetMemoryWindow

namespace Ui {
class TrainingSelectionWindow;
}

class TrainingSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingSelectionWindow(QWidget *parent = nullptr);
    ~TrainingSelectionWindow();

    void setUserProfile(const QString &username, const QString &name, const QPixmap &image, int maxMathStreak);
    void updateMaxMathStreak(int newMaxMathStreak);

private slots:
    void on_mathTrainingButton_clicked();
    void on_speedTrainingButton_clicked();
    void on_backButton_clicked();
    void on_viewProfileButton_clicked();
    void on_questButtonThirdWindow_clicked();
    void on_languageTrainingButton_clicked();
    void on_NetMemoryButton_clicked();

private:
    Ui::TrainingSelectionWindow *ui;
    QDialog *profileDialog;
    QString currentUsername;
    QString currentName;
    QPixmap currentImage;
    int currentMaxMathStreak;
    NetMemoryWindow *netMemoryTraining; // Указатель на окно "Net Memory"
};

#endif // TRAININGSELECTIONWINDOW_H
