#include <SDK/Classes/Instance.h>
#include <SDK/Offsets.h>

str RBX::Instance::getName() {
	u64 name = Comms->read<u64>(address + Offsets::Name);

	if (name) {
		return Comms->readstr(name);
	}

	return "unknown";
}

str RBX::Instance::getClassName() {
	u64 name = Comms->read<u64>(address + Offsets::ClassDescriptor);
	u64 size = Comms->read<u64>(name + 0x8);

	if (size) {
		return Comms->readstr(size);
	}

	return "unknown";
}

std::vector<RBX::Instance> RBX::Instance::getChildren() {
	std::vector<RBX::Instance> children;

	u64 start = Comms->read<u64>(address + Offsets::Children);
	u64 end = Comms->read<u64>(start + 0x8);

	for (u64 child = Comms->read<u64>(start); child != end; child += 0x10) {
		children.push_back(RBX::Instance(Comms->read<u64>(child)));
	}

	return children;
}

RBX::Instance RBX::Instance::findFirstChild(const str& name) {
	std::vector<RBX::Instance> children = getChildren();

	for (RBX::Instance& child: children) {
		if (child.getName() == name) {
			return child;
		}
	}

	return RBX::Instance();
}

RBX::Instance RBX::Instance::findFirstChildByClass(const str& name) {
	std::vector<RBX::Instance> children = getChildren();

	for (RBX::Instance& child : children) {
		if (child.getClassName() == name) {
			return child;
		}
	}

	return RBX::Instance();
}

u64 RBX::Instance::getAddress() {
	return address;
}
