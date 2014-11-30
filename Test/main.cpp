
#include <Culling3D.h>
#include <vector>

#if _DEBUG
#pragma comment(lib,"Debug/Culling3D.lib")
#else
#pragma comment(lib,"Release/Culling3D.lib")
#endif

int main()
{
	Culling3D::World* world = Culling3D::World::Create(100, 20, 100, 4);

	std::vector<Culling3D::Object*> objs;

	for (auto i = 0; i < 100; i++)
	{
		Culling3D::Object* o = Culling3D::Object::Create();

		world->AddObject(o);
		o->SetPosition(Culling3D::Vector3DF(1, 1, -40));
		o->SetRadius(50.0f);
		objs.push_back(o);
	}

	Culling3D::Matrix44 cameraMat, projMat;

	cameraMat.SetLookAtRH(Culling3D::Vector3DF(50, 0, 50), Culling3D::Vector3DF(0, 0, 0), Culling3D::Vector3DF(0, 1, 0));
	projMat.SetPerspectiveFovRH(10.0f / 180.0f * 3.14f, 4.0f / 3.0f, 1.0f, 100.0f);

	Culling3D::Matrix44 mat = projMat * cameraMat;

	world->Culling(mat, false);

	for (auto i = 0; i < objs.size(); i++)
	{
		objs[i]->Release();
	}
	objs.clear();

	Culling3D::SafeRelease(world);

	return 0;
}