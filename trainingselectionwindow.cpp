#include "trainingselectionwindow.h"
#include "ui_trainingselectionwindow.h"

TrainingSelectionWindow::TrainingSelectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingSelectionWindow)
{
    ui->setupUi(this);
}

TrainingSelectionWindow::~TrainingSelectionWindow()
{
    delete ui;
}
