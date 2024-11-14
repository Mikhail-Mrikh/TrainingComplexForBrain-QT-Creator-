#ifndef TRAININGSELECTIONWINDOW_H
#define TRAININGSELECTIONWINDOW_H

#include <QDialog>

namespace Ui {
class TrainingSelectionWindow;
}

class TrainingSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingSelectionWindow(QWidget *parent = nullptr);
    ~TrainingSelectionWindow();

private:
    Ui::TrainingSelectionWindow *ui;
};

#endif // TRAININGSELECTIONWINDOW_H
