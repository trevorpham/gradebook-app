#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include "assignment.h"
#include <QString>
#include <QVector>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTableWidget>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gradebook;
}
QT_END_NAMESPACE

class Gradebook : public QMainWindow
{
    Q_OBJECT
    QVector<Assignment*> assignments_;
    float latePenaltyHomework_;
    float weightHomework_;
    float weightExam_;

public:
    Gradebook(QWidget *parent = nullptr);
    QString calcLetterGrade(float);
    int nextAssignmentID();
    ~Gradebook();

private slots:
    void on_btnAddNewHomework_clicked();

    void on_btnAddNewExam_clicked();

    void on_tableHomeworks_cellChanged(int row, int column);

    void on_tableExams_cellChanged(int row, int column);

    void GradeCalculation();


private:
    Ui::Gradebook *ui;
    QMenu* addMenu = nullptr;
    QAction* addHW = nullptr;
    QAction* addEXAM = nullptr;
};
#endif // GRADEBOOK_H
