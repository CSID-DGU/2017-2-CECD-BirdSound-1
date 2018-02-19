#pragma once
#include<iostream>
class double3
{
public:
	double X, Y, Z;
	double3(double _X, double _Y, double _Z) :X(_X), Y(_Y), Z(_Z) {}

	friend std::ostream &operator<<(std::ostream &os, const double3& value)
	{
		os << value.X << " " << value.Y << " " << value.Z;
		return os;
	}
	double *getData()
	{
		double data[3] = { X,Y,Z };
		return data;
	}
};