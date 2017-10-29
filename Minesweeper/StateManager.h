#pragma once

#include "State.h"

#include <memory>
#include <stack>

typedef std::unique_ptr<State> StateRef;

class StateManager {

public:
	StateManager() {}
	~StateManager() {}

	void AddState(StateRef, bool = true);
	void RemoveState();

	void ProcessStateChanges();

	StateRef &GetActiveState();

private:
	std::stack<StateRef> _states;
	StateRef _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;

};