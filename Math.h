#pragma once



struct fVec2
{
	float x, y;

	fVec2(float _x, float _y);
	fVec2();

	float& operator[](int index);
	float sqrMag();
	float mag();
};


struct fVec3
{
	float x, y, z;
	fVec3(float _x, float _y, float _z);
	fVec3();

	float& operator[](int index);
	float sqrMag();
	float mag();
};



struct iVec2
{
	int x, y;

	iVec2(int _x, int _y);
	iVec2();

	int& operator[](int index);
};


struct iVec3
{
	int x, y, z;
	iVec3(int _x, int _y, int _z);
	iVec3();

	int& operator[](int index);
};