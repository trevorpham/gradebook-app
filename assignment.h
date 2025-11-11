#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
class Assignment
{
protected:
    int id_;
    std::string type_ = "ASSIGNMENT";
    std::string name_ = "";
    float pointsAwarded_ = 0;
    int pointsMax_ = 1;
public:
    Assignment(int id);
    virtual ~Assignment();
    int id();
    std::string type();
    std::string virtual name();
    void virtual setName(std::string &newName);
    float virtual pointsAwarded();
    void virtual setPointsAwarded(float newPointsAwarded);
    float virtual pointsMax();
    void virtual setPointsMax(int newPointsMax);
    float virtual effectivePointsAwarded() = 0;
    float virtual effectivePointsAwarded(float modifier) = 0;
};

#endif // ASSIGNMENT_H
