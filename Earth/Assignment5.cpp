#include "Assignment5.h"
#include "Lightsource.h"


Scene *Scene::scene = 0;
Assignment5 * Assignment5::assignment5 = 0;
LightSourceManager * LightSourceManager::lightSourceManager = 0;
GLuint GraphObject::gluiMapMode = 0;
GraphObject::EMAP GraphObject::eMap = GraphObject::SURFACE;

//****************************************************************
//	Date:		03/10/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Scene
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	Initialize Scene, Cameras, Set Current Camera
//******************************************************************
void Scene::Init()
{
	eCamera = STATIC;
	cCameraStatic.Reset();
	cCameraStatic.Init(vec4(0,0,20.0,1.0),vec4(0.0,0.0,0.0,1.0),vec4(0.0,1.0,0.0,0.0),60.0,fWindowWidth/fWindowHeight,1.0,105.0);
	cCameraChase.Init(vec4(20,10,0,1.0),vec4(0,10,0.0,1.0),vec4(0.0,1.0,0.0,0.0),60.0,fWindowWidth/fWindowHeight,1.0,105.0);
	cCameraViewpoint.Init(vec4(1,6,0,1.0),vec4(-10.0,6.0,0.0,1.0),vec4(0.0,10.0,0.0,0.0),60.0,fWindowWidth/fWindowHeight,1.0,105.0);


	pCameraCurrent = &cCameraStatic;

}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Scene
//	Function:	Draw
//	Inputs:		none
//	Output:		none
//	Purpose:	Draw Scene	
//******************************************************************
void	Scene::Draw(GraphObject *object)
{
 	mv = pCameraCurrent ? pCameraCurrent->GetMv()  * RotateX(glfXRot) * RotateY(glfYRot): mat4();
	p  = pCameraCurrent ? pCameraCurrent->GetP() : mat4();

	if (object)
	{
		object->SetMv(mv);
		object->SetP(p);
		object->Draw();
	}
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment5
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	Initialize class members
//******************************************************************
void	Assignment5::Init()
{
	Assignment5::SceneInstance()->Init();
	
	clouds.Init();
	earth.Init();
			

	sun.SetPosition(vec4(-100,0,0,1));
	sun.SetColor(vec4(1.0,1.0,1.0,1.0));
	sun.SetDirection(vec4(1,0,0,0));
	sun.SetCutoffAngle(180.0);

	LightSourceManager::GetInstance()->AddLightSource(&sun);
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment5
//	Function:	DrawObjects
//	Inputs:		none
//	Output:		none
//	Purpose:	Draw Field and Car
//******************************************************************
void	Assignment5::DrawObjects()
{
	if (EarthInstance()->GetMap() != Earth::CLOUDS)
		SceneInstance()->Draw(&earth);
	
	if (EarthInstance()->GetMap() == Earth::CLOUDS || EarthInstance()->GetMap() == Earth::FINAL)
		SceneInstance()->Draw(&clouds);

}
