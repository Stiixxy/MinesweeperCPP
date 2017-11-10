#include "StateManager.h"

void StateManager::AddState(StateRef newState, bool isReplacing) {

	_isAdding = true;
	_isReplacing = isReplacing;
	
	_newState = std::move(newState);

}

void StateManager::RemoveState() {
	_isRemoving = true;
}

void StateManager::RemoveAllStates() {
	_removeAll = true;
}

void StateManager::ProcessStateChanges() {

	if (_removeAll) {
		while (_states.size() > 0) _states.pop_back();
		_removeAll = false;
	}

	if (_isRemoving && !_states.empty()) {
		_states.back()->BeforeDestroy();
		_states.pop_back();
	
		_isRemoving = false;
	}

	if (_isAdding) {
		if (!_states.empty()) {
			if (_isReplacing) {
				_states.pop_back();
			}
		}

		_newState->Init();//Init before adding so if the state wants it can get a ref to the current state
		_states.push_back(std::move(_newState));
		_isAdding = false;
	}
}

StateRef &StateManager::GetActiveState() {
	return _states.back();
}

StateRef &StateManager::GetState(int i) {
	return _states.at(i);
}