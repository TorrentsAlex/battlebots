#pragma once
class BaseScreen {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void input() = 0;
	virtual void clean() = 0;
	virtual void init() = 0;
};