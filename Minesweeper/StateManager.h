#pragma once

#include "State.h"

#include <memory>
#include <vector>

typedef std::unique_ptr<State> StateRef;

class StateManager {

public:
	StateManager() {}
	~StateManager() {}

	void AddState(StateRef, bool = true);
	void RemoveState();
	void RemoveAllStates();

	void ProcessStateChanges();

	StateRef &GetActiveState();
	StateRef &GetState(int);

private:
	std::vector<StateRef> _states;
	StateRef _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
	bool _removeAll;

};