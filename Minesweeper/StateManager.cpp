#include "StateManager.h"

void StateManager::AddState(StateRef newState, bool isReplacing) {

	this->_isAdding = true;
	this->_isReplacing = isReplacing;
	
	this->_newState = std::move(newState);

}

void StateManager::RemoveState() {
	this->_isRemoving = true;
}

void StateManager::ProcessStateChanges() {

	if (this->_isRemoving && !this->_states.empty()) {
		this->_states.top()->BeforeDestroy();
		this->_states.pop();
	
		this->_isRemoving = false;
	}

	if (this->_isAdding) {
		if (!this->_states.empty()) {
			if (this->_isReplacing) {
				this->_states.pop();
			}
		}

		_newState->Init();//Init before adding so if the state wants it can get a ref to the current state
		this->_states.push(std::move(this->_newState));
		this->_isAdding = false;
	}
}

StateRef &StateManager::GetActiveState() {
	return this->_states.top();
}