#ifndef __LIGHTSOURCE_H
#define __LIGHTSOURCE_H

#include <list>

#include <Angel/Angel.h>

using namespace std;

class	LightSource
{
public:

	LightSource():v4Position(vec4(0,0,0,1)),v4Color(vec4(0,0,0,1)),v4Direction(vec4(0,0,0,0)),glfCutoffAngle(0){}
	LightSource(vec4 pos, vec4 color, vec4 direction,GLfloat angle) : v4Position(pos),v4Color(color),v4Direction(direction),glfCutoffAngle(angle) {}

	void	SetPosition(vec4 pos) {v4Position = pos;}
	vec4	GetPosition() const {return v4Position;}
	void	SetColor(vec4 color) {v4Color = color;}
	vec4	GetColor() const {return v4Color;}
	void	SetDirection(vec4 dir) {v4Direction = dir;}
	vec4	GetDirection() const {return v4Direction;}
	void	SetCutoffAngle(GLfloat angle)  {glfCutoffAngle = angle;}
	GLfloat GetCutoffAngle() const {return glfCutoffAngle;}
private:
	vec4	v4Position;
	vec4	v4Color;
	vec4	v4Direction;
	GLfloat	glfCutoffAngle;
};


class	LightSourceManager : private vector<LightSource *>
{
public:

	static  LightSourceManager* GetInstance() { if (!lightSourceManager) return  lightSourceManager = new LightSourceManager(); else return lightSourceManager;}

	void AddLightSource(LightSource *s) {push_back(s);}
	int	 GetNumberOfLights() const {return size();}

	~LightSourceManager() {if(lightSourceManager) delete lightSourceManager; lightSourceManager = 0; }

	LightSource*	GetLightNumber(unsigned int pos) { if (size() > pos) return at(pos); else return 0;}
private:

	static LightSourceManager *lightSourceManager;
};



#endif