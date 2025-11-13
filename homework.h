#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <assignment.h>

class Homework : public Assignment
{
    AssignmentType type() override;
    bool isLate_;
    bool isIgnored_;
public:
    Homework(int id);
    void setPointsAwarded(float newPointsAwarded) override;
    float effectivePointsAwarded() override;
    bool isLate();
    void setIsLate();
};

#endif // HOMEWORK_H
