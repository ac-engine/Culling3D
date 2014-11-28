
#include "Culling3D.h"

namespace Culling3D
{
	Vector3DF::Vector3DF()
		: X(0)
		, Y(0)
		, Z(0)
	{
	}

	Vector3DF::Vector3DF(float x, float y, float z)
		: X(x)
		, Y(y)
		, Z(z)
	{
	}

	bool Vector3DF::operator == (const Vector3DF& o)
	{
		return X == o.X && Y == o.Y && Z == o.Z;
	}

	bool Vector3DF::operator != (const Vector3DF& o)
	{
		return !(X == o.X && Y == o.Y && Z == o.Z);
	}

	Vector3DF Vector3DF::operator-()
	{
		return Vector3DF(-X, -Y, -Z);
	}

	Vector3DF Vector3DF::operator + (const Vector3DF& o) const
	{
		return Vector3DF(X + o.X, Y + o.Y, Z + o.Z);
	}

	Vector3DF Vector3DF::operator - (const Vector3DF& o) const
	{
		return Vector3DF(X - o.X, Y - o.Y, Z - o.Z);
	}

	Vector3DF Vector3DF::operator * (const Vector3DF& o) const
	{
		return Vector3DF(X * o.X, Y * o.Y, Z * o.Z);
	}

	Vector3DF Vector3DF::operator / (const Vector3DF& o) const
	{
		return Vector3DF(X / o.X, Y / o.Y, Z / o.Z);
	}

	Vector3DF Vector3DF::operator * (const float& o) const
	{
		return Vector3DF(X * o, Y * o, Z * o);
	}

	Vector3DF Vector3DF::operator / (const float& o) const
	{
		return Vector3DF(X / o, Y / o, Z / o);
	}

	Vector3DF& Vector3DF::operator += (const Vector3DF& o)
	{
		X += o.X;
		Y += o.Y;
		Z += o.Z;
		return *this;
	}

	Vector3DF& Vector3DF::operator -= (const Vector3DF& o)
	{
		X -= o.X;
		Y -= o.Y;
		Z -= o.Z;
		return *this;
	}

	Vector3DF& Vector3DF::operator *= (const float& o)
	{
		X *= o;
		Y *= o;
		Z *= o;
		return *this;
	}

	Vector3DF& Vector3DF::operator /= (const float& o)
	{
		X /= o;
		Y /= o;
		Z /= o;
		return *this;
	}
}