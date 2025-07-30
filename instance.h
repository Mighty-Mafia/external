#pragma once

namespace RBX {
	class Instance {
	public:
		u64 address;

		Instance() = default;
		Instance(u64 address) : address(address) {}

		str getName();
		str getClassName();

		std::vector<RBX::Instance> getChildren();
		RBX::Instance findFirstChild(const str& name);
		RBX::Instance findFirstChildByClass(const str& className);

		u64 getAddress();
	};
}
