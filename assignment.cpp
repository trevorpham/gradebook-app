#include "assignment.h"

Assignment::Assignment(int id) : m_id{id} {}
Assignment::~Assignment() = default;

int Assignment::id()
{
    return m_id;
}

std::string Assignment::name()
{
    return m_name;
}

void Assignment::setName(std::string &newName)
{
    m_name = newName;
}

float Assignment::pointsAwarded()
{
    return m_pointsAwarded;
}

void Assignment::setPointsAwarded(float newPointsAwarded)
{
    m_pointsAwarded = newPointsAwarded;
}

float Assignment::pointsMax()
{
    return m_pointsMax;
}

void Assignment::setPointsMax(float newPointsMax)
{
    m_pointsMax = newPointsMax;
}

