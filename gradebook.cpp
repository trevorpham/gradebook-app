#include "gradebook.h"
#include "exam.h"
#include "homework.h"
#include "ui_gradebook.h"
#include <QLineEdit>
#include<QTextEdit>
#include <QCheckBox>

Gradebook::Gradebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gradebook)
{
    ui->setupUi(this);
    ui->tableHomeworks->verticalHeader()->setVisible(false);
    ui->tableExams->verticalHeader()->setVisible(false);
}

int Gradebook::nextAssignmentID()
{
    static int s_nextID = 1;
    return s_nextID++;
}

Assignment* Gradebook::createAssignment(AssignmentType type, int id)
{
    switch(type) {
    case HOMEWORK:
        return new Homework(id);
    case EXAM:
        return new Exam(id);
    default:
        return nullptr;
    }
}

bool Gradebook::deleteAssignment(int id)
// Deletes an assignment with specified id. Returns true if successful.
{
    for (int i = 0; i < assignments_.size(); i++)
    {
        if (assignments_.at(i)->id() == id)
        {
            delete assignments_.at(i);
            assignments_.remove(i);
            return true;
        }
    }
    return false;
}

QString Gradebook::letterGrade(float percent)
{
    if (percent >= .90) return QString("A");
    if (percent >= .80) return QString("B");
    if (percent >= .70) return QString("C");
    if (percent >= .60) return QString("D");
    else return QString("F");
}

Gradebook::~Gradebook()
{
    while (!assignments_.isEmpty()) delete assignments_.takeLast();
    delete ui;
}

float Gradebook::categoryEffPointsAwarded(AssignmentType type)
{
    float sum = 0.f;
    for (int i = 0; i < assignments_.size(); i++)
    {
        if (assignments_.at(i)->type() == type) {
            sum += assignments_.at(i)->effectivePointsAwarded();
        }
    }
    return sum;
}

float Gradebook::categoryMaxPoints(AssignmentType type)
{
    float sum = 0.f;
    for (int i = 0; i < assignments_.size(); i++)
    {
        if (assignments_.at(i)->type() == type) {
            sum += assignments_.at(i)->pointsMax();
        }
    }
    return sum;
}

void Gradebook::updateDisplayedCalcs()
{
    float effHWPointsAwarded = categoryEffPointsAwarded(HOMEWORK);
    float maxHWPoints = categoryMaxPoints(HOMEWORK);
    float HWPercent = (effHWPointsAwarded / maxHWPoints) * 100;

    float effExamPointsAwarded = categoryEffPointsAwarded(EXAM);
    float maxExamPoints = categoryMaxPoints(EXAM);
    float examPercent = (effExamPointsAwarded / maxExamPoints) * 100;


    ui->totalHomeworkPtsAwarded->setText(QString::number(effHWPointsAwarded));
    ui->totalHomeworkPtsMax->setText(QString::number(maxHWPoints));
    ui->totalHomeworkPercent->setText(QString::number(HWPercent).append("%"));

    ui->totalExamPtsAwarded->setText(QString::number(effExamPointsAwarded));
    ui->totalExamPtsMax->setText(QString::number(maxExamPoints));
    ui->totalExamPercent->setText(QString::number(examPercent).append("%"));
}

void Gradebook::updateDisplayedCalcs(AssignmentType type)
{
    float effPointsAwarded = categoryEffPointsAwarded(type);
    float maxPoints = categoryMaxPoints(type);
    float categoryPercent = (effPointsAwarded / maxPoints) * 100;

    switch(type) {
    case HOMEWORK:
        ui->totalHomeworkPtsAwarded->setText(QString::number(effPointsAwarded));
        ui->totalHomeworkPtsMax->setText(QString::number(maxPoints));
        ui->totalHomeworkPercent->setText(QString::number(categoryPercent));
        break;
    case EXAM:
        ui->totalExamPtsAwarded->setText(QString::number(effPointsAwarded));
        ui->totalExamPtsMax->setText(QString::number(maxPoints));
        ui->totalExamPercent->setText(QString::number(categoryPercent));
        break;
    default:
        break;
    }
}

