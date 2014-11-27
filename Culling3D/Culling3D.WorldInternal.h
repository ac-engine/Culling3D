
#pragma once

#include "Culling3D.h"
#include "Culling3D.Layer.h"
#include "Culling3D.Grid.h"

namespace Culling3D
{
	class WorldInternal
		: public World
	{
	private:
		float xSize;
		float ySize;
		float zSize;

		float	gridSize;
		int32_t	layerCount;

		std::vector<Layer*>	layers;

		Grid	outofLayers;

		std::vector<Object*> objs;

		std::vector<Grid*> grids;

	public:
		WorldInternal(float xSize, float ySize, float zSize, int32_t layerCount);
		virtual ~WorldInternal();

		void AddObject(Object* o);
		void RemoveObject(Object* o);

		void Culling(const Matrix44& cameraProjMat, bool isOpenGL);
		int32_t GetObjectCount() { return objs.size(); }
		Object* GetObject(int32_t index) { return objs[index]; }
	};
}