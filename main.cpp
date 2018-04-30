#include "Transition.h"

int main(int argc, char * argv[]) {
	State * s1 = new State(1);
	State * s2 = new State(2);
	State * s3 = new State(3);
	State * s4 = new State(4);
	State * s5 = new State(5);
	State * s6 = new State(6);

	s1->add_transition(12, s2);
	s1->add_transition(1, s6);
	s2->add_transition(6, s3);
	s2->add_transition(3, s6);
	s3->add_transition(3, s4);
	s3->add_transition(20, s6);
	s4->add_transition(1, s5);
	s4->add_transition(6, s6);
	s5->add_transition(2, s1);
	s5->add_transition(4, s6);
	
	int i = 1;
	State * states[6] = {s1, s2, s3, s4, s5, s6};
	std::vector<Transition *> cur;
	return 0;
}
