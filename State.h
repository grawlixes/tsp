#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include "Transition.h"

using namespace std;

class Transition;

// marks states
class State {
	public:	

		State() {
			this->label = -1;
			this->transitions = {};
		}

		State(int label) {
			this->label = label;
			this->transitions = {};
		}

		void add_transition(int label, State * to);

		~State();

		// label (integer): the label of the state
		// (always between 1 and 1000)
		int label;

		// transitions (array of characters):
		// a pointer to the beginning of a list
		// of LABELS OF transitions FROM this state
		vector<Transition *> transitions;
};

#endif
