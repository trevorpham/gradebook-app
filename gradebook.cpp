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
}

Gradebook::~Gradebook()
{
    delete ui;
}

void Gradebook::on_btnAddNewHomework_clicked()
{

}


void Gradebook::on_btnAddNewExam_clicked()
{

}

