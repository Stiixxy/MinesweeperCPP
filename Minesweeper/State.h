#pragma once

#include <memory>
#include <stack>

class State {
public:
	virtual void Init() = 0;
	virtual void BeforeDestroy() = 0; //For cleanup

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
private:
};

