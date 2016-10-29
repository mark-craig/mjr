// #include "gtest/gtest.h"
// #include "objects.h"

// TEST(PolygonIntersectionTest, SkewedPlaneAtOrigin) {
// 	// coordinates obtained from Maya
// 	vector<Vector3D> verts = {Vector3D(-1, -1, -1), 
// 						  		Vector3D(-1, 1, -1),
// 						  		Vector3D(1, 1, 1),
// 						  		Vector3D(1, -1, 1)};

// 	Polygon plane = Polygon(verts);
// 	Ray test1 = Ray(Vector3D(-1, 0, 0), Vector3D(1, 0, 0)); // should intersect
// 	Ray test2 = Ray(Vector3D(-2, 0, 0), Vector3D(0, 1, 0)); // should not intersect
// 	Intersection intersectionPoint;
// 	bool test1result = plane.intersect(test1, intersectionPoint);
// 	EXPECT_EQ(test1result, true);
// 	EXPECT_FLOAT_EQ(intersectionPoint.time, 1.0f);
// 	cerr << intersectionPoint.time << endl;
// 	EXPECT_FLOAT_EQ(intersectionPoint.position.x, 0.0f);
// 	EXPECT_FLOAT_EQ(intersectionPoint.position.y, 0.0f);
// 	EXPECT_FLOAT_EQ(intersectionPoint.position.z, 0.0f);
// 	bool test2result = plane.intersect(test2, intersectionPoint);
// 	EXPECT_EQ(test2result, false);
// }