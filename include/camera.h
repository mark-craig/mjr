class Camera
{
public:
	//position
	double x; double y; double z;
	// lower left
	double llx; double lly; double llz;
	// lower right
	double lrx; double lry; double lrz;
	// upper left
	double ulx; double uly; double ulz;
	// upper right
	double urx; double ury; double urz;

	//constructors
	Camera();
	Camera(double x, double y, double z,
		   double illx, double illy, double illz,
		   double ilrx, double ilry,double ilrz,
		   double iulx, double iuly,double iulz,
		   double iurx, double iury,double iurz);

	// other methods
	Vector3D getPosition();
};
