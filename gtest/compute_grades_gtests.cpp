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
*/

/*TEST(ComputeGradesTests, Validate) {
    Student valid_student;
    valid_student.hw = {100, 90, 80};
    valid_student.quiz = {90, 80, 70};
    valid_student.final_score = 85;
    EXPECT_NO_THROW(valid_student.validate());
    Student invalid_student;
    invalid_student.hw = {101};
    EXPECT_THROW(invalid_student.validate(), std::domain_error);
}

TEST(ComputeGradeTests, ComparisonOperators) {
    Student student1;
    student1.last_name = "D";
    student1.first_name = "J";

    Student student2;
    student2.last_name = "D";
    student2.first_name = "J";

    EXPECT_TRUE(student1 < student2);
    EXPECT_FALSE(student1 == student2);
}


TEST(ComputeGradeTests, ValidateThrowsExceptionOnInvalidScores) {
    Student s;
    s.hw = {95, 85, -5};
    EXPECT_THROW(s.validate(), std::domain_error);
}*/
TEST(GradebookTests, ValidateStudentScoresErrorMessage) {
    std::stringstream ss;
    // Simulate input file content with an invalid HW score
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
