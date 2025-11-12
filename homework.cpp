#include "homework.h"
#include <QDebug>

Homework::Homework(int id) : Assignment(id) {
        qDebug() << "Homework object created with ID:" << id;
}

// void Homework::setPointsAwarded(float newPointsAwarded)
// {
//     pointsAwarded_ = std::max(0.0f, newPointsAwarded);
// }

// float Homework::effectivePointsAwarded(float latePenaltyFactor = 1.f)
// {
//     float effPts = pointsAwarded_ * (isLate_ ? latePenaltyFactor * pointsAwarded_ : 1.f);
//     return effPts;
// }

bool Homework::isLate()
{
    return isLate_;
}

void Homework::setIsLate()
{
    isLate_ = !isLate_;
}

bool Homework::isIgnored()
{
    return isIgnored_;
}

void Homework::setIsIgnored()
{
    isIgnored_ = !isIgnored_;
}
