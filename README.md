# Simple Gradebook App

This is a group project for FGCU's Programming II course in Fall 2025. It is a simple
student gradebook app where the instructor enters grades in a list of homework assignments
and exams, and the computer calculates the final grade.

## Project Planning Notes

### Features
- There is only one user role for this app: the Instructor (maybe do a Student too if we can add a login page
    and figure out how to set the correct view for the role the user is logged in as)
- There is only one student to enter grades for.
- Time permitting, implement the ability to manage grades for multiple students
- The user (an Instructor) creates assignments, names them, enters in value of assignment in points, and enters in the number of points the student actually earned based on performance
- The user can read, create, edit, and delete assignments
- The user can create categories of assignments (e.g. Homework, Attendance, Exams) with customizable weightings (just do pre-defined categories instead?)
- The computer calculates a grade for the student. Displays the number of points earned out of the total number of points possible along with a letter grade.
- Time permitting: "What-if" grades like in Canvas. The user can enter in a "What-if" score for an assignment in another input box to do a separate calculation of a "What-if" grade. For example, this feature can answer questions such as "What score does the student need to get on the next exam to get an "A" in the course?"

### "Assignment" Class Design
- One superclass "Assignment" with 2 subclasses: Homework, Exams

```cpp
class Assignment {
protected:
    int m_id;               // ID number of the assignment
    std::string m_type;
    std::string m_name;     // Name of assignment
    float m_pointAwarded;     // Points awarded to student
    float m_pointMax;         // Maximum points possible
public:
    // can be instantiated without needing to initialize name, pointAwarded, pointMax, and gradeWeight
    // because the user clicks a button to create a new Assignment but the fields will begin blank
    Assignment(int id, int studentID) : m_id{id}, m_studentID{studentID} {}
    ... // virtual getters, setters, and destructor
    virtual float getFinalPointAwarded()
};
```

```cpp
class Homework : public Assignment { // same scheme for Attendance and Exams
    bool isLate = false;
public:
    Homework(int id) : Assignment(id), m_type{"HOMEWORK"} {}
    void setPointAwarded() override // pointAwarded is allowed to exceed pointMax
    float getFinalPointAwarded() override // if isLate, 0.5x score penalty
};
```

<!-- ```cpp
class Attendance : public Assignment {
    bool isExcused = false;
public:
    Attendance(int id) : Assignment(id), m_pointAwarded{0.0f}, m_pointMax{1.0f} {}
    void setPointAwarded() override // switches between 0 or 1
    void setPointMax() override // does nothing (set to 1 on instantiation)
    void setIsExcused() // switches the state of isExcused; if true, this Attendance does not count against grade
};
``` -->

```cpp
class Exam : public Assignment {
    float m_curveOffset = 0.0f; 
    // because there's only one student to manage (for now), grading on
    // a curve wouldn't really make sense, but the user can enter in a
    // number to add a specified percentage of pointMax to pointAwarded
    // to emulate a curve
public:
    Exam(int id) : Assignment(id), m_type{"EXAM"} {}
    float curveOffset()
    void setCurveOffset(float curveOffset)
    void setPointAwarded() override // pointAwarded is allowed to exceed pointMax
    float getFinalPointAwarded() override // add curveOffset to pointAwarded
}
```

### A class to contain the manage the collection of Assignments the user creates
- A "Gradebook" class to contain a collection of Assignments.
- The Gradebook class handles creating, updating, editing, and deleting Assignments
- The Gradebook class does operations like calculate total number of points, get letter grade.
- The Gradebook class can set, from user input, weightings for the three categories of Assignments

```cpp
class Gradebook {
    // std::vector<Assignment*> m_assignments;
    std::vector<Homework> m_homeworks;
    std::vector<Exam> m_exams;
    float m_weightHomework;
    float m_weightExam;
public:
    float weightHomework()
    float weightExam()
    void setWeightHomework(float weight)
    void setWeightExam(float weight)
    void getAssignments() // Reads out each element in m_assignments
    void createAssignment(std::string& type) // Make a new element in m_assignments
    void deleteAssignment(Assignment* assignment) // how do you tell which element in m_assignments to remove? and don't forget to deallocate
    void updateAssignment(Assignment* assignment) // add arguments to pass in data
    float calcCategoryPointTotal(std::string& type)
    float calcWeightedCoursePercent()
    float calcFinalLetterGrade()
    ~Gradebook() = default;
}
```

<!-- ## "User" Class Design (time permitting)
- One superclass "User" with two derived classes "Student" and "Instructor"
- "Student" and "Instructor" differ by user role. They will see different pages when logged in.
- Instructors can add Assignments, enter in Assignment scores, edit Assignment scores, set Assignment weightings and delete Assignments
- Students can only read assignments, not update, create, or delete them

```cpp
enum UserPermissions {
    CREATE_ASSIGNMENT,
    READ_ASSIGNMENT,
    UPDATE_ASSIGNMENT,
    DELETE_ASSIGNMENT
}

class BaseUser {
protected:
    int m_id;
    std::string m_name;
    std::string m_username;
    std::string m_password;
    std::vector<UserPermissions> m_permissions;
public:
    BaseUser(int id, std::string name, std::string username, std::string password) : 
        m_id{id}, 
        m_name{name},
        m_username{username},
        m_password{password} 
    {}
};
```

```cpp
class GradebookUser : public BaseUser {
public:
    GradebookUser(int id, std::string name, std::string username, std::string password) : 
        User(id, name, username, password)
    {}
    void getAssignments()
    void editAssignment(int assignmentID, int pointAwarded, int pointMax, float gradeWeight)
    void createAssignment()
    void deleteAssignment()
}
```

```cpp
class Student : public GradebookUser {
protected:
    std::vector<UserPermissions> = { READ_ASSIGNMENT };
public:
    Student(int id, std::string name, std::string username, std::string password) : User(id, name, username, password) {}
    void getAssignments()
    void editAssignment(int assignmentID, int pointAwarded, int pointMax, float gradeWeight)
    void createAssignment()
    void deleteAssignment()
}
``` -->

### UI Design

Questions to answer:
- What is the relationship between the UI and data?
- Where in the code is your data?
- How do you make interaction with UI elements, such as clicking or entering text, change the data?
- And in the reverse direction: If data changes, how do you update the UI?
- How do you create or delete UI elements during runtime? (e.g. add a new row to a table upon pressing a button)
- If you decide to implement user roles, how do you tell who is logged in? Show the correct page depending on who is logged in.