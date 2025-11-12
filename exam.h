#ifndef EXAM_H
#define EXAM_H

#include "assignment.h"

class Exam : public Assignment
{
    std::string type_ = "EXAM";
    float curveOffset_ = 0.0f;
    float weight_;
public:
    Exam(int id);
    float curveOffset();
    void setCurveOffset(float newCurveOffset);
    //float effectivePointsAwarded() override;

    //setter/getter
    void setExamWeight(float W){
        weight_ = W;
    }
    float getExamWeight(){
        return weight_;
    }

    //Getter
    // Get type
    std::string get_type(){
        return type_;
    }
};

#endif // EXAM_H
