#ifndef TRANSITION_H
#define TRANSITION_H

#include "State.h"

class State;

// marks transitions
class Transition {
	public:

		Transition() {
			this->label = ' ';
			this->to = nullptr;

		}

		Transition(int label, State * to) {
			this->label = label;
			this->to = to;

		}

		

		~Transition();		

		// label (int): the label of this transition
		// (between 0 and 9 or lowercase a and lowercase z) 
		int label;

		// to (State): the state that this transition leads
		// TO, held as a pointer that can be switched
		State * to;

};

#endif
