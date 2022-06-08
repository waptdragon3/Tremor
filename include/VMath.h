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

	fVec3(fVec2 v);

	float& operator[](int index);
	float sqrMag();
	float mag();
};

//basic operators
fVec2 operator+(fVec2 u, fVec2 v);
fVec2 operator-(fVec2 u, fVec2 v);
fVec2 operator*(fVec2 v, float s);
fVec2 operator/(fVec2 v, float s);
//negate vector
fVec2 operator-(fVec2 v);
//assignment operators
fVec2& operator+=(fVec2& l, fVec2& r);
fVec2& operator-=(fVec2& l, fVec2& r);
fVec2& operator*=(fVec2& l, float& r);
fVec2& operator/=(fVec2& l, float& r);


//operators
fVec3 operator+(fVec3 u, fVec3 v);
fVec3 operator-(fVec3 u, fVec3 v);
fVec3 operator*(fVec3 v, float s);
fVec3 operator/(fVec3 v, float s);
//negate vector
fVec3 operator-(fVec3 v);
//assignment operators
fVec3& operator+=(fVec3& l, fVec3& r);
fVec3& operator-=(fVec3& l, fVec3& r);
fVec3& operator*=(fVec3& l, float& r);
fVec3& operator/=(fVec3& l, float& r);


class Transform
{
private:
	float items[16];
	Transform();
public:

	float& operator[](unsigned int index);

	float& get(unsigned int i, unsigned int j);

	static Transform Identity();
	static Transform Translate(fVec3 pos);
	static Transform Rotate(float thetaRad, fVec3 axis);
	static Transform Perspective(float fov, float aspectRatio, float near, float far);
	static Transform Scale(fVec3 scaleFactors);

	Transform operator* (Transform t);
	friend class Shader;

};

float degreesToRad(float degrees);