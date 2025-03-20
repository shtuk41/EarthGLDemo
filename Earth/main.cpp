
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Angel/Angel.h>


#include "Assignment5.h"




#pragma comment(lib, "glew32.lib")

#pragma comment(lib,"ILUT.lib")
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ILU.lib")



void init();
void myDisplay();
void myIdle();
void myReshape(int width, int height);
void myMouseEvent(int,int,int,int);
void myMouseMotion(int, int);
void myMousePassiveMotion(int,int);
void myMouseEntryEvent(int);
void myKeyboard(unsigned char,int,int);
void mySpecial(int,int,int);

//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	main
//	Inputs:		none
//	Output:		none
//	Purpose:	main function
//******************************************************************
int main(int argc, char** argv)
{
	//init
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1200,700);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Assignment5 Aleksander Shtuk");
	glewInit();
	init();

	//display
	glutDisplayFunc(myDisplay);

	//idle
	glutIdleFunc(myIdle);

	//input
	glutMouseFunc(myMouseEvent);
	glutMotionFunc(myMouseMotion);
	glutPassiveMotionFunc(myMousePassiveMotion);
	glutEntryFunc(myMouseEntryEvent);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecial);

	//reshape
	glutReshapeFunc(myReshape);	

	glutMainLoop();

	return 0;
}


//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	all objects must be initilialized here
//******************************************************************
void init()
{
	//testing

	Assignment5::Create();

	glClearColor(0.0,0.0,0.0,1.0);

	glMatrixMode(GL_PROJECTION);

	glEnable(GL_DEPTH_TEST);

}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myDisplay
//	Inputs:		none
//	Output:		none
//	Purpose:	Callback that handles display
//******************************************************************


