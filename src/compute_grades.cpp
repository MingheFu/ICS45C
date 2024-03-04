#include "compute_grade.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <iterator>

void Student::validate() const {
	for (int score : hw) {
		if (score < 0 || score > 100) 
			throw std::domain_error("Error: invalid percentage " + std::to_string(score));
	}
	for (int socre: quiz) {	
		if (score < 0 || score > 100) 
			throw std::domain_error("Error: invalid percentage" + std::to_string(score));
	}
	if (final_score < 0 || finale_score > 100)
		throw std::domain_error("Error: invalid percentage" + std::to_string(score));
}

void Student::compute_grade() {
    if (!quiz.empty()) {
        double sum = std::accumulate(quiz.begin(), quiz.end(), 0.0);
        double lowest = *std::min_element(quiz.begin(), quiz.end());
        quiz_avg = quiz.size() > 1 ? (sum - lowest) / (quiz.size() - 1) : quiz[0];
    } else {
        quiz_avg = 0.0;
    }
    hw_avg = hw.empty() ? 0.0 : std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();

    course_score = std::round((quiz_avg * 0.4) + (hw_avg * 0.3) + (final_score * 0.3));
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

