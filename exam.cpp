#include "exam.h"
#include "idcounter.h"

Exam::Exam() : Assignment(IDCounter<Exam>::getNextID()) {}

float Exam::curveOffset()
{
    return m_curveOffset;
}

void Exam::setCurveOffset(float newCurveOffset)
{
    m_curveOffset = newCurveOffset;
}

float Exam::effectivePointsAwarded()
{
    float effPts = std::min(m_pointsMax, m_pointsAwarded + (m_curveOffset * m_pointsMax));
    return effPts;
}
