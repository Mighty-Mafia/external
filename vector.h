#pragma once

#ifndef VECTOR_H
#define VECTOR_H

struct Vector2 final {
	f32 x{ 0 }, y{ 0 };
};

struct Vector3 final {
	f32 x{ 0 }, y{ 0 }, z{ 0 };
};

struct Vector4 final {
	f32 x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 };
};

#endif // VECTOR_H
