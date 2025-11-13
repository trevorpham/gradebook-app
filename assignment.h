#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "assignmentType.h"
#include <string>
class Assignment
{
protected:
    int id_;
    AssignmentType const type_ = ASSIGNMENT;
    std::string name_ = "";
    bool isIgnored_ = false;
    float pointsAwarded_ = 0;
    float pointsMax_ = 1.f;
public:
    Assignment(int id);
    virtual ~Assignment();
    int id();
    AssignmentType type();
    std::string virtual name();
    void virtual setName(std::string &newName);
    float virtual pointsAwarded();
    void virtual setPointsAwarded(float newPointsAwarded);
    float virtual pointsMax();
    void virtual setPointsMax(int newPointsMax);
    bool isIgnored();
    void setIsIgnored();
    float virtual effectivePointsAwarded();
    float virtual effectivePointsAwarded(float modifier);
};

#endif // ASSIGNMENT_H
