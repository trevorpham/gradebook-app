#include "assignment.h"

Assignment::Assignment(int id) : id_{id} {}
Assignment::~Assignment() = default;

int Assignment::id()
{
    return id_;
}

AssignmentType Assignment::type()
{
    return AssignmentType::ASSIGNMENT;
}

std::string Assignment::name()
{
    return name_;
}

void Assignment::setName(const std::string& newName)
{
    name_ = newName;
}

float Assignment::pointsAwarded()
{
    if (isDropped_) return 0.f;
    return pointsAwarded_;
}

void Assignment::setPointsAwarded(float newPointsAwarded)
{
    pointsAwarded_ = std::min(
        static_cast<float>(pointsMax_),
        std::max(0.0f, newPointsAwarded)
    );
}

float Assignment::pointsMax()
{
    if (isDropped_) return 0.f;
    return pointsMax_;
}

void Assignment::setPointsMax(int newPointsMax)
{
    pointsMax_ = std::max(1, newPointsMax);
}

bool Assignment::isDropped()
{
    return isDropped_;
}

void Assignment::setIsDropped()
{
    isDropped_ = !isDropped_;
}
