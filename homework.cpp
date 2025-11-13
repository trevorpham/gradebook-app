#include "homework.h"

Homework::Homework(int id) : Assignment(id) {}

AssignmentType Homework::type()
{
    return AssignmentType::HOMEWORK;
}

void Homework::setPointsAwarded(float newPointsAwarded)
{
    pointsAwarded_ = std::max(0.0f, newPointsAwarded);
}

float Homework::effectivePointsAwarded()
{
    // if (isIgnored_) return 0;
    float effPts = pointsAwarded_ * (isLate_ ? 0.5f * pointsAwarded_ : 1.f);
    return effPts;
}

bool Homework::isLate()
{
    return isLate_;
}

void Homework::setIsLate()
{
    isLate_ = !isLate_;
}
