#ifndef EXAM_H
#define EXAM_H

#include <assignment.h>

class Exam : public Assignment
{
    float m_curveOffset = 0.0f;
public:
    Exam();
    float curveOffset();
    void setCurveOffset(float newCurveOffset);
    float effectivePointsAwarded();
};

#endif // EXAM_H
