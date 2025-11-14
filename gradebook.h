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
    // score modifiers applied from user input
    float                latePenaltyHomework_;
    // percentage multipliers applied to Assignment categories for calculating course grade
    int                  weightHomework_ = 0;
    int                  weightExam_     = 0;

    int         gradeWeight(AssignmentType type);
    void        setGradeWeight(AssignmentType type, int newWeight);
    int         nextAssignmentID();
    Assignment* createAssignment(AssignmentType assignmentType, int id);
    Assignment* getAssignmentByID(int id);
    bool        deleteAssignment(int id); // Returns true if successful.
    float       categoryEffPointsAwarded(AssignmentType assignmentType);
    float       categoryMaxPoints(AssignmentType assignmentType);
    float       coursePercent();
    void        updateDisplayedCalcs();
    QString     letterGrade(float percent);

public:
    Gradebook(QWidget *parent = nullptr);
    ~Gradebook();

private slots:
    void on_btnAddNewHomework_clicked();
    void on_btnAddNewExam_clicked();
    void on_tableHomeworks_cellChanged(int row, int column);
    void on_tableExams_cellChanged(int row, int column);
    void on_hwWeight_textEdited(const QString &arg1);
    void on_examWeight_textEdited(const QString &arg1);

private:
    Ui::Gradebook *ui;
};
#endif // GRADEBOOK_H
