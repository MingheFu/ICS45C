#include "compute_grades.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>

#include <iomanip>
#include <iterator>
#include <cmath>

void Student::validate() const {
	    auto check_score = [](int score) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(score));
        }
    };
    std::for_each(hw.begin(), hw.end(), check_score);
    std::for_each(quiz.begin(), quiz.end(), check_score);
    check_score(final_score);
}

void Student::compute_grade() {
    //compute_quiz_avg();
	//compute_hw_avg();
	compute_course_score();
	if (course_score >= 97) course_grade = "A+";
	else if (course_score >= 93) course_grade = "A";
	else if (course_score >= 90) course_grade = "A-";
    else if (course_score >= 87) course_grade = "B+";
    else if (course_score >= 83) course_grade = "B";
    else if (course_score >= 80) course_grade = "B-";
    else if (course_score >= 77) course_grade = "C+";
    else if (course_score >= 73) course_grade = "C";
    else if (course_score >= 70) course_grade = "C-";
    else if (course_score >= 67) course_grade = "D+"; 
    else if (course_score >= 63) course_grade = "D";
    else if (course_score >= 60) course_grade = "D-";
    else course_grade = "F";
}

void Student::compute_quiz_avg() {
	if (!quiz.empty()) {
        double sum = std::accumulate(quiz.begin(), quiz.end(), 0.0);
        double lowest = *std::min_element(quiz.begin(), quiz.end());
        quiz_avg = quiz.size() > 1 ? (sum - lowest) / (quiz.size() - 1) : quiz[0];
    } else {
        quiz_avg = 0.0;
    }
}

void Student::compute_hw_avg() {
	//hw_avg = hw.empty() ? 0.0 : std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
	if (!hw.empty()) {
        double sum = std::accumulate(hw.begin(), hw.end(), 0.0);
        hw_avg = sum / hw.size();
    } else {
        hw_avg = 0.0;
    }
}

void Student::compute_course_score() {
	compute_hw_avg();
	compute_quiz_avg();
	course_score = std::round((quiz_avg * 0.4) + (hw_avg * 0.3) + (final_score * 0.3));
}

std::strong_ordering Student::operator<=>(const Student& other) const {
	    if (auto cmp = last_name <=> other.last_name; cmp != 0) 
        	return cmp;
    return first_name <=> other.first_name;
}

bool Student::operator==(const Student& other) const {
	return last_name == other.last_name && first_name == other.first_name;
}

void Gradebook::compute_grades() {
        std::for_each(students.begin(), students.end(), [](Student& student) {
        student.compute_grade();
    });
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}

void Gradebook::validate()const {
	    std::for_each(students.begin(), students.end(), [](const Student& student) {
        student.validate();
    });
}

std::istream& operator>>(std::istream& in, Student& s) {
    s.first_name.clear();
    s.last_name.clear();
    s.hw.clear();
    s.quiz.clear();
    s.final_score = 0;  
	  std::string line, keyword;
    while (std::getline(in, line) && !line.empty()) {
        std::istringstream iss(line);
        iss >> keyword;
        if (keyword == "Name") {
            s.first_name = s.last_name = "";
            iss >> s.first_name;
            std::getline(iss >> std::ws, s.last_name);
        } else if (keyword == "Quiz") {
            s.quiz.clear();
            int score;
            while (iss >> score) {
                s.quiz.push_back(score);
            }
        } else if (keyword == "HW") {
            s.hw.clear();
            int score;
            while (iss >> score) {
                s.hw.push_back(score);
            }
        } else if (keyword == "Final") {
            iss >> s.final_score;
        }
    }
    s.validate();
    return in; 
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student student;
    while (in >> student) {
		student.validate();
        b.students.push_back(student);
		student = Student();
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::left << std::setw(8) << "Name:"  << s.first_name << ' ' << s.last_name << '\n'
        << std::left << std::setw(8) << "HW Ave:"  << s.hw_avg << '\n'
        << std::left << std::setw(8) << "QZ Ave:"  << s.quiz_avg << '\n'
        << std::left << std::setw(8) << "Final:"   << s.final_score << '\n'
        << std::left << std::setw(8) << "Total:"   << s.course_score << '\n'
        << std::left << std::setw(8) << "Grade:"   << s.course_grade << "\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b){
	
	for (const Student& student : b.students) {
        out << student << '\n';
	}
    return out;
}


