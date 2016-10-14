using namespace std;

class Vector3D
{
public:
	// fields
	double x;
	double y;
	double z;
	
	// constructors
	Vector3D();
	Vector3D(double inputx, double inputy, double inputz);
	// other methods
	double magnitude();
	Vector3D normalize();
	Vector3D scale(double scalefactor);
	Vector3D add(Vector3D v2);
	Vector3D subtract(Vector3D v2);
	double dot(Vector3D v2);
	Vector3D cross(Vector3D v2);
	Vector3D project(Vector3D v2);
	double getTheta(Vector3D v2);
};

