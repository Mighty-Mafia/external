#pragma once

namespace Offsets {
	inline constexpr u64 Children = 0x80;
	inline constexpr u64 Name = 0x78;
	inline constexpr u64 ClassDescriptor = 0x18;

	inline constexpr u64 LocalPlayer = 0x128;
	inline constexpr u64 ModelInstance = 0x340;

	inline constexpr u64 Dimensions = 0x720;
	inline constexpr u64 ViewMatrix = 0x4B0;

	inline constexpr u64 FakeDataModel = 0x68D7308;
	inline constexpr u64 RealDataModel = 0x1C0;
	inline constexpr u64 VisualEngine = 0x6719638;

}
