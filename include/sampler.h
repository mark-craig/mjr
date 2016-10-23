#pragma once
class Sampler {
	public:
	// constructor
	Sampler(int ix, int iy);
	//methods
	bool getSample(Sample &sample);

	private:
	//fields
	int x;
	int y;
	int current_x = 0;
	int current_y = 0;
};