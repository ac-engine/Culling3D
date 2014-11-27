
#pragma once

#include <stdio.h>
#include <assert.h>
#include <float.h>

#ifdef _WIN32
typedef signed char			int8_t;
typedef unsigned char		uint8_t;
typedef short				int16_t;
typedef unsigned short		uint16_t;
typedef int					int32_t;
typedef unsigned int		uint32_t;
typedef __int64				int64_t;
typedef unsigned __int64	uint64_t;
#else
#include <stdint.h>
#endif

namespace Culling3D
{
	/**
	@brief	最大値取得
	*/
	template <typename T, typename U>
	T Max(T t, U u)
	{
		if (t > (T) u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	最小値取得
	*/
	template <typename T, typename U>
	T Min(T t, U u)
	{
		if (t < (T) u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	範囲内値取得
	*/
	template <typename T, typename U, typename V>
	T Clamp(T t, U max_, V min_)
	{
		if (t > (T) max_)
		{
			t = (T) max_;
		}

		if (t < (T) min_)
		{
			t = (T) min_;
		}

		return t;
	}

	class World;
	class Object;

	struct Vector3DF
	{
		float	X;
		float	Y;
		float	Z;

		Vector3DF();
		Vector3DF(float x, float y, float z);
	};
	
	struct Matrix44
	{
		float	Values[4][4];

		Matrix44();
		Matrix44& SetInverted();
		Vector3DF Transform3D(const Vector3DF& in) const;
	};

	class IReference
	{
	public:
		/**
		@brief	参照カウンタを加算する。
		@return	加算後の参照カウンタ
		*/
		virtual int AddRef() = 0;

		/**
		@brief	参照カウンタを取得する。
		@return	参照カウンタ
		*/
		virtual int GetRef() = 0;

		/**
		@brief	参照カウンタを減算する。0になった時、インスタンスを削除する。
		@return	減算後の参照カウンタ
		*/
		virtual int Release() = 0;
	};

	class World
	{
	public:
		virtual void AddObject(Object* o) = 0;
		virtual void RemoveObject(Object* o) = 0;

		virtual void Culling(const Matrix44& cameraProjMat, bool isOpenGL) = 0;
		virtual int32_t GetObjectCount() = 0;
		virtual Object* GetObject(int32_t index) = 0;
	};

	class Object
	{
	public:
		virtual Vector3DF GetPosition() = 0;
		virtual void SetPosition(Vector3DF pos) = 0;
		virtual void SetRadius(float radius) = 0;

		virtual void* GetUserData() = 0;
		virtual void SetUserData(void* data) = 0;
	};
}