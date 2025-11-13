#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <assignment.h>

class Homework : public Assignment
{
    AssignmentType const type_ = HOMEWORK;
    bool isLate_;
    bool isIgnored_;
public:
    Homework(int id);
    void setPointsAwarded(float newPointsAwarded) override;
    float effectivePointsAwarded(float latePenaltyFactor) override;
    bool isLate();
    void setIsLate();
    bool isIgnored();
    void setIsIgnored();
};

#endif // HOMEWORK_H
