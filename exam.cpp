#include "exam.h"
#include <QDebug>

Exam::Exam(int id) : Assignment(id) {
     qDebug() << "Exam object created with ID:" << id;
}

float Exam::curveOffset()
{
    return curveOffset_;
}

void Exam::setCurveOffset(float newCurveOffset)
{
    curveOffset_ = std::max(0.0f, newCurveOffset);
}

// float Exam::effectivePointsAwarded()
// {
//     return std::min(
//         static_cast<float>(pointsMax_),
//         pointsAwarded_ + (curveOffset_ * pointsMax_)
//     );
// }
