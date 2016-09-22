#pragma once
class BaseMode {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void input() = 0;
};

