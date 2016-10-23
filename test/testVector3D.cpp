#include "gtest/gtest.h"
#include "vector3d.h"
 
TEST(Vector3DTest, AssertionTrue) {
    Vector3D v1 = Vector3D(1.0, 1.0, 1.0);
    Vector3D v2 = Vector3D(1.0, 1.0, 1.0);
    ASSERT_EQ(v1.dot(v2), 3.0);
}