#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <iostream>

using namespace std;


class Vector3
{
public:
	//Overloaded Constructor so it can take all three values or none at all.
	//made an empty constructor in case I find some reason someone would
	//want to make an empty vector.

	Vector3(){}
	Vector3(float i, float j, float k);
	~Vector3() {}

	float length();

	Vector3 normalize();

	void showinfo(); //shows the vector's values.
	void setinfo();
	
	/*
	When I first started I made the operators call the methods
	but realized this would make things very messy considering
	all the operations possible on vectors.
	Will fix this later.
	*/
	float Dotproduct(Vector3 &vector2)
	{
		//method used to calculate inner product of two vectors
		float ans;
		ans = (itsx*vector2.itsx) + (itsy*vector2.itsy) + (itsz*vector2.itsz);
		return ans;
	}


	//operators
	float operator | (Vector3 &vector2);
	void operator +=(Vector3 &vector2);
	Vector3 operator + (Vector3 &vector2);
	void operator -= (Vector3 &vector2);
	Vector3 operator - (Vector3 &vector2);
	void operator *= (const float value);
	Vector3 operator * (const float value);
	/*
	there is not an operator that exists in c++
	That looks like x for the cross product, so I am using carrot.
	*/
	Vector3 operator ^(Vector3 &vector2);

	

private:
	float itsx;
	float itsy;
	float itsz;
};

//These are functions for calculating the relative motion between two points
	Vector3 velb(Vector3& ra, Vector3& rb, Vector3& vela, Vector3& velba, Vector3& angv);
	Vector3 accelb(Vector3& ra, Vector3& rb, Vector3& accela, Vector3& accelba, Vector3& velba, Vector3& angv,Vector3& angaccel);

	Vector3::Vector3(float i, float j, float k):
itsx(i), itsy(j), itsz(k)
{
	//cout << "Vector constructor.\n";
}

float Vector3::length()
{
	//returns scalar value of the vector's length

	float answer;
	answer = sqrt((pow(itsx,2) + pow(itsy,2) + pow(itsz, 2)));
	return answer;
}

Vector3 Vector3::normalize()
{
	/*
	same idea as +,-,and ^ operators. It will
	return a vector that is the unit vector of original.
	Could have made an operator, but I feel this is more clear and
	easier to work with.
	*/

	//intermediate length value
	float veclength = this->length();
	
	//Making intermediate values to make it more readable

	float i = itsx/veclength;
	float j = itsy/veclength;
	float k = itsz/veclength;

	return Vector3(i,j,k);
}

void Vector3::showinfo()
{
	cout << "\nx: " << itsx;
	cout << " y: " << itsy;
	cout << " z: " << itsz << endl;
}

void Vector3::setinfo()
{
	float x, y, z;
	cout << "Please input the x coordinate." << endl;
	cin >> x;
	cout << "Please input the y coordinate." << endl;
	cin >> y;
	cout << "Please input the z coordinate." << endl;
	cin >> z;
	cout << endl;

	itsx = x;
	itsy = y;
	itsz = z;
}

float Vector3::operator| (Vector3 &vector2)
{
	/*
	I selected this operator for dot product because
	it resembles the notation used for an inner product space.
	*/
	return Vector3::Dotproduct(vector2);
}
void  Vector3::operator+= (Vector3 & vector2)
{
	/*
	This is supposed to change the first vector in the 
	operator to be the sum of the two vectors
	*/
	itsx += vector2.itsx;
	itsy += vector2.itsy;
	itsz += vector2.itsz;
}

Vector3 Vector3::operator+ (Vector3 &vector2)
{
	/*
	returns a vector that holds the answer, so have to create a new vector
	and initialize with (vector1+vector2).
	*/

	return Vector3(itsx + vector2.itsx, itsy + vector2.itsy, itsz + vector2.itsz);
}
void Vector3::operator-= (Vector3 &vector2)
{
	//same idea as +=, but with subtraction

	itsx -= vector2.itsx;
	itsy -= vector2.itsy;
	itsz -= vector2.itsz;
}
Vector3 Vector3::operator - (Vector3 &vector2)
{
	//same idea as +, but with subtraction.

	return Vector3(itsx - vector2.itsx, itsy - vector2.itsy, itsz - vector2.itsz);
}


void Vector3::operator *= (const float value)
{
	/*
	This is element wise multiplication
	It will change the vector you are working with
	*/
	
	itsx *= value;
	itsy *= value;
	itsz *= value;
}
Vector3 Vector3::operator* (const float value)
{
	//element wise multiplication making a new vector
	return Vector3(value*itsx, value*itsy, value*itsz);
}
Vector3 Vector3::operator^ (Vector3 &vector2)
{
	/*
	This returns a vector that holds the cross product of
	two vectors. Like the + and - operators. you need
	to create a new vector object and initialize with the
	operation. 
	*/

	//to make it more readable I am making i,j,k values
	float i = (itsy*vector2.itsz - itsz*vector2.itsy);
	float j = - (itsx*vector2.itsz - itsz*vector2.itsx);
	float k = (itsx*vector2.itsy - itsy*vector2.itsx);
	return Vector3(i,j,k);
}
Vector3 velb(Vector3& ra, Vector3& rb, Vector3& vela, Vector3& velba, Vector3& angv)
{
	//find rba, which is position of object b relative to a.
	Vector3 rba(rb-ra);

	//vector that holds the cross product of angular velocity and rba.
	Vector3 angcrossrba(angv^rba);

	return Vector3(vela+angcrossrba+velba);


}
Vector3 accelb(Vector3& ra, Vector3& rb, Vector3& accela, Vector3& accelba, Vector3& velba, Vector3& angv,Vector3& angaccel)
{
	//relative position.
	Vector3 rba(rb-ra);

	Vector3 angaccelcrossrba(angaccel^rba);

	Vector3 angvcrossrba(angv^rba);

	Vector3 angvcrossagain(angv^angvcrossrba);

	Vector3 doubleangv(angv*2);

	Vector3 doubleangvcrossvelba(doubleangv^velba);

	return Vector3(accela+angaccelcrossrba+angvcrossagain+doubleangvcrossvelba+accelba);


}

#endif