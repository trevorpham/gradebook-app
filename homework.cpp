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
    if (isDropped_) return 0.f;
    float effPts = pointsAwarded_ * (isLate_ ? 0.5f : 1.f);
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
