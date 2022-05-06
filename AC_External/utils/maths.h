#pragma once

namespace Math {
    bool World2Screen(Vector3 position, int width, int height, Vector2& screenposition);
    float CalcDistanceVec3(Vector3& pos1, Vector3& pos2);
    Vector3 SubtractVec3(Vector3& src, Vector3& dst);
    float CalcDistanceVec2(Vector2& pos1, Vector2& pos2);
    Vector2 CalcAngles(Vector3& local_pos, Vector3& target_pos);
    float Magnitude(Vector3 vec);
};
