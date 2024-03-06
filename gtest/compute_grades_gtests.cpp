#include <gtest/gtest.h>

#include "compute_grades.hpp"




TEST(ComputeGradeTests,ErrorMessageThrown) {
    std::stringstream ss;
    ss << "Name John Doe\nQuiz 90 85 92\nHW 88 105 100\nFinal 93\n\n";

    Gradebook gb;
    EXPECT_ANY_THROW({
        try {
            ss >> gb;
            gb.validate(); // Ensure to call validate if it's not automatically dg >> operation
        } catch (const std::domain_error& err) {
            // Check the specific error message
            EXPECT_EQ(std::string(err.what()), "Error: invalid percentage 105");
            throw; // Rethrow the exception to satisfy EXPECT_ANY_THROW
        }
    });
}

TEST(ComputeGradesTests, ValidationWithValidData) {
    std::stringstream ss("Jane Doe\n95\n"); // Simulating valid final score input
    Student student;

    EXPECT_NO_THROW({
        ss >> student;
    });
}


TEST(ComputeGradesTests, Comparison) {
    std::stringstream ssStudent1, ssStudent2;
    ssStudent1 << "Name: Alice Smith\nQuiz: 90 85\nHW: 88 92\nFinal: 93\n";
    ssStudent2 << "Name: Bob Johnson\nQuiz: 78 82\nHW: 85 87\nFinal: 88\n";
    Student student1, student2;
    ssStudent1 >> student1;
    ssStudent2 >> student2;
    EXPECT_FALSE(student1 < student2);
    std::stringstream ssStudent3;
    ssStudent3 << "Name: Charlie Smith\nQuiz: 95 90\nHW: 93 88\nFinal: 94\n";
    Student student3;
    ssStudent3 >> student3;
    EXPECT_FALSE(student1 < student3);
    EXPECT_FALSE(student3 < student2);
}

TEST(ComputeGradesTest, ValidationWithInvalidData) {
    std::stringstream ss;
    ss << "Name: John Doe\n"
       << "HW: 90 95\n"
       << "Quiz: 85 80\n"
       << "Final: -5\n";

    Student student;
	ss >> student;
    EXPECT_THROW({
       student.validate() ;
    }, std::domain_error);
}

