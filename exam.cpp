#include "exam.h"

Exam::Exam(int id) : Assignment(id) {}

float Exam::curveOffset()
{
    return curveOffset_;
}

void Exam::setCurveOffset(float newCurveOffset)
{
    curveOffset_ = std::max(0.0f, newCurveOffset);
}

float Exam::effectivePointsAwarded()
{
    if (isIgnored_) return 0.f;
    return std::min(
        static_cast<float>(pointsMax_),
        pointsAwarded_ + (curveOffset_ * pointsMax_)
    );
}
