#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <assignment.h>

class Homework : public Assignment
{
    bool isLate_;
public:
    Homework(int id);
    AssignmentType type() override;
    void setPointsAwarded(float newPointsAwarded) override;
    float effectivePointsAwarded() override;
    bool isLate();
    void setIsLate();
};

#endif // HOMEWORK_H
