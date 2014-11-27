
#pragma once

#include "Culling3D.h"

namespace Culling3D
{
	class ObjectInternal
		: public Object
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
	};
}