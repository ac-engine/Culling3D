
#include "Culling3D.WorldInternal.h"
#include "Culling3D.ObjectInternal.h"

namespace Culling3D
{
	WorldInternal::WorldInternal(float xSize, float ySize, float zSize, int32_t layerCount)
	{
		this->xSize = xSize;
		this->ySize = ySize;
		this->zSize = zSize;

		this->gridSize = Max(Max(this->xSize, this->ySize), this->zSize);

		this->layerCount = layerCount;

		layers.resize(this->layerCount);

		for (size_t i = 0; layers.size(); i++)
		{
			float gridSize_ = this->gridSize / powf(2.0f, i);

			int32_t xCount = (int32_t) (this->xSize / gridSize_);
			int32_t yCount = (int32_t) (this->ySize / gridSize_);
			int32_t zCount = (int32_t) (this->zSize / gridSize_);

			if (xCount * gridSize_ < this->xSize) xCount++;
			if (yCount * gridSize_ < this->ySize) yCount++;
			if (zCount * gridSize_ < this->zSize) zCount++;

			layers[i] = new Layer(xCount, yCount, zCount, xSize / 2.0f, ySize / 2.0f, zSize / 2.0f, gridSize_);
		}
	}

	WorldInternal::~WorldInternal()
	{
		for (size_t i = 0; layers.size(); i++)
		{
			delete layers[i];
		}

		layers.clear();
	}

	void WorldInternal::AddObject(Object* o)
	{
		assert(o != NULL);

		ObjectInternal* o_ = (ObjectInternal*) o;

		int32_t gridInd = (int32_t)((o_->GetNextStatus().Radius * 2.0f) / gridSize);

		if (gridInd * gridSize < (o_->GetNextStatus().Radius * 2.0f)) gridInd++;

		int32_t ind = 0;
		bool found = false;
		for (size_t i = 0; i < layers.size(); i++)
		{
			if (ind <= gridInd && gridInd < ind * 2)
			{
				if (layers[i]->AddObject(o))
				{
					((ObjectInternal*) o)->SetWorld(this);
					found = true;
				}
				else
				{
					break;
				}
			}
		}

		if (!found)
		{
			((ObjectInternal*) o)->SetWorld(this);
			outofLayers.AddObject(o);
		}
	}

	void WorldInternal::RemoveObject(Object* o)
	{
		assert(o != NULL);

		ObjectInternal* o_ = (ObjectInternal*) o;

		int32_t gridInd = (int32_t) ((o_->GetCurrentStatus().Radius * 2.0f) / gridSize);

		if (gridInd * gridSize < (o_->GetCurrentStatus().Radius * 2.0f)) gridInd++;

		int32_t ind = 0;
		bool found = false;
		for (size_t i = 0; i < layers.size(); i++)
		{
			if (ind <= gridInd && gridInd < ind * 2)
			{
				if (layers[i]->RemoveObject(o))
				{
					((ObjectInternal*) o)->SetWorld(NULL);
					found = true;
				}
				else
				{
					break;
				}
			}
		}

		if (!found)
		{
			((ObjectInternal*) o)->SetWorld(NULL);
			outofLayers.RemoveObject(o);
		}
	}

	void WorldInternal::Culling(const Matrix44& cameraProjMat, bool isOpenGL)
	{
		objs.clear();

		Vector3DF eyebox[8];
		eyebox[0 + 0] = Vector3DF(-1.0f, -1.0f, +1.0f);
		eyebox[1 + 0] = Vector3DF(+1.0f, -1.0f, +1.0f);
		eyebox[2 + 0] = Vector3DF(-1.0f, +1.0f, +1.0f);
		eyebox[3 + 0] = Vector3DF(+1.0f, +1.0f, +1.0f);

		float far = 0.0f;
		if (isOpenGL) far = -1.0f;

		eyebox[0 + 4] = Vector3DF(-1.0f, -1.0f, far);
		eyebox[1 + 4] = Vector3DF(+1.0f, -1.0f, far);
		eyebox[2 + 4] = Vector3DF(-1.0f, +1.0f, far);
		eyebox[3 + 4] = Vector3DF(+1.0f, +1.0f, far);

		Matrix44 cameraProjMatInv = cameraProjMat;
		cameraProjMatInv.SetInverted();

		for (int32_t i = 0; i < 8; i++)
		{
			eyebox[i] = cameraProjMatInv.Transform3D(eyebox[i]);
		}

		Vector3DF max_(FLT_MIN, FLT_MIN, FLT_MIN);
		Vector3DF min_(FLT_MAX, FLT_MAX, FLT_MAX);

		for (int32_t i = 0; i < 8; i++)
		{
			if (eyebox[i].X > max_.X) max_.X = eyebox[i].X;
			if (eyebox[i].Y > max_.Y) max_.Y = eyebox[i].Y;
			if (eyebox[i].Z > max_.Z) max_.Z = eyebox[i].Z;

			if (eyebox[i].X < min_.X) min_.X = eyebox[i].X;
			if (eyebox[i].Y < min_.Y) min_.Y = eyebox[i].Y;
			if (eyebox[i].Z < min_.Z) min_.Z = eyebox[i].Z;
		}

		/* 範囲内に含まれるグリッドを取得 */
		for (size_t i = 0; i < layers.size(); i++)
		{
			layers[i]->AddGrids(max_, min_, grids);
		}

		grids.push_back(&outofLayers);
		

		/* グリッドからオブジェクト取得 */
		for (size_t i = 0; i < grids.size(); i++)
		{
			for (size_t j = 0; j < grids[i]->GetObjects().size(); j++)
			{
				Object* o = grids[i]->GetObjects()[j];
				objs.push_back(o);
			}
		}

		/* 取得したグリッドを破棄 */
		for (size_t i = 0; i < grids.size(); i++)
		{
			grids[i]->IsScanned = false;
		}
	}
}