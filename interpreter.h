#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
// The point of this class is to create an object that 
// manages the menus and such at the beginning of the 
// chess program. It will then initialize controller 
// or the chess game player accordingly. Right now, it 
// should be able to determine between when a user 
// wants to go to the opening book, explore and modify
// the games library.

class Interpreter {
	std::string openingBook;
	std::string gameBook;
public:
	Interpreter(); // Should add ability to use a different opening book later. 
	void initiate();
	void help(std::string);
};

#endif

