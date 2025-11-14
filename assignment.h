#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "assignmentType.h"
#include <string>
class Assignment
{
protected:
    int id_;
    AssignmentType const type_ = AssignmentType::ASSIGNMENT;
    std::string name_ = "";
    bool isDropped_ = false;
    float pointsAwarded_ = 0.f;
    float pointsMax_ = 0.f;
public:
    Assignment(int id);
    virtual ~Assignment();
    int id();
    AssignmentType virtual type();
    std::string virtual name();
    void virtual setName(const std::string& newName);
    float virtual pointsAwarded();
    void virtual setPointsAwarded(float newPointsAwarded);
    float virtual pointsMax();
    void virtual setPointsMax(int newPointsMax);
    bool isDropped();
    void setIsDropped();
    float virtual effectivePointsAwarded() = 0;
};

#endif // ASSIGNMENT_H
