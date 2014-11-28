
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

	o0->SetPosition(Culling3D::Vector3DF(1, 1, 50));
	
	o0->SetRadius(10.0f);



	Culling3D::SafeRelease(o0);

	Culling3D::SafeRelease(world);

	return 0;
}