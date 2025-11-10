#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
class Assignment
{
protected:
    int m_id;
    std::string m_name;
    float m_pointsAwarded;
    float m_pointsMax;
public:
    Assignment(int id);
    virtual ~Assignment();
    int id();
    int static getNextID();
    std::string virtual name();
    void virtual setName(std::string &newName);
    float virtual pointsAwarded();
    void virtual setPointsAwarded(float newPointsAwarded);
    float virtual pointsMax();
    void virtual setPointsMax(float newPointsMax);
};

#endif // ASSIGNMENT_H