void Gradebook::on_btnAddNewExam_clicked()
{
    Assignment* a = createAssignment(EXAM, nextAssignmentID());
    assignments_.push_back(a);

    int row = ui->tableExams->rowCount();
    ui->tableExams->insertRow(row);
    QCheckBox* checkBoxIgnore = new QCheckBox(ui ->tableExams);
    ui->tableExams->setCellWidget(row, 3, checkBoxIgnore);
    connect(checkBoxIgnore, &QCheckBox::toggled, this, [this, a]{
        a->setIsIgnored();
        updateDisplayedCalcs(EXAM);
    });
}

void Gradebook::on_tableExams_cellChanged(int row, int column) {
    // switch statement here...call the correct setter depending on column number
    updateDisplayedCalcs(EXAM);
}

void Gradebook::on_btnAddNewHomework_clicked()
{
    Assignment* a = createAssignment(HOMEWORK, nextAssignmentID());
    assignments_.push_back(a);

    int row = ui->tableHomeworks->rowCount();
    ui->tableHomeworks->insertRow(row);
    QCheckBox* checkBoxIgnore = new QCheckBox(ui->tableHomeworks);
    ui->tableHomeworks->setCellWidget(row, 3, checkBoxIgnore);
    connect(checkBoxIgnore, &QCheckBox::toggled, this, [this, a]{
        a->setIsIgnored();
        updateDisplayedCalcs(HOMEWORK);
    });
}

void Gradebook::on_tableHomeworks_cellChanged(int row, int column) {
    // switch statement here...call the correct setter depending on column number
    updateDisplayedCalcs(HOMEWORK);
}


// // START OF EXAM
// void Gradebook::recomputeExam()
// {
//     QTableWidget* Exam = ui ->tableExams;
//     int rowCount = ui->tableExams->rowCount();
//     int colCount = ui->tableExams->columnCount();
//     int pointAwardedCol = 1;
//     int pointMaxCol = 2;
//     float pointAwardedSum = 0;
//     float pointMaxSum = 0;
//     float percent = 0;

//     for (int i=0; i<rowCount; i++) {
//         QTableWidgetItem* itemPointAwarded = ui->tableExams->item(i, pointAwardedCol);
//         QTableWidgetItem* itemPointMax = ui->tableExams->item(i, pointMaxCol);

//         QCheckBox* Box = qobject_cast<QCheckBox*>(Exam->cellWidget(i,3));
//         if(Box && Box->isChecked()){
//             continue;
//         }

//         if (itemPointAwarded) {
//             float itemValue = itemPointAwarded->text().toFloat();
//             pointAwardedSum += itemValue;
//         }
//         if (itemPointMax) {
//             float itemValue = itemPointMax->text().toFloat();
//             pointMaxSum += itemValue;
//         }
//     }


//     ui->totalExamPtsAwarded->setText(QString::number(pointAwardedSum));
//     ui->totalExamPtsMax->setText(QString::number(pointMaxSum));

//     if (pointMaxSum != 0) {
//         percent = pointAwardedSum / pointMaxSum;
//         ui->totalExamPercent->setText(QString::number(percent * 100).append("%"));
//     }

//     float Test_Hw = ui->Test_HW2->text().toFloat();
//     float Test_Exam = ui->Test_Exam2->text().toFloat();

//     float homeworkPoints = ui->totalHomeworkPtsAwarded->text().toFloat();
//     float totalPointsAwarded = (pointAwardedSum*Test_Exam) + (homeworkPoints*Test_Hw); // grade calculation w weigth
//     ui->totalPtsAwarded->setText(QString::number(totalPointsAwarded));

//     float homeworkMaxPoints = ui->totalHomeworkPtsMax->text().toFloat();
//     float totalPointsMax = (pointMaxSum*Test_Exam) + (homeworkMaxPoints*Test_Hw); // something here?
//     ui->totalPtsMax->setText(QString::number(totalPointsMax));

//     float totalPercent = totalPointsAwarded / totalPointsMax;
//     ui->totalPercent->setText(QString::number(totalPercent * 100).append("%"));

//     QString letterGrade = calcLetterGrade(totalPercent);
//     ui->letterGrade->setText(letterGrade);
// }


