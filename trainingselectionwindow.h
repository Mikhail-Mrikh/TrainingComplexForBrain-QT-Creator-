#ifndef TRAININGSELECTIONWINDOW_H
#define TRAININGSELECTIONWINDOW_H

#include <QDialog>
#include <QSqlQuery>
#include <QPixmap>
#include <QLabel>

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

private:
    Ui::TrainingSelectionWindow *ui;

    QDialog *profileDialog;
    QString currentUsername;
    QString currentName;
    QPixmap currentImage;
    int currentMaxMathStreak = 0;
};

#endif // TRAININGSELECTIONWINDOW_H