void myDisplay()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Assignment5::Instance()->DrawObjects();
	

	glFlush();
	glutSwapBuffers();
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myIdle
//	Inputs:		none
//	Output:		none
//	Purpose:	check if car is inside field boundaries
//******************************************************************
void myIdle()
{

	Assignment5::Instance()->EarthInstance()->Rotate(0.05);
	Assignment5::Instance()->CloudsInstance()->Rotate(0.03);

	Assignment5::Instance()->SceneInstance()->GetStaticCamera()->SetFocus(CameraStatic::CENTER);	
	Assignment5::Instance()->SceneInstance()->GetStaticCamera()->SetAt(vec4(0.0,0.0,0.0,1.0));
	
	glutPostRedisplay();
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myReshape
//	Inputs:		none
//	Output:		none
//	Purpose:	Callback that handles window reshaping			
//******************************************************************

void myReshape(int width, int height)
{
	Assignment5::Instance()->SceneInstance()->SetWindowSize(GLfloat(width),GLfloat(height));
	Assignment5::Instance()->SceneInstance()->GetCurrentCamera()->SetAspect(GLfloat(width)/GLfloat(height));

	static bool ii = true;

	if (ii)
	{
		Assignment5::Instance()->SceneInstance()->Init();
		ii = false;
	}


	glViewport(0,0,width,height);
	glutPostRedisplay();
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myReshape
//	Inputs:		none
//	Output:		none
//	Purpose:	Callback that handles processing special keys	
//				Left, Right - turn car
//				Up, Down - move forward, backward
//******************************************************************
void mySpecial(int key,int x,int z)
{
	

}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myKeyboard
//	Inputs:		none
//	Output:		none
//	Purpose:	keyboard handling
//				x,z - rotate head
//				1-9 - set speed
//******************************************************************
void myKeyboard(unsigned char key,int x,int y)
{
	static double Ry = 0.0;

	static double Rx = 0.0;

	

	if (key == 'a')
	{
		Assignment5::Instance()->SceneInstance()->GetStaticCamera()->ZoomInLens();
	}
	else if (key == 's')
	{
		Assignment5::Instance()->SceneInstance()->GetStaticCamera()->ZoomOutLens();
	}
	else if (key == 'v' && Assignment5::Instance()->EarthInstance()->GetMap() == GraphObject::FINAL)
	{
		Assignment5::Instance()->EarthInstance()->SetMap(GraphObject::SURFACE);	
	}
	else if (key == 'v' && Assignment5::Instance()->EarthInstance()->GetMap() == GraphObject::SURFACE)
	{
		Assignment5::Instance()->EarthInstance()->SetMap(GraphObject::SPEC);
	}
	else if (key == 'v' && Assignment5::Instance()->EarthInstance()->GetMap() == GraphObject::SPEC)
	{
		Assignment5::Instance()->EarthInstance()->SetMap(GraphObject::NIGHT);	
	}
	else if (key == 'v' && Assignment5::Instance()->EarthInstance()->GetMap() == GraphObject::NIGHT)
	{
		Assignment5::Instance()->EarthInstance()->SetMap(GraphObject::CLOUDS);	
	}
	else if (key == 'v' && Assignment5::Instance()->EarthInstance()->GetMap() == GraphObject::CLOUDS)
	{
		Assignment5::Instance()->EarthInstance()->SetMap(GraphObject::NORMAL);	
	}
	else if (key == 'v' && Assignment5::Instance()->EarthInstance()->GetMap() == GraphObject::NORMAL)
	{
		Assignment5::Instance()->EarthInstance()->SetMap(GraphObject::FINAL);	
	}
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMouseEntryEvent
//	Inputs:		none
//	Output:		none
//******************************************************************
void myMouseEntryEvent(int)
{
	
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMousePassiveMotion
//	Inputs:		none
//	Output:		none
//******************************************************************
void myMousePassiveMotion(int,int)
{

}
//****************************************************************
//	Date:		04/29/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMouseMotion
//	Inputs:		none
//	Output:		none
//	Note:		THis is taken from Dr.Gossett example in class with a little abstraction
//******************************************************************
void myMouseMotion(int xPos,int yPos)
{
	if (Assignment5::Instance()->MouseInstance()->IsLeftButtonDown())
	{
		Assignment5::Instance()->SceneInstance()->UpdateYRot(360.0  *  ((xPos - Assignment5::Instance()->MouseInstance()->GetXPosition()) / Assignment5::Instance()->SceneInstance()->GetWindowWidth()));
		Assignment5::Instance()->SceneInstance()->UpdateXRot(360.0  * ((yPos - Assignment5::Instance()->MouseInstance()->GetYPosition() ) / Assignment5::Instance()->SceneInstance()->GetWindowHeight()));
	
		Assignment5::Instance()->SunInstance()->SetPosition(mat4(1.0) * RotateX(Assignment5::Instance()->SceneInstance()->GetXRot()) * RotateY(Assignment5::Instance()->SceneInstance()->GetYRot()) * vec4(-100.0,0.0,0.0,1.0));
		Assignment5::Instance()->SunInstance()->SetDirection(vec4(0.0,0.0,0.0,1.0) - Assignment5::Instance()->SunInstance()->GetPosition());
	
	}
	else if (Assignment5::Instance()->MouseInstance()->IsRightButtonDown())
	{
		if (yPos > Assignment5::Instance()->MouseInstance()->GetYPosition())
			Assignment5::Instance()->SceneInstance()->GetStaticCamera()->ZoomInLens();
		else
			Assignment5::Instance()->SceneInstance()->GetStaticCamera()->ZoomOutLens();
	}

	Assignment5::Instance()->MouseInstance()->UpdatePosition(xPos,yPos);

	glutPostRedisplay();
}
//****************************************************************
//	Date:		04/29/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMouseEvent
//	Inputs:		none
//	Output:		none
//	Note:		THis is taken from Dr.Gossett example in class with a little abstraction
//******************************************************************
void myMouseEvent(int button,int state,int xPos,int yPos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Assignment5::Instance()->MouseInstance()->SetLeftButton(Mouse::BUTTON_DN);
		Assignment5::Instance()->MouseInstance()->UpdatePosition(xPos,yPos);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Assignment5::Instance()->MouseInstance()->SetRightButton(Mouse::BUTTON_DN);	
		Assignment5::Instance()->MouseInstance()->UpdatePosition(xPos,yPos);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Assignment5::Instance()->MouseInstance()->SetLeftButton(Mouse::BUTTON_UP);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		Assignment5::Instance()->MouseInstance()->SetRightButton(Mouse::BUTTON_UP);	
	}
}