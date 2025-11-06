#include "gradebook.h"
#include "exam.h"
#include "homework.h"
#include "ui_gradebook.h"

Gradebook::Gradebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gradebook)
{
    QVector<Homework> m_homeworks;
    QVector<Exam>     m_exams;
    ui->setupUi(this);
    ui->tableHomeworks->verticalHeader()->setVisible(false);
    ui->tableExams->verticalHeader()->setVisible(false);
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
    delete ui;
}

void Gradebook::on_btnAddNewHomework_clicked()
{
    ui->tableHomeworks->insertRow(ui->tableHomeworks->rowCount());
}


void Gradebook::on_btnAddNewExam_clicked()
{
    ui->tableExams->insertRow(ui->tableExams->rowCount());
}


void Gradebook::on_tableHomeworks_cellChanged(int row, int column)
{
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

    float examPoints = ui->totalExamPtsAwarded->text().toFloat();
    float totalPointsAwarded = pointAwardedSum + examPoints;
    ui->totalPtsAwarded->setText(QString::number(totalPointsAwarded));

    float examMaxPoints = ui->totalExamPtsMax->text().toFloat();
    float totalPointsMax = pointMaxSum + examMaxPoints;
    ui->totalPtsMax->setText(QString::number(totalPointsMax));

    float totalPercent = totalPointsAwarded / totalPointsMax;
    ui->totalPercent->setText(QString::number(totalPercent * 100).append("%"));

    QString letterGrade = calcLetterGrade(totalPercent);
    ui->letterGrade->setText(letterGrade);
}

void Gradebook::on_tableExams_cellChanged(int row, int column)
{
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

    float homeworkPoints = ui->totalHomeworkPtsAwarded->text().toFloat();
    float totalPointsAwarded = pointAwardedSum + homeworkPoints;
    ui->totalPtsAwarded->setText(QString::number(totalPointsAwarded));

    float homeworkMaxPoints = ui->totalHomeworkPtsMax->text().toFloat();
    float totalPointsMax = pointMaxSum + homeworkMaxPoints;
    ui->totalPtsMax->setText(QString::number(totalPointsMax));

    float totalPercent = totalPointsAwarded / totalPointsMax;
    ui->totalPercent->setText(QString::number(totalPercent * 100).append("%"));

    QString letterGrade = calcLetterGrade(totalPercent);
    ui->letterGrade->setText(letterGrade);
}

