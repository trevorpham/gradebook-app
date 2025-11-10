#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <assignment.h>

class Homework : public Assignment
{
    bool m_isLate;
    bool m_isIgnored;
public:
    Homework(int id);
    // std::string virtual name();
    // void virtual setName(std::string &newName);
    // float virtual pointsAwarded();
    // void virtual setPointsAwarded(float newPointsAwarded);
    // float virtual pointsMax();
    // void virtual setPointsMax(float newPointsMax);
    bool isLate();
    void setIsLate();
    bool isIgnored();
    void setIsIgnored();
};

#endif // HOMEWORK_H
