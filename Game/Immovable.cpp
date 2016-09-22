#include "Immovable.h"

Immovable::Immovable() {
}

Immovable::Immovable(OBJ* mesh, GameObject gameObject) :
	Entity(mesh, gameObject) {
}

Immovable::~Immovable() {
}