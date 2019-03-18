#include "States/StateMachine.hpp"
#include <iostream>


namespace cp{
	StateMachine::StateMachine(){
	}
	StateMachine::~StateMachine(){
	}
	void StateMachine::add_state(StateRef new_state, bool is_replacing) {
		is_adding=true;
		this->is_replacing=is_replacing;
		this->new_state=std::move(new_state);
	}
	void StateMachine::remove_state() {
		is_removing=true;
	}
	void StateMachine::process_state_change() {
		if(is_removing && !stack_state.empty() ){

			stack_state.pop();
			if(!stack_state.empty())
				stack_state.top()->resume();
			is_removing=false;
		}
		if(is_adding){

			if(!stack_state.empty()){
				if(is_replacing)
					stack_state.pop();
				else
					stack_state.top()->pause();
			}
			stack_state.push(std::move(new_state));\
			stack_state.top()->init();
			is_adding=false;
		}
	}
	StateRef& StateMachine::get_active_state() {
		return stack_state.top();
	}
}
