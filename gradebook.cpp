#include "gradebook.h"
#include "homework.h"
#include "Exam.h"
#include "ui_gradebook.h"
#include <QLineEdit>
#include<QTextEdit>
#include <QCheckBox>
#include <QString>
// #include <QTableWidgetItem>
// #include <QSignalBlocker>

Gradebook::Gradebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gradebook)
{
    ui->setupUi(this);
    addMenu = new QMenu(this);
    addHW = addMenu->addAction("Add Homework");
    addEXAM = addMenu->addAction("Add Exam");
    ui->btnAddNewHomework->setMenu(addMenu);
    //should create an object of each class ?
    connect(addHW, &QAction::triggered, this, &Gradebook::on_btnAddNewHomework_clicked);
    connect(addEXAM, &QAction::triggered, this, &Gradebook::on_btnAddNewExam_clicked);

    connect(ui->tableHomeworks,&QTableWidget::cellChanged,this,&Gradebook::on_tableHomeworks_cellChanged);



    ui->tableHomeworks->verticalHeader()->setVisible(false);
    //ui->tableExams->verticalHeader()->setVisible(false);


    connect(ui->Test_HW2, &QLineEdit::textChanged, this, [this]{GradeCalculation();});
    connect(ui->Test_Exam2, &QLineEdit::textChanged, this, [this]{GradeCalculation();});
}

int Gradebook::nextAssignmentID()
{
    static int s_nextID = 1;
    return s_nextID++;
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

//=========== HW CODE ==============

void Gradebook::on_btnAddNewHomework_clicked()
{
    int row = ui->tableHomeworks->rowCount();
    ui->tableHomeworks->insertRow(row);

    Homework* hw = new Homework(nextAssignmentID());
    hw->get_type();
    assignments_.push_back(hw);

    ui->tableHomeworks->setItem(row, 0,
    new QTableWidgetItem(QString::fromStdString(hw->get_type())));

    QCheckBox* checkBox = new QCheckBox(ui ->tableHomeworks);
    ui->tableHomeworks->setCellWidget(row, 3, checkBox);
    connect(checkBox, &QCheckBox::toggled, this, [this]{ GradeCalculation(); });

    // connect(ui->Test_HW2, &QLineEdit::textChanged, this, [this]{GradeCalculation();});

}

// ============ CODE FOR EXAM ========================
void Gradebook::on_btnAddNewExam_clicked()
{
    //ui->tableExams->insertRow(ui->tableExams->rowCount());

    int row = ui->tableHomeworks->rowCount();
    ui->tableHomeworks->insertRow(row);

    Exam* ex = new Exam(nextAssignmentID());
    ex->get_type();
    assignments_.push_back(ex);

    ui->tableHomeworks->setItem(row, 0,
    new QTableWidgetItem(QString::fromStdString(ex->get_type())));

    QCheckBox* checkBox = new QCheckBox(ui ->tableHomeworks); // (ui -> tableExams ) change to (ui ->tableHomeworks) we're creating everything in tableHomeworks for now
    ui->tableHomeworks->setCellWidget(row, 3, checkBox);
    connect(checkBox, &QCheckBox::toggled, this, [this]{ GradeCalculation(); });

    //connect(ui->Test_Exam2, &QLineEdit::textChanged, this, [this]{GradeCalculation();});
}

void Gradebook::on_tableHomeworks_cellChanged(int row, int column){
    GradeCalculation();
}

// In your class definition or setup function:
// In your class definition or setup function:




void Gradebook::GradeCalculation()
{
    #define DUMP(name, val) qDebug() << #name ":" << (val)

    qDebug().noquote() << "\n===== GradeCalculation() =====";
    weightExam_ = ui->Test_Exam2->text().toFloat();
    weightHomework_ = ui->Test_HW2->text().toFloat();


    // DUMP(weightHomework_, weightHomework_);
    // DUMP(weightExam_,     weightExam_);


    QTableWidget* HW = ui->tableHomeworks;

    int rowCount = ui->tableHomeworks->rowCount();
    int colCount = ui->tableHomeworks->columnCount();
    float HW_ptsAwarded = 0,HW_ptsMax = 0;
    float exam_ptsAwarded = 0,exam_ptsMax = 0;


    qDebug() << "Row count:" << rowCount << " Assignments size:" << assignments_.size();


    for (int i=0; i<rowCount; i++) {
        Assignment* T = assignments_[i];

        bool okay1 = false, okay2 = false;

        float Awarded_pts = 0;
        float Max_pts = 0;
        if (QTableWidgetItem* pts_awarded = ui->tableHomeworks->item(i,1)){
            Awarded_pts = pts_awarded->text().toFloat(&okay1);
        }
        if(QTableWidgetItem* pts_max = ui->tableHomeworks->item(i, 2)){
            Max_pts = pts_max->text().toFloat(&okay2);
        }


        QCheckBox* Box = qobject_cast<QCheckBox*>(HW->cellWidget(i,3));
        if(Box && Box->isChecked()){
            continue;
        }

        if (auto* Hw = dynamic_cast<Homework*>(T)) {
            //float Earned_HW_pts = pts_awarded->text().toFloat();
            std::string t = Hw->get_type();
            HW_ptsAwarded += Awarded_pts;
            HW_ptsMax += Max_pts;
        }
        if (auto* Ex =dynamic_cast<Exam*>(T)) {
            std::string t = Ex->get_type();
            exam_ptsAwarded += Awarded_pts;
            exam_ptsMax += Max_pts;
        }
        DUMP(HW_ptsAwarded, HW_ptsAwarded);
        DUMP(HW_ptsMax,     HW_ptsMax);
        DUMP(EX_ptsAwarded, exam_ptsAwarded);
        DUMP(EX_ptsMax,     exam_ptsMax);
    }






    float totalPointsAwarded = (HW_ptsAwarded*weightHomework_) + (exam_ptsAwarded*weightExam_);
    ui->totalPtsAwarded->setText(QString::number(totalPointsAwarded));

    float totalPointsMax = (HW_ptsMax*weightHomework_) + (exam_ptsMax*weightExam_); //calculation (examMaxPoints*weight) change to point MaxSum
    ui->totalPtsMax->setText(QString::number(totalPointsMax));

    float totalPercent = totalPointsAwarded / totalPointsMax;
    ui->totalPercent->setText(QString::number(totalPercent * 100).append("%"));

    QString letterGrade = calcLetterGrade(totalPercent);
    ui->letterGrade->setText(letterGrade);

    DUMP(totalPointsAwarded, totalPointsMax);
    DUMP(totalPercent,letterGrade);
}



