#pragma once
#include "Command.h"

class JumpCommand : public Command {
public:
	virtual void execute(Robot& actor) {
		actor.jump();
	};
};

class ShootCommand : public Command {
public:
	virtual void execute(Robot& actor) {
		actor.shoot();
	};
};

//Buttons Y AND B
class Y : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "Y" << std::endl;
	};
};
class B : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "B" << std::endl;
	};
};
// DPAD
class UP : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "UP" << std::endl;
	};
};
class Down : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "Down" << std::endl;
	};
};
class Right : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "right" << std::endl;
	};
};
class Left : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "Left" << std::endl;
	};
};

// LB AND RB
class Lb : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "LB" << std::endl;
	};
};
class RB : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "RB" << std::endl;
	};
};


//STart and select
class Select : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "select" << std::endl;
	};
};
class Start : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "start" << std::endl;
	};
};
// joystick buttons
class L3 : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "L3" << std::endl;
	};
};
class R3 : public Command {
public:
	virtual void execute(Robot& actor) {
		std::cout << "R3" << std::endl;
	};
};
