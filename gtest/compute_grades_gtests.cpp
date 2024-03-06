#include <gtest/gtest.h>

#include "compute_grades.hpp"

/*TEST(ComputeGradeTests, to_lowercase) {
    EXPECT_EQ(to_lowercase("hello WORLD"), "hello world");
    EXPECT_EQ(to_lowercase("T"), "t");
    EXPECT_EQ(to_lowercase(""), "");
}

TEST(ComputeGradeTests, load_stopwords) {
    stringstream words1{"hello WORLD test TEST bar FOO bar"};
    std::set<std::string> set1{"bar", "foo", "hello", "test", "world"};
    EXPECT_EQ(load_stopwords(words1), set1);

    stringstream words2{};
    std::set<std::string> set2;
    EXPECT_EQ(load_stopwords(words2), set2);

    stringstream words3{"A a"};
    std::set<std::string> set3{"a"};
    EXPECT_EQ(load_stopwords(words3), set3);
}

TEST(ComputeGradeTests, count_words) {
    stringstream test("aa aa Aa aA AA bC bc bc BC XY XY foo FOO foO Foo BAR bar");
    std::map<std::string, int> expected{{"aa", 5}, {"bc", 4}, {"xy", 2}, {"bar", 2}};
    EXPECT_EQ(count_words(test, {"foo"}), expected);
}

TEST(ComputeGradeTests, output_word_counts) {
    map<string, int> word_counts{{"foo", 1}, {"bar", 5}, {"xy", 3}};
    stringstream output;
    output_word_counts(word_counts, output);
    EXPECT_STREQ(output.str().c_str(), "bar 5\nfoo 1\nxy 3\n");
}

TEST(ComputeGradeTests, ValidationThrowsForInvalidScore) {
    Student student("John Doe", 101); // Assuming this score is out of valid range
    EXPECT_THROW(student.validate(), std::domain_error);
}
TEST(ComputeGradeTests, CorrectlyComparesStudents) {
    Student student1("Alice", 90);
    Student student2("Bob", 95); // Bob has a higher score than Alice

    EXPECT_TRUE(student1 < student2); // Expect that student1 compares less than student2
}*/



/*TEST(ComputeGradeTests, ValidateThrowsExceptionOnInvalidScores) {
    Student s;
    s.hw = {95, 85, -5};
    EXPECT_THROW(s.validate(), std::domain_error);
}*/
TEST(ComputeGradeTests, ValidateStudentScoresErrorMessage) {
    std::stringstream ss;
    ss << "Name John Doe\nQuiz 90 85 92\nHW 88 105 100\nFinal 93\n\n";

    Gradebook gb;

    try {
        // Assuming operator>> for Gradebook is overloaded to read and validate scores
        ss >> gb;
        FAIL() << "Expected std::domain_error due to invalid HW score";
    } catch (std::domain_error const& err) {
        EXPECT_EQ(std::string(err.what()), "Error: invalid percentage 105");
    } catch (...) {
        FAIL() << "Caught an unexpected exception type";
    }
}


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

/*TEST(ComputeGradesTests, ValidationWithInvalidData) {
    std::stringstream ss("John Doe\n-5\n"); // Simulating invalid final score input
    Student student;

    EXPECT_THROW({
        ss >> student; // Assuming operator>> is implemented to read data and call validate() internally
    }, std::domain_error);
}*/

TEST(GradebookTest, InvalidStudentScores) {
    std::stringstream ss;
    ss << "Name John Doe\nQuiz 101\nHW 90 -5\nFinal 85\n\n"; // Invalid Quiz score
    Gradebook gb;

    EXPECT_THROW(ss >> gb, std::domain_error);
}

// Test validation logic with valid data
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
