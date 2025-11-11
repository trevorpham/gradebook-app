#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include "assignment.h"
#include <QMainWindow>

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
    int weightHomework_;
    int weightExam_;

public:
    Gradebook(QWidget *parent = nullptr);
    QString calcLetterGrade(float percent);
    int nextAssignmentID();
    bool deleteAssignment(int id); // Returns true if successful.
    ~Gradebook();

private slots:
    void on_btnAddNewHomework_clicked();

    void on_btnAddNewExam_clicked();

    void on_tableHomeworks_cellChanged(int row, int column);

    void on_tableExams_cellChanged(int row, int column);

    void recomputeHW();

    void recomputeExam();


private:
    Ui::Gradebook *ui;
};
#endif // GRADEBOOK_H
