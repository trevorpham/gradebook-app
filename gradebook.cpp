#include "gradebook.h"
#include "exam.h"
#include "homework.h"
#include "ui_gradebook.h"
#include <QLineEdit>
#include<QTextEdit>
#include <QCheckBox>
#include <QDebug>

Gradebook::Gradebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gradebook)
{
    ui->setupUi(this);
    ui->tableHomeworks->hideColumn(0); // hide ID column
    ui->tableHomeworks->verticalHeader()->setVisible(false); // hide row index
    ui->tableExams->hideColumn(0); // hide ID column
    ui->tableExams->verticalHeader()->setVisible(false); // hide row index
}

int Gradebook::nextAssignmentID()
{
    static int s_nextID = 1;
    return s_nextID++;
}

Assignment* Gradebook::createAssignment(AssignmentType type, int id)
{
    switch(type) {
    case AssignmentType::HOMEWORK:
        return new Homework(id);
    case AssignmentType::EXAM:
        return new Exam(id);
    default:
        return nullptr;
    }
}

Assignment* Gradebook::getAssignmentByID(int id)
{
    for (int i = 0; i < assignments_.size(); i++) {
        if (assignments_.at(i)->id() == id) {
            return assignments_.at(i);
        }
    }

    return nullptr;
}

bool Gradebook::deleteAssignment(int id)
// Deletes an assignment with specified id. Returns true if successful.
{
    for (int i = 0; i < assignments_.size(); i++)
    {
        if (assignments_.at(i) == nullptr) continue;
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
        if (assignments_.at(i) == nullptr) continue;
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
        if (assignments_.at(i) == nullptr) continue;
        if (assignments_.at(i)->type() == type) {
            sum += assignments_.at(i)->pointsMax();
        }
    }
    return sum;
}

void Gradebook::updateDisplayedCalcs()
// overloaded method, updates all displayed calculated values if no AssignmentType given
{
    float effHWPointsAwarded = categoryEffPointsAwarded(AssignmentType::HOMEWORK);
    float maxHWPoints = categoryMaxPoints(AssignmentType::HOMEWORK);
    float HWPercent = (effHWPointsAwarded / maxHWPoints) * 100;

    float effExamPointsAwarded = categoryEffPointsAwarded(AssignmentType::EXAM);
    float maxExamPoints = categoryMaxPoints(AssignmentType::EXAM);
    float examPercent = (effExamPointsAwarded / maxExamPoints) * 100;


    ui->totalHomeworkPts->setText(
        QString::number(effHWPointsAwarded)
        .append(QString("/"))
        .append(QString::number(maxHWPoints))
    );
    ui->totalHomeworkPercent->setText(QString::number(HWPercent).append("%"));

    ui->totalExamPts->setText(
        QString::number(effExamPointsAwarded)
        .append(QString("/"))
        .append(QString::number(maxExamPoints))
    );
    ui->totalExamPercent->setText(QString::number(examPercent).append("%"));
}

void Gradebook::updateDisplayedCalcs(AssignmentType type)
// overloaded method, updates displayed calculations only for specified AssignmentType
{
    float effPointsAwarded = categoryEffPointsAwarded(type);
    float maxPoints = categoryMaxPoints(type);
    float categoryPercent = (effPointsAwarded / maxPoints) * 100;

    switch(type) {
    case AssignmentType::HOMEWORK:
        ui->totalHomeworkPts->setText(
            QString::number(effPointsAwarded)
            .append(QString("/"))
            .append(QString::number(maxPoints))
        );
        ui->totalHomeworkPercent->setText(QString::number(categoryPercent).append("%"));
        break;
    case AssignmentType::EXAM:
        ui->totalExamPts->setText(
            QString::number(effPointsAwarded)
            .append(QString("/"))
            .append(QString::number(maxPoints))
        );
        ui->totalExamPercent->setText(QString::number(categoryPercent).append("%"));
        break;
    default:
        break;
    }
}

void Gradebook::on_btnAddNewExam_clicked()
{
    // creates new Exam and adds it to assignments_
    Assignment* a = createAssignment(AssignmentType::EXAM, nextAssignmentID());
    assignments_.push_back(a);

    // prevent events from the initialization of the new row from triggering an infinite loop
    ui->tableExams->blockSignals(true);

    // insert a new row at the bottom of the table
    int row = ui->tableExams->rowCount();
    ui->tableExams->insertRow(row);

    // initialize id cell (hidden)
    ui->tableExams->setItem( row, 0, new QTableWidgetItem(QString::number(a->id())) );

    // initialize points awarded cell
    QTableWidgetItem* itemPtsAward = new QTableWidgetItem(QString::number(a->pointsAwarded()));
    ui->tableExams->setItem( row, 2, itemPtsAward );

    // initialize points max cell
    QTableWidgetItem* itemPtsMax = new QTableWidgetItem(QString::number(a->pointsMax()));
    ui->tableExams->setItem( row, 3, itemPtsMax );

    // initialize curve offset cell
    QTableWidgetItem* itemCurve = new QTableWidgetItem(QString::number(static_cast<Exam*>(a)->curveOffset()));
    ui->tableExams->setItem( row, 4, itemCurve );

    // initialize checkbox isDropped cell
    QCheckBox* checkBoxDropped = new QCheckBox(ui->tableExams);
    ui->tableExams->setCellWidget(row, 5, checkBoxDropped);

    // add event listeners & handlers to checkboxes (cellChanged functions do not trigger when these are toggled)
    connect(checkBoxDropped, &QCheckBox::toggled, this, [this, a]{
        a->setIsDropped();
        this->updateDisplayedCalcs(AssignmentType::EXAM);
    });

    // reactivate events
    ui->tableExams->blockSignals(false);
}

