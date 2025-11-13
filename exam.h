#ifndef EXAM_H
#define EXAM_H

#include <assignment.h>

class Exam : public Assignment
{
    AssignmentType const type_ = EXAM;
    float curveOffset_ = 0.0f;
public:
    Exam(int id);
    float curveOffset();
    void setCurveOffset(float newCurveOffset);
    float effectivePointsAwarded() override;
};

#endif // EXAM_H
