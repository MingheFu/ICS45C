#include <fstream>
#include <compute_grades.hpp>

using namesapce std;

int main() {
	ifstream gradebook{"gradebook.txt."};
	Gradebook b;
	gradebook >> b;

	b.validate();
	b.compute_grade();
	b.sort();

	ofstream course_grades{"course_grades.txt"};

	course_grades << b;
}


