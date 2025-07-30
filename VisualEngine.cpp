#include <SDK/Classes/VisualEngine/VisualEngine.h>
#include <SDK/Offsets.h>

/*
namespace RBX {
	class VisualEngine : public Instance {
	private:
		Vector2 getDimensions();
		Matrix4 getViewMatrix();
	public:
		Vector2 worldToScreen(const Vector3& world);
	};
}
*/

Vector2 RBX::VisualEngine::getDimensions() {
	return Comms->read<Vector2>(address + Offsets::Dimensions);
}

Matrix4 RBX::VisualEngine::getViewMatrix() {
	return Comms->read<Matrix4>(address + Offsets::ViewMatrix);
}

Vector2 RBX::VisualEngine::worldToScreen(const Vector3& world) {
	Vector4 quaternion;

	Vector2 dimensions = getDimensions();
	Matrix4 viewMatrix = getViewMatrix();

	quaternion.x = (world.x * viewMatrix.data[0]) + (world.y * viewMatrix.data[1]) + (world.z * viewMatrix.data[2]) + viewMatrix.data[3];
	quaternion.y = (world.x * viewMatrix.data[4]) + (world.y * viewMatrix.data[5]) + (world.z * viewMatrix.data[6]) + viewMatrix.data[7];
	quaternion.z = (world.x * viewMatrix.data[8]) + (world.y * viewMatrix.data[9]) + (world.z * viewMatrix.data[10]) + viewMatrix.data[11];
	quaternion.w = (world.x * viewMatrix.data[12]) + (world.y * viewMatrix.data[13]) + (world.z * viewMatrix.data[14]) + viewMatrix.data[15];

	Vector2 screen;

	if (quaternion.w < 0.1f) {
		return screen;
	}

	Vector3 normalizedDeviceCoordinates;
	normalizedDeviceCoordinates.x = quaternion.x / quaternion.w;
	normalizedDeviceCoordinates.y = quaternion.y / quaternion.w;
	normalizedDeviceCoordinates.z = quaternion.z / quaternion.w;

	screen.x = (dimensions.x / 2.0f * normalizedDeviceCoordinates.x) + (dimensions.x / 2.0f);
	screen.y = -(dimensions.y / 2.0f * normalizedDeviceCoordinates.y) + (dimensions.y / 2.0f);

	return screen;
}
