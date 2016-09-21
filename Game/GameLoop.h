#pragma once
class GameLoop {
private:
	void input();
	void update();
	void render();
public:
	GameLoop();
	~GameLoop();

	void startLoop();
};

