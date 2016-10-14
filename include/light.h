class Light
{
public:
	//fields
	bool pointLight;
	bool directionalLight;
	//position
	double x;
	double y;
	double z;
	//color
	double r;
	double g;
	double b;

	//constructors
	Light();
	Light(double ix, double iy, double iz, double ir, double ig, double ib, int flag);

	// other methods
	Vector3D getVector();
	Vector3D getColor();
};
