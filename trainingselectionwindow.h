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

    void setUserProfile(const QString &username, const QString &name, const QPixmap &image);

private slots:
    void on_mathTrainingButton_clicked();
    void on_speedTrainingButton_clicked();


    void on_offButton_clicked();

    void on_viewProfileButton_clicked();

private:
    Ui::TrainingSelectionWindow *ui;

    QString currentUsername;
    QString currentName;
    QPixmap currentImage;
};

#endif // TRAININGSELECTIONWINDOW_H
