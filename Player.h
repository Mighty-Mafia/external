#pragma once
#include <SDK/Classes/Instance.h>
#include <SDK/Classes/DataModel/ModelInstance.h>

namespace RBX {
	class Player : public Instance {
	public:
		RBX::ModelInstance getModelInstance();
	};
}
