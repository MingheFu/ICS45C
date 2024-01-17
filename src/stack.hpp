constexpr int STK_MAX = 1000;

class Stack
{
	int _top;
	char buf[STK_MAX];
public:
	// constructs this stack
	Stack(): _top(-1){
	}
	// adds c to the top of this Stack
	void push(char c){
		if (!isFull()){
			buf[++_top] = c;
		} else {
			std::cerr << "Stack is full.\n";
		}
	}
	// removes and returns the top character of this Stack
	char pop(){
		if (!isEmpty()){
			return buf[_top--];
		} else {
			std::cerr << "Stack is empty.\n";
			return '@';
			}
	}
	// peeks at the top char and returns it without removing
	char top(){
		if (!isEmpty()){
			return buf[_top];
		} else {
			std::cerr << "Stack is empty.\n";
			return '@';
		}
	}
	// returns true iff this stack is empty
	bool isEmpty(){
		return _top == -1;
	}
	// returns true iff this stack is full
	bool isFull(){
		return _top ==STK_MAX -1;
	}
};

// pushes all the characters from string line onto the Stack stk
void push_all(Stack & stk, string line){
	for (char c: line){
		stk.push(c);
	}
}
// pops characters from stk and prints to cout
// all chars will be on the same line without any extra spaces
void pop_all(Stack & stk) {
	while (!stk.isEmpty()) {
		std::cout << stk.pop();
	}
}

