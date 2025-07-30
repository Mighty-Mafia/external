#include <SDK/Classes/DataModel/Player.h>
#include <SDK/Offsets.h>

RBX::ModelInstance RBX::Player::getModelInstance() {
	return RBX::ModelInstance(Comms->read<u64>(address + Offsets::ModelInstance));
}
