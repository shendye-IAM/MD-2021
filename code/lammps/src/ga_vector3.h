#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include <random>
#include <time.h>
#include <math.h>

class Vector3
{
public:
	double x;
	double y;
	double z;
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(double x[3]);
	void RandomVector(Vector3 lowerBounds, Vector3 upperBounds, std::default_random_engine& defEngine);
	void RandomNormalizedVector(std::default_random_engine defEngine);
	double EuclideanDistance(Vector3 vector); //calculates the euclidean distance between this and vector
	double GetLength();
	void Normalize();
	double MagnitudeSquared();
	double DotProduct(Vector3 vector);

	//Operator Overloading
	Vector3 operator*(int number);
	Vector3 operator*(double number);
	Vector3 operator+(const Vector3& vector);
	Vector3 operator-(const Vector3& vector);
};

#endif

