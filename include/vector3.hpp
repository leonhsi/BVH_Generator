#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <bits/stdc++.h>

namespace  bvh{

const double Zero = 1e-6;

class Vector3{
private:
	double x, y, z;
public:
	//constructor
	Vector3():x(0), y(0), z(0){}
	Vector3(double d) : x(d), y(d), z(d) {}
	Vector3(double x1, double y1, double z1) : x(x1), y(y1), z(z1) {}
	~Vector3();

	//operator overloadding
	// void operator=(const Vector3 &v);
    // Vector3 operator+(const Vector3 &v);
    // Vector3 operator-(const Vector3 &v);
    // Vector3 operator/(const Vector3 &v);
    // Vector3 operator*(const Vector3 &v);
    // Vector3 operator+(float f);
    // Vector3 operator-(float f);
    // Vector3 operator/(float f);
    // Vector3 operator*(float f);

	double& operator [] (size_t i) {return (i==0) ? x : ((i==1) ? y : z);};
	double  operator [] (size_t i) const {return (i==0) ? x : ((i==1) ? y : z);};
};

// Vector3 Vector3::operator+(const Vector3 &v){
// 	return Vector3(x+v.x, y+v.y, z+v.z);
// }

// Vector3 Vector3::operator-(const Vector3 &v){
// 	return Vector3(x-v.x, y-v.y, z-v.z);
// }

// Vector3 Vector3::operator/(const Vector3 &v){
// 	if(fabsf(v.x) <= Zero || fabsf(v.y) <= Zero || fabsf(v.z) <= Zero){
// 		std::cerr<<"Overflow\n";
// 		return *this;
// 	}
// 	return Vector3(x/v.x, y/v.y, z/v.z);
// }

// Vector3 Vector3::operator*(const Vector3 &v){
// 	return Vector3(x*v.x, y*v.y, z*v.y);
// }

// Vector3 Vector3::operator+(float f){
// 	return Vector3(x+f, y+f, z+f);
// }

// Vector3 Vector3::operator-(float f){
// 	return Vector3(x-f, y-f, z-f);
// }

// Vector3 Vector3::operator/(float f){
// 	if(fabsf(f) < Zero){
// 		std::cerr<<"Overflow\n";
// 		return *this;
// 	}
// 	return Vector3(x/f, y/f, z/f);
// }

// Vector3 Vector3::operator*(float f){
// 	return Vector3(x*f, y*f, z*f);
// }

Vector3 operator+(const Vector3 &a, const Vector3 &b){
	Vector3 ret;
	for(auto i=0; i<3; i++){
		ret[i] = a[i] + b[i];
	}
	return ret;
}

Vector3 operator-(const Vector3 &a, const Vector3 &b){
	Vector3 ret;
	for(auto i=0; i<3; i++){
		ret[i] = a[i] - b[i];
	}
	return ret;
}

Vector3 operator*(const Vector3 &a, const Vector3 &b){
	Vector3 ret;
	for(auto i=0; i<3; i++){
		ret[i] = a[i] * b[i];
	}
	return ret;
}

Vector3 min(const Vector3 &a, const Vector3 &b){
	Vector3 ret;
	for(auto i=0; i<3; i++){
		ret[i] = std::min(a[i], b[i]);
	}
	return ret;
}

Vector3 max(const Vector3 &a, const Vector3 &b){
	Vector3 ret;
	for(auto i=0; i<3; i++){
		ret[i] = std::max(a[i], b[i]);
	}
	return ret;
}

Vector3 cross(const Vector3 &a, const Vector3 &b){
	Vector3 ret;
	for(auto i=0; i<3; i++){
		size_t j = (i+1) % 3;
		size_t k = (i+2) % 3;
		ret[i] = a[j] * b[k] - a[k] * b[j];
	}
	return ret;
}

} //namespace bvh

#endif