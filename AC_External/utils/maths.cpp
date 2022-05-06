#include "includes.h"

float Math::CalcDistanceVec3(Vector3 &pos1, Vector3 &pos2) {
	double distance{ 0.0 };
	distance += sqrt(pow((pos2.x - pos1.x), 2.0f) + pow((pos2.y - pos1.y), 2.0f) + pow((pos2.z - pos1.z), 2.0f));

	return (float) sqrt(distance);
}

Vector3 Math::SubtractVec3(Vector3& src, Vector3& dst) {
    Vector3 diff;
    diff.x = src.x - dst.x;
    diff.y = src.y - dst.y;
    diff.z = src.z - dst.z;
    return diff;
}

float Math::CalcDistanceVec2(Vector2& pos1, Vector2& pos2) {
	double distance{ 0.0 };
	distance += sqrt(pow((pos2.x - pos1.x), 2.0f) + pow((pos2.y - pos1.y), 2.0f));

	return (float)sqrt(distance);
}


Vector2 Math::CalcAngles(Vector3 &local_pos, Vector3 &target_pos) {

	Vector3 delta{ Math::SubtractVec3(target_pos, local_pos) };
	float delta_length{ Math::Magnitude(delta) };

	Vector2 angles;

	angles.x = (float)-atan2(delta.x, delta.y) * (180.0f / (float)M_PI) + 180.0f; // yaw
	angles.y = (float)asin(delta.z / delta_length) * (180.0f / (float)M_PI); // pitch

	return angles;
}

float Math::Magnitude(Vector3 vec) {
    return (float) sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

bool Math::World2Screen(Vector3 position, int width, int height, Vector2& screenposition) {
	Matrix4x4 viewMatrix = interfaces->getViewMatrix();

	float x_value = (position.x * viewMatrix.matrix[0]) + (position.y * viewMatrix.matrix[4]) + (position.z * viewMatrix.matrix[8]) + viewMatrix.matrix[12];
	float y_value = (position.x * viewMatrix.matrix[1]) + (position.y * viewMatrix.matrix[5]) + (position.z * viewMatrix.matrix[9]) + viewMatrix.matrix[13];
	float w_value = (position.x * viewMatrix.matrix[3]) + (position.y * viewMatrix.matrix[7]) + (position.z * viewMatrix.matrix[11]) + viewMatrix.matrix[15];

	if (w_value < 1.0f) {
		return false;
	}

	float cam_x = width / 2.0f;
	float cam_y = height / 2.0f;

	screenposition.x = cam_x + (cam_x * x_value / w_value);
	screenposition.y = cam_y - (cam_y * y_value / w_value);

	return true;
}
