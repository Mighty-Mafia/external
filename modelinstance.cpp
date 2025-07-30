#include <SDK/Classes/DataModel/ModelInstance.h>

bool RBX::ModelInstance::isRig15() {
	if (findFirstChild("Upper Torso").getAddress()) {
		return true;
	}
	else if (findFirstChild("Torso").getAddress()) {
		return false;
	}

	return false;
}
