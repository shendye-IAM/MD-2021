#include "ga_vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(double x[3]) {
	this->x = x[0];
	this->y = x[1];
	this->z = x[2];
}

void Vector3::RandomVector(Vector3 lowerBounds, Vector3 upperBounds, std::default_random_engine& defEngine)
{
	std::uniform_real_distribution<double> dblDistroX(lowerBounds.x, upperBounds.x);
	std::uniform_real_distribution<double> dblDistroY(lowerBounds.y, upperBounds.y);
	std::uniform_real_distribution<double> dblDistroZ(lowerBounds.z, upperBounds.z);
	this->x = dblDistroX(defEngine);
	this->y = dblDistroY(defEngine);
	this->z = dblDistroZ(defEngine);
}

void Vector3::RandomNormalizedVector(std::default_random_engine defEngine)
{
	Vector3 vector;
	vector.RandomVector(Vector3(0,0,0), Vector3(1, 1, 1), defEngine);
	vector.Normalize();
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

double Vector3::EuclideanDistance(Vector3 vector)
{
	double distance;

	double deltaX = x - vector.x;
	double deltaY = y - vector.y;
	double deltaZ = z - vector.z;

	distance = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
	distance = sqrt(distance);
	return distance;
}

double Vector3::GetLength()
{
	double length = x * x + y * y + z * z;
	length = sqrt(length);
	return length;
}

void Vector3::Normalize()
{
	double multiplier = (double)1 / GetLength();
	this->x = this->x * multiplier;
	this->y = this->y * multiplier;
	this->z = this->z * multiplier;
}

double Vector3::MagnitudeSquared()
{
	return this->GetLength() * this->GetLength();
}

double Vector3::DotProduct(Vector3 vector)
{
	return this->x*vector.x + this->y*vector.y + this->z*vector.z;
}

Vector3 Vector3::operator*(int number)
{
	Vector3 vector = Vector3(this->x * number, this->y * number, this->z * number);
	return vector;
}

Vector3 Vector3::operator*(double number)
{
	Vector3 vector = Vector3(this->x * number, this->y * number, this->z * number);
	return vector;
}

Vector3 Vector3::operator+(const Vector3& vector)
{
	Vector3 sum;
	sum.x = this->x + vector.x;
	sum.y = this->y + vector.y;
	sum.z = this->z + vector.z;

	return sum;
}

Vector3 Vector3::operator-(const Vector3& vector)
{
	Vector3 sum;
	sum.x = this->x - vector.x;
	sum.y = this->y - vector.y;
	sum.z = this->z - vector.z;

	return sum;
}
