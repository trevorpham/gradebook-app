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

QString Gradebook::calcLetterGrade(float percent)
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

void Gradebook::on_btnAddNewHomework_clicked()
{
    int row = ui->tableHomeworks->rowCount();
    // create Assignment object
    // Assignment* a = createAssignment<Homework>(nextAssignmentID());
    // assignments_.push_back(a);
    // int id = a->id();
    ui->tableHomeworks->insertRow(row);
    QCheckBox* checkBoxIgnore = new QCheckBox(ui->tableHomeworks);
    QPushButton* checkBoxDelete = new QPushButton(ui->tableHomeworks);
    ui->tableHomeworks->setCellWidget(row, 3, checkBoxIgnore);
    ui->tableHomeworks->setCellWidget(row, 4, checkBoxDelete);
    connect(checkBoxIgnore, &QCheckBox::toggled, this, [this]{ recomputeHW(); });
    // connect(checkBoxDelete, &QPushButton::clicked, this, [this, id]{ deleteAssignment(id); });
    connect(ui->Test_HW2, &QLineEdit::textChanged, this, [this]{recomputeHW();});
}

void Gradebook::on_tableHomeworks_cellChanged(int row,int column){
    recomputeHW();
}


// START OF HOMEWORK


void Gradebook::recomputeHW()
{
    QTableWidget* HW = ui->tableHomeworks;
    int rowCount = ui->tableHomeworks->rowCount();
    int colCount = ui->tableHomeworks->columnCount();
    int pointAwardedCol = 1;
    int pointMaxCol = 2;
    float pointAwardedSum = 0;
    float pointMaxSum = 0;
    float percent = 0;

    for (int i=0; i<rowCount; i++) {
        QTableWidgetItem* itemPointAwarded = ui->tableHomeworks->item(i, pointAwardedCol);
        QTableWidgetItem* itemPointMax = ui->tableHomeworks->item(i, pointMaxCol);
        QCheckBox* Box = qobject_cast<QCheckBox*>(HW->cellWidget(i,3));
        if(Box && Box->isChecked()){
            continue;
        }

        if (itemPointAwarded) {
            float itemValue = itemPointAwarded->text().toFloat();
            pointAwardedSum += itemValue;
        }
        if (itemPointMax) {
            float itemValue = itemPointMax->text().toFloat();
            pointMaxSum += itemValue;
        }

    }

    ui->totalHomeworkPtsAwarded->setText(QString::number(pointAwardedSum));
    ui->totalHomeworkPtsMax->setText(QString::number(pointMaxSum));

    if (pointMaxSum != 0) {
        percent = pointAwardedSum / pointMaxSum;
        ui->totalHomeworkPercent->setText(QString::number(percent * 100).append("%"));
    }


    float Test_Hw = ui->Test_HW2->text().toFloat();
    float Test_Exam = ui->Test_Exam2->text().toFloat();

    float examPoints = ui->totalExamPtsAwarded->text().toFloat();
    float totalPointsAwarded = (pointAwardedSum*Test_Hw) + (examPoints*Test_Exam); //  CHANGE HERE grade calculation with weight
    ui->totalPtsAwarded->setText(QString::number(totalPointsAwarded));

    float examMaxPoints = ui->totalExamPtsMax->text().toFloat();
    float totalPointsMax = (pointMaxSum*Test_Hw) + (examMaxPoints*Test_Exam);
    ui->totalPtsMax->setText(QString::number(totalPointsMax));

    float totalPercent = totalPointsAwarded / totalPointsMax;
    ui->totalPercent->setText(QString::number(totalPercent * 100).append("%"));

    QString letterGrade = calcLetterGrade(totalPercent);
    ui->letterGrade->setText(letterGrade);
}

// MOVE THIS HERE FOR NOW
void Gradebook::on_btnAddNewExam_clicked()
{
    //ui->tableExams->insertRow(ui->tableExams->rowCount());

    int row = ui->tableExams->rowCount();
    ui->tableExams->insertRow(row);
    QCheckBox* checkBox = new QCheckBox(ui ->tableExams);
    ui->tableExams->setCellWidget(row, 3, checkBox);
    connect(checkBox, &QCheckBox::toggled, this, [this]{ recomputeExam(); });
    connect(ui->Test_Exam2, &QLineEdit::textChanged, this, [this]{recomputeExam();});

}

void Gradebook::on_tableExams_cellChanged(int row, int column){
    recomputeExam();
}


// START OF EXAM
void Gradebook::recomputeExam()
{
    QTableWidget* Exam = ui ->tableExams;
    int rowCount = ui->tableExams->rowCount();
    int colCount = ui->tableExams->columnCount();
    int pointAwardedCol = 1;
    int pointMaxCol = 2;
    float pointAwardedSum = 0;
    float pointMaxSum = 0;
    float percent = 0;

    for (int i=0; i<rowCount; i++) {
        QTableWidgetItem* itemPointAwarded = ui->tableExams->item(i, pointAwardedCol);
        QTableWidgetItem* itemPointMax = ui->tableExams->item(i, pointMaxCol);

        QCheckBox* Box = qobject_cast<QCheckBox*>(Exam->cellWidget(i,3));
        if(Box && Box->isChecked()){
            continue;
        }

        if (itemPointAwarded) {
            float itemValue = itemPointAwarded->text().toFloat();
            pointAwardedSum += itemValue;
        }
        if (itemPointMax) {
            float itemValue = itemPointMax->text().toFloat();
            pointMaxSum += itemValue;
        }
    }


    ui->totalExamPtsAwarded->setText(QString::number(pointAwardedSum));
    ui->totalExamPtsMax->setText(QString::number(pointMaxSum));

    if (pointMaxSum != 0) {
        percent = pointAwardedSum / pointMaxSum;
        ui->totalExamPercent->setText(QString::number(percent * 100).append("%"));
    }

    float Test_Hw = ui->Test_HW2->text().toFloat();
    float Test_Exam = ui->Test_Exam2->text().toFloat();

    float homeworkPoints = ui->totalHomeworkPtsAwarded->text().toFloat();
    float totalPointsAwarded = (pointAwardedSum*Test_Exam) + (homeworkPoints*Test_Hw); // grade calculation w weigth
    ui->totalPtsAwarded->setText(QString::number(totalPointsAwarded));

    float homeworkMaxPoints = ui->totalHomeworkPtsMax->text().toFloat();
    float totalPointsMax = (pointMaxSum*Test_Exam) + (homeworkMaxPoints*Test_Hw); // something here?
    ui->totalPtsMax->setText(QString::number(totalPointsMax));

    float totalPercent = totalPointsAwarded / totalPointsMax;
    ui->totalPercent->setText(QString::number(totalPercent * 100).append("%"));

    QString letterGrade = calcLetterGrade(totalPercent);
    ui->letterGrade->setText(letterGrade);
}


