#pragma once
#include "Command.h"

class JoystickCommand {
public:
	virtual ~JoystickCommand() {};
	virtual void execute(Robot& actor) = 0;
};