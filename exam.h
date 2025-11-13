#ifndef EXAM_H
#define EXAM_H

#include <assignment.h>

class Exam : public Assignment
{
    AssignmentType const type_ = AssignmentType::EXAM;
    float curveOffset_ = 0.0f;
public:
    Exam(int id);
    AssignmentType type() override;
    float curveOffset();
    void setCurveOffset(float newCurveOffset);
    float effectivePointsAwarded() override;
};

#endif // EXAM_H
