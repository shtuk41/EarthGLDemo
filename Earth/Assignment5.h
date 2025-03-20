#ifndef __ASSIGNMENT_4_H
#define __ASSIGNMENT_4_H

#include "GraphObjects.h"
#include "Camera.h"
#include "Devices.h"



class	Scene
{
public:
	enum	CAMERA {STATIC=0,VIEWPOINT,CHASE};

	Scene(): glfXRot(0.0),glfYRot(0.0),glfZRot(0.0) {}




	void Init();
	//against OP, but seems like true according to Stroustrup
	void Draw(GraphObject *object);
	void SetMv(mat4 *m) { if (!m) return; else mv = *m;};
	void SetP(mat4 *p) { if (!p) return; else this->p = *p;};
	mat4 GetMv() const {return mv;}
	mat4 GetP() const {return p;}
	void SetWindowSize(GLfloat w, GLfloat h) {fWindowWidth = w; fWindowHeight = h;}
	GLfloat	GetWindowHeight() const {return fWindowHeight;}
	GLfloat	GetWindowWidth() const {return fWindowWidth;}
	CAMERA	GetCamera() const {return eCamera;}
	void	SetCameraStatic() {pCameraCurrent = &cCameraStatic;eCamera=STATIC;}
	void	SetCameraViewpoint() {pCameraCurrent = &cCameraViewpoint;eCamera=VIEWPOINT;}
	void	SetCameraChase() {pCameraCurrent = &cCameraChase;eCamera=CHASE;}
	Camera *	GetCurrentCamera() { return pCameraCurrent;}
	CameraStatic *GetStaticCamera() {return &cCameraStatic;}
	void		SetXRot(GLfloat x) {glfXRot = x;}
	GLfloat		GetXRot() const {return glfXRot;}
	void		SetYRot(GLfloat y) {glfYRot = y;}
	GLfloat		GetYRot() const {return glfYRot;}
	void		SetZRot(GLfloat z) {glfZRot = z;}
	GLfloat		GetZRot() const {return glfZRot;}
	void		UpdateXRot(GLfloat x) {glfXRot += x; glfXRot = Utility::Lim360(glfXRot);}
	void		UpdateYRot(GLfloat y) {glfYRot += y; glfYRot = Utility::Lim360(glfYRot);}
	void		UpdateZRot(GLfloat z) {glfZRot += z; glfZRot = Utility::Lim360(glfZRot);}


	static Scene * SceneInstance() { if (scene) return scene; else return scene = new Scene();}
protected:


private:
		static Scene *scene;

	mat4 mv;
	mat4 p;

	CAMERA	eCamera;
	GLfloat	fFovy;

	GLfloat fWindowWidth;
	GLfloat fWindowHeight;

	CameraStatic	cCameraStatic;
	Camera			cCameraViewpoint;
	Camera			cCameraChase;

	Camera	*pCameraCurrent;

	GLfloat		glfXRot;
	GLfloat		glfYRot;
	GLfloat		glfZRot;
};

class	Assignment5 : public Scene
{
public:
	Assignment5(GLfloat minx, GLfloat maxx, GLfloat minz, GLfloat maxz) : earth(10), clouds(10.2) { Init();}
	static Assignment5* Instance() { if (assignment5) return assignment5; else return assignment5 =  new Assignment5(-50,50,-50,50);}
	static void Create() {  Instance();}
	Earth * EarthInstance()  {return &earth;}
	Clouds * CloudsInstance() {return &clouds;}
	Mouse * MouseInstance() {return &mouse;}
	LightSource * SunInstance() {return &sun;}
	void	DrawObjects();

	~Assignment5() { if (assignment5) delete assignment5;  assignment5 = 0;}
private:
	void	Init();

	static Assignment5 *assignment5;

	LightSource	sun;
	Earth earth;
	Clouds clouds;
	Mouse	mouse;
};
#endif