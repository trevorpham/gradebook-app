#include "gradebook.h"
#include "ui_gradebook.h"

Gradebook::Gradebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gradebook)
{
    ui->setupUi(this);
}

Gradebook::~Gradebook()
{
    delete ui;
}
