
#include <Culling3D.h>

#if _DEBUG
#pragma comment(lib,"Debug/Culling3D.lib")
#else
#pragma comment(lib,"Release/Culling3D.lib")
#endif

int main()
{
	Culling3D::World* world = Culling3D::World::Create(100, 100, 100, 4);

	Culling3D::Object* o0 = Culling3D::Object::Create();

	world->AddObject(o0);

	o0->SetPosition(Culling3D::Vector3DF(1, 1, -40));
	
	o0->SetRadius(10.0f);

	Culling3D::Matrix44 cameraMat, projMat;

	cameraMat.SetLookAtRH(Culling3D::Vector3DF(0, 0, 1), Culling3D::Vector3DF(0, 0, 0), Culling3D::Vector3DF(0, 1, 0));
	projMat.SetPerspectiveFovRH(20.0f / 180.0f * 3.14f, 4.0f / 3.0f, 1.0f, 100.0f);

	Culling3D::Matrix44 mat = projMat * cameraMat;

	world->Culling(mat, false);

	Culling3D::SafeRelease(o0);

	Culling3D::SafeRelease(world);

	return 0;
}