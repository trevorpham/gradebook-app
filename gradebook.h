#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include "exam.h"
#include "homework.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gradebook;
}
QT_END_NAMESPACE

class Gradebook : public QMainWindow
{
    Q_OBJECT
    QVector<Homework> m_homeworks;
    QVector<Exam>     m_exams;

public:
    Gradebook(QWidget *parent = nullptr);
    QString calcLetterGrade(float);
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
