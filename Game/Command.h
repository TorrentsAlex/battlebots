#pragma once
#include "Robot.h"

class Command {
public:
	virtual ~Command() {};
	virtual void execute(Robot& actor) = 0;
};