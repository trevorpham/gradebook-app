#ifndef HOMEWORK_H
#define HOMEWORK_H

#include "assignment.h"
#include <string>

class Homework : public Assignment
{
    std::string type_ = "HOMEWORK";
    bool isLate_;
    bool isIgnored_;
    bool isExtraCredit_;
    float weight_;
public:
    Homework(int id);
    //===========Comment out for now============//
    // void setPointsAwarded(float newPointsAwarded) override;
    // float effectivePointsAwarded(float latePenaltyFactor) override;
    bool isLate();
    void setIsLate();
    bool isIgnored();
    void setIsIgnored();
    //setter and getter
    void setHwWeight(float W){
        weight_ = W;
    }
    float getHwWeight(){
        return weight_;
    }

    // Get type
    std::string get_type(){
        return type_;
    }
};

#endif // HOMEWORK_H
