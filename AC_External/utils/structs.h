#pragma once

// Needed to allow ExtInterface to get strings
// CBA to make another method in ExtInterface
class String16 {
public:
	char str[16];

	std::string toString() {
		return std::string{ str };
	}
};

struct Matrix4x4 {
	float matrix[16];
};

struct Vector4 {
	float x, y, z, w;
};

struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, y;
};
