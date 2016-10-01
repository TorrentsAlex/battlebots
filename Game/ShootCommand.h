#pragma once
#include "Command.h"

class ShootCommand : public Command {
public:
	virtual void execute(Robot& actor) {
		actor.shoot();
	};
};
