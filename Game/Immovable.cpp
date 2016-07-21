#include "Immovable.h"

Immovable::Immovable() {
}

Immovable::Immovable(OBJ* mesh, GameObject gameObject) :
	Object(mesh, gameObject) {
}

Immovable::~Immovable() {
}