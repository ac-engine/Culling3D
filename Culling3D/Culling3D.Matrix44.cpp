
#include "Culling3D.h"

namespace Culling3D
{
	Matrix44::Matrix44()
	{
		for (int32_t c = 0; c < 4; c++)
		{
			for (int32_t r = 0; r < 4; r++)
			{
				Values[c][r] = 0.0f;
			}
		}

		for (int32_t i = 0; i < 4; i++)
		{
			Values[i][i] = 1.0f;
		}
	}

	Matrix44& Matrix44::SetInverted()
	{
		float a11 = this->Values[0][0];
		float a12 = this->Values[0][1];
		float a13 = this->Values[0][2];
		float a14 = this->Values[0][3];
		float a21 = this->Values[1][0];
		float a22 = this->Values[1][1];
		float a23 = this->Values[1][2];
		float a24 = this->Values[1][3];
		float a31 = this->Values[2][0];
		float a32 = this->Values[2][1];
		float a33 = this->Values[2][2];
		float a34 = this->Values[2][3];
		float a41 = this->Values[3][0];
		float a42 = this->Values[3][1];
		float a43 = this->Values[3][2];
		float a44 = this->Values[3][3];

		/* s—ñ®‚ÌŒvZ */
		float b11 = +a22 * (a33 * a44 - a43 * a34) - a23 * (a32 * a44 - a42 * a34) + a24 * (a32 * a43 - a42 * a33);
		float b12 = -a12 * (a33 * a44 - a43 * a34) + a13 * (a32 * a44 - a42 * a34) - a14 * (a32 * a43 - a42 * a33);
		float b13 = +a12 * (a23 * a44 - a43 * a24) - a13 * (a22 * a44 - a42 * a24) + a14 * (a22 * a43 - a42 * a23);
		float b14 = -a12 * (a23 * a34 - a33 * a24) + a13 * (a22 * a34 - a32 * a24) - a14 * (a22 * a33 - a32 * a23);

		float b21 = -a21 * (a33 * a44 - a43 * a34) + a23 * (a31 * a44 - a41 * a34) - a24 * (a31 * a43 - a41 * a33);
		float b22 = +a11 * (a33 * a44 - a43 * a34) - a13 * (a31 * a44 - a41 * a34) + a14 * (a31 * a43 - a41 * a33);
		float b23 = -a11 * (a23 * a44 - a43 * a24) + a13 * (a21 * a44 - a41 * a24) - a14 * (a21 * a43 - a41 * a23);
		float b24 = +a11 * (a23 * a34 - a33 * a24) - a13 * (a21 * a34 - a31 * a24) + a14 * (a21 * a33 - a31 * a23);

		float b31 = +a21 * (a32 * a44 - a42 * a34) - a22 * (a31 * a44 - a41 * a34) + a24 * (a31 * a42 - a41 * a32);
		float b32 = -a11 * (a32 * a44 - a42 * a34) + a12 * (a31 * a44 - a41 * a34) - a14 * (a31 * a42 - a41 * a32);
		float b33 = +a11 * (a22 * a44 - a42 * a24) - a12 * (a21 * a44 - a41 * a24) + a14 * (a21 * a42 - a41 * a22);
		float b34 = -a11 * (a22 * a34 - a32 * a24) + a12 * (a21 * a34 - a31 * a24) - a14 * (a21 * a32 - a31 * a22);

		float b41 = -a21 * (a32 * a43 - a42 * a33) + a22 * (a31 * a43 - a41 * a33) - a23 * (a31 * a42 - a41 * a32);
		float b42 = +a11 * (a32 * a43 - a42 * a33) - a12 * (a31 * a43 - a41 * a33) + a13 * (a31 * a42 - a41 * a32);
		float b43 = -a11 * (a22 * a43 - a42 * a23) + a12 * (a21 * a43 - a41 * a23) - a13 * (a21 * a42 - a41 * a22);
		float b44 = +a11 * (a22 * a33 - a32 * a23) - a12 * (a21 * a33 - a31 * a23) + a13 * (a21 * a32 - a31 * a22);

		// s—ñ®‚Ì‹t”‚ğ‚©‚¯‚é
		float Det = (a11 * b11) + (a12 * b21) + (a13 * b31) + (a14 * b41);
		if ((-FLT_MIN <= Det) && (Det <= +FLT_MIN))
		{
			return *this;
		}

		float InvDet = 1.0f / Det;

		Values[0][0] = b11 * InvDet;
		Values[0][1] = b12 * InvDet;
		Values[0][2] = b13 * InvDet;
		Values[0][3] = b14 * InvDet;
		Values[1][0] = b21 * InvDet;
		Values[1][1] = b22 * InvDet;
		Values[1][2] = b23 * InvDet;
		Values[1][3] = b24 * InvDet;
		Values[2][0] = b31 * InvDet;
		Values[2][1] = b32 * InvDet;
		Values[2][2] = b33 * InvDet;
		Values[2][3] = b34 * InvDet;
		Values[3][0] = b41 * InvDet;
		Values[3][1] = b42 * InvDet;
		Values[3][2] = b43 * InvDet;
		Values[3][3] = b44 * InvDet;

		return *this;
	}

	Vector3DF Matrix44::Transform3D(const Vector3DF& in) const
	{
		float values[4];

		for (int i = 0; i < 4; i++)
		{
			values[i] = 0;
			values[i] += in.X * Values[i][0];
			values[i] += in.Y * Values[i][1];
			values[i] += in.Z * Values[i][2];
			values[i] += Values[i][3];
		}

		Vector3DF o;
		o.X = values[0] / values[3];
		o.Y = values[1] / values[3];
		o.Z = values[2] / values[3];
		return o;
	}

}