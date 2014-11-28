
#pragma once

#include "Culling3D.h"
#include "Culling3D.ReferenceObject.h"

namespace Culling3D
{
	class ObjectInternal
		: public Object
		, public ReferenceObject
	{
	public:
		struct Status
		{
			Vector3DF	Position;
			float		Radius;
		};

	private:
		void*		userData;
		Vector3DF	position;
		World*		world;

		Status	currentStatus;
		Status	nextStatus;

	public:
		ObjectInternal();

		Vector3DF GetPosition();
		void SetPosition(Vector3DF pos);

		void SetRadius(float radius);

		void* GetUserData();
		void SetUserData(void* userData);

		void SetWorld(World* world);

		Status	GetCurrentStatus() { return currentStatus; }
		Status	GetNextStatus() { return nextStatus; }

		int32_t ObjectIndex;

		virtual int32_t GetRef() { return ReferenceObject::GetRef(); }
		virtual int32_t AddRef() { return ReferenceObject::AddRef(); }
		virtual int32_t Release() { return ReferenceObject::Release(); }
	};
}