void Gradebook::on_tableExams_cellChanged(int row, int column) {
    // identify the Assignment the cell belongs to then call the appropriate setter
    int id = ui->tableExams->item(row, 0)->text().toInt();

    Exam* exam = static_cast<Exam*>(getAssignmentByID(id));
    QTableWidgetItem* value = ui->tableExams->item(row, column);

    ui->tableExams->blockSignals(true);
    switch(column) {
    case 1: // set name
        exam->setName(value->text().toStdString());
        ui->tableExams->setItem( row, column, new QTableWidgetItem(QString::fromStdString(exam->name())) );
        break;
    case 2: // set points awarded
        exam->setPointsAwarded(value->text().toFloat());
        ui->tableExams->setItem( row, column, new QTableWidgetItem(QString::number(exam->pointsAwarded())) );
        break;
    case 3: // set max points
        exam->setPointsMax(value->text().toFloat());
        ui->tableExams->setItem( row, column, new QTableWidgetItem(QString::number(exam->pointsMax())) );
        break;
    case 4: // set exam curve
        exam->setCurveOffset(value->text().toFloat());
        ui->tableExams->setItem( row, column, new QTableWidgetItem(QString::number(exam->curveOffset())) );
        break;
    }
    ui->tableExams->blockSignals(false);

    updateDisplayedCalcs(AssignmentType::EXAM);
}

void Gradebook::on_btnAddNewHomework_clicked()
{
    // creates new Homework and adds it to assignments_
    Assignment* a = createAssignment(AssignmentType::HOMEWORK, nextAssignmentID());
    assignments_.push_back(a);

    // prevent events from the initialization of the new row from triggering an infinite loop
    ui->tableHomeworks->blockSignals(true);

    // insert a new row at the bottom of the table
    int row = ui->tableHomeworks->rowCount();
    ui->tableHomeworks->insertRow(row);

    // initialize id cell (hidden)
    ui->tableHomeworks->setItem( row, 0, new QTableWidgetItem(QString::number(a->id())) );

    // initialize points awarded cell
    ui->tableHomeworks->setItem( row, 2, new QTableWidgetItem(QString::number(a->pointsAwarded())) );

    // initialize points max cell
    ui->tableHomeworks->setItem( row, 3, new QTableWidgetItem(QString::number(a->pointsMax())) );

    // initialize checkbox isLate cell
    QCheckBox* checkBoxLate = new QCheckBox(ui->tableHomeworks);
    ui->tableHomeworks->setCellWidget(row, 4, checkBoxLate);

    // initialize checkbox isDropped cell
    QCheckBox* checkBoxDropped = new QCheckBox(ui->tableHomeworks);
    ui->tableHomeworks->setCellWidget(row, 5, checkBoxDropped);

    // add event listeners & handlers to checkboxes (cellChanged functions do not trigger when these are toggled)
    connect(checkBoxLate, &QCheckBox::toggled, this, [this, a]{
        static_cast<Homework*>(a)->setIsLate();
        this->updateDisplayedCalcs(AssignmentType::HOMEWORK);
    });
    connect(checkBoxDropped, &QCheckBox::toggled, this, [this, a]{
        a->setIsDropped();
        this->updateDisplayedCalcs(AssignmentType::HOMEWORK);
    });

    // reactivate events
    ui->tableHomeworks->blockSignals(false);
}

void Gradebook::on_tableHomeworks_cellChanged(int row, int column) {
    // identify the Assignment the cell belongs to then call the appropriate setter
    int id = ui->tableHomeworks->item(row, 0)->text().toInt();
    Homework* hw = static_cast<Homework*>(getAssignmentByID(id));
    QTableWidgetItem* value = ui->tableHomeworks->item(row, column);

    ui->tableHomeworks->blockSignals(true);
    switch(column) {
    case 1: // set name
        hw->setName(value->text().toStdString()); // call setter. then call getter and pass result to UI
        ui->tableHomeworks->setItem( row, column, new QTableWidgetItem(QString::fromStdString(hw->name())) );
        break;
    case 2: // set points awarded
        hw->setPointsAwarded(value->text().toFloat());
        ui->tableHomeworks->setItem( row, column, new QTableWidgetItem(QString::number(hw->pointsAwarded())) );
        break;
    case 3: // set max points
        hw->setPointsMax(value->text().toFloat());
        ui->tableHomeworks->setItem( row, column, new QTableWidgetItem(QString::number(hw->pointsMax())) );
        break;
    }
    ui->tableHomeworks->blockSignals(false);

    updateDisplayedCalcs(AssignmentType::HOMEWORK);
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


