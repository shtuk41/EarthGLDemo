#ifndef __GRAPH_OBJECTS
#define __GRAPH_OBJECTS

#include <Angel/Angel.h>
#include <vector>
#include "utility.h"
#include "Lightsource.h"

using namespace std;

struct LightStruct
{
	GLuint position;	
	GLuint color;		
	GLuint direction;	
	GLuint cutoffangle;
};

class	GraphObject
{
public:
	enum	EMAP { SURFACE = 0, SPEC, NIGHT, CLOUDS, FINAL, NORMAL,NONE};


	GraphObject() { 
	tx=
	ty=
	tz=
	rx=
	ry=
	rz= 0.0;

	}

	virtual void Init() = 0;
	virtual void Draw() = 0;

	void SetMv(mat4 mat) {mv = mat;}
	mat4 GetMv() const {return mv;}

	void SetP(mat4 mat) {p = mat;}
	mat4 GetP() const {return p;}

	void SetTx(GLfloat val) {tx = val;}
	GLfloat GetTx() const {return tx;}

	void SetTy(GLfloat val) {ty = val;}
	GLfloat GetTy() const {return ty;}

	void SetTz(GLfloat val) {tz = val;}
	GLfloat GetTz() const {return tz;}

	void SetRx(GLfloat val) {rx = val;}
	GLfloat GetRx() const {return tx;}

	void SetRy(GLfloat val) {ry = val;}
	GLfloat GetRy() const {return ty;}

	void SetRz(GLfloat val) {rz = val;}
	GLfloat GetRz() const {return tz;}

	vec4	GetSpecularColor() const {return vec4(1.0,1.0,1.0,1.0);}
	GLfloat	GetSpecularExponent() const {return 100;}

	static	void SetMapMode(GLuint in) {gluiMapMode = in;}
	static  GLuint GetMapMode() {return gluiMapMode;}
	static	void	SetMap(EMAP e) {eMap = e;}
	static	EMAP	GetMap() {return eMap;}


	
protected:
	mat4	mv,p;

	GLfloat		tx;
	GLfloat		ty;
	GLfloat		tz;

	GLfloat		rx;
	GLfloat		ry;
	GLfloat		rz;

	GLuint vao[2];
	GLuint vbo[7];

	GLuint vPosition;
	GLuint vAmbientDiffuseColor;
	GLuint vNormal;
	GLuint vTexture;
	GLuint vTangent;
	
	GLuint vSpecularColor;
	GLuint vSpecularExponent;
	GLuint model_view;
	GLuint projection;

	GLuint program;

	LightStruct		lightSun;

	static GLuint		gluiMapMode;
	static EMAP			eMap;


};

class Earth : public GraphObject
{
public:

	Earth(GLfloat r) : glfRadius(r) {}
	void Init();
	void Draw();
	void Rotate(double);
	GLfloat	GetRotAngle() const {return glfRotAngle;}

private:
	double	ConvJ(double);

	vec4 v4Vertices[4800];
	vec4	v4AmbientDiffuseColor[4800];
	vec3	v3Normal[4800];
	vec2	v2Texture[4800];
	vec4	v4Tangent[4800];

	GLfloat		glfRadius;

	GLfloat		glfRotAngle;

	GLuint		gluiTexName[4];
	GLuint		gluiTexMap[4];




};

class Clouds : public GraphObject
{
public:
public:
	Clouds(GLfloat r) : glfRadius(r) {}
	void Init();
	void Draw();
	void Rotate(double);
	GLfloat	GetRotAngle() const {return glfRotAngle;}
private:
	double	ConvJ(double);

	vec4 v4Vertices[4800];
	vec4	v4AmbientDiffuseColor[4800];
	vec3	v3Normal[4800];
	vec2	v2Texture[4800];

	GLfloat		glfRadius;
	GLfloat		glfSubdiv;

	GLfloat		glfRotAngle;

	GLuint		gluiTexName;
	GLuint		gluiTexMap;

};





#endif