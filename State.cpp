#include "State.h"

void State::add_transition(int label, State * to) {
	this->transitions.push_back(new Transition(label, to));
	to->transitions.push_back(new Transition(label, this));
}

State::~State() {
	/*
	vector<Transition *>::iterator it;
	for (it = this->transitions.begin() ; it != this->transitions.end() ; it++) {
		(*it)->~Transition();	

	}*/

	delete this;
}
