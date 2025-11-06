#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gradebook;
}
QT_END_NAMESPACE

class Gradebook : public QMainWindow
{
    Q_OBJECT

public:
    Gradebook(QWidget *parent = nullptr);
    ~Gradebook();

private:
    Ui::Gradebook *ui;
};
#endif // GRADEBOOK_H
