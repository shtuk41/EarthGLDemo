#include "GraphObjects.h"
#include "TextureOpenIL.h"

const float fM_PI = 3.14159265358979323846f;

//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Earth
//	Function:	INit
//	Inputs:		none
//	Output:		none
//	Purpose:	Initilalize Head
/*

 Author: Nathan Gossett
 code to generate a sphere
 Note that this code is not a complete program
 
 **/

//******************************************************************

double Earth::ConvJ(double j)
{
	return ((j + fM_PI) / (fM_PI * 2.0));	
}

vec4 CalcTangent(vec3 a)
{
	return vec4(cross(a,vec3(0,0,-1)),0);
}

void Earth::Init()
{
	vec3	test = vec3(0,1,0);
	
	vec4	newtest = CalcTangent(test);

	float step = static_cast<float>((360.0/40.0)*(fM_PI/180.0));

	int k = 0;
	for(float i = -fM_PI/2.0; i<=fM_PI/2.0; i+=step){
		for(float j = -fM_PI; j<=fM_PI; j+=step){


			double dI = i * 180.0 / fM_PI;
			double dJ = j * 180.0 / fM_PI;
			//triangle 1
			v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
			v3Normal[k]=vec3(glfRadius*sin(j)*cos(i),glfRadius*cos(j)*cos(i),glfRadius*sin(i));
			v4Vertices[k]=   vec4(glfRadius*sin(j)*cos(i), glfRadius*cos(j)*cos(i), glfRadius*sin(i), 1.0);
			v2Texture[k]= vec2(ConvJ(j), (1 + sin(i)) / 2.0);
			v4Tangent[k]= CalcTangent(v3Normal[k]);
			k++;
		
			v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
			v3Normal[k]=vec3(glfRadius*sin(j)*cos(i + step),glfRadius*cos(j)*cos(i + step),glfRadius*sin(i + step));
			v4Vertices[k]=   vec4(glfRadius*sin(j)*cos(i+step), glfRadius*cos(j)*cos(i+step), glfRadius*sin(i+step), 1.0);
			v2Texture[k]= vec2(ConvJ(j),(1+sin(i + step))/2.0);
			v4Tangent[k]= CalcTangent(v3Normal[k]);
			k++;
				
			v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
			v3Normal[k]=vec3(glfRadius*sin(j+step)*cos(i + step),glfRadius*cos(j+step)*cos(i + step),glfRadius*sin(i + step));
			v4Vertices[k]=   vec4(glfRadius*sin((j+step))*cos((i+step)), glfRadius*cos(j+step)*cos(i+step), glfRadius*sin(i+step), 1.0);
			v2Texture[k]= vec2(ConvJ(j + step),(1+sin(i + step))/2.0);
			v4Tangent[k]= CalcTangent(v3Normal[k]);
			k++;

			//triangle 2
			v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
			v3Normal[k]=vec3(glfRadius*sin((j+step))*cos((i+step)), glfRadius*cos(j+step)*cos(i+step), glfRadius*sin(i+step));
			v4Vertices[k]=   vec4(glfRadius*sin((j+step))*cos((i+step)), glfRadius*cos(j+step)*cos(i+step), glfRadius*sin(i+step), 1.0);
			v2Texture[k]= vec2(ConvJ(j + step),(1+sin(i + step))/2.0 );
			v4Tangent[k]= CalcTangent(v3Normal[k]);
			k++;

			v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
			v3Normal[k]=vec3(glfRadius*sin(j+step)*cos(i), glfRadius*cos(j+step)*cos(i), glfRadius*sin(i));
			v4Vertices[k]=   vec4(glfRadius*sin(j+step)*cos(i), glfRadius*cos(j+step)*cos(i), glfRadius*sin(i), 1.0);
			v2Texture[k]= vec2(ConvJ(j+step),(1+sin(i))/2.0);
			v4Tangent[k]= CalcTangent(v3Normal[k]);
			k++;

			v4AmbientDiffuseColor[k] = vec4(1.0,1.0,1.0,1.0);
			v3Normal[k]=vec3(glfRadius*sin(j)*cos(i), glfRadius*cos(j)*cos(i), glfRadius*sin(i));
			v4Vertices[k]=   vec4(glfRadius*sin(j)*cos(i), glfRadius*cos(j)*cos(i), glfRadius*sin(i), 1.0);
			v2Texture[k]= vec2(ConvJ(j),(1+sin(i))/2.0);
			v4Tangent[k]= CalcTangent(v3Normal[k]);
			k++;

			//system("pause");
		}
	}

	program = InitShader("vshader_Assignment5_2.glsl","fshader_Assignment5_2.glsl");
	//program = InitShader("vshader_Assignment5.glsl","fshader_Assignment5.glsl");

	glGenVertexArrays(1, &vao[0]);

	glBindVertexArray(vao[0]);
	glGenBuffers(5,&vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(v4Vertices),v4Vertices,GL_STATIC_DRAW);
	vPosition = glGetAttribLocation(program,"vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition,4,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(v4AmbientDiffuseColor),v4AmbientDiffuseColor,GL_STATIC_DRAW);
	vAmbientDiffuseColor = glGetAttribLocation(program,"vAmbientDiffuseColor");
	glEnableVertexAttribArray(vAmbientDiffuseColor);
	glVertexAttribPointer(vAmbientDiffuseColor,4,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,vbo[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(v3Normal),v3Normal,GL_STATIC_DRAW);
	vNormal = glGetAttribLocation(program,"vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer( GL_ARRAY_BUFFER, vbo[3] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(v2Texture), v2Texture, GL_STATIC_DRAW);
	vTexture = glGetAttribLocation(program,"vTexture");
	glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture,2,GL_FLOAT,GL_FALSE,0,0);

	glBindBuffer( GL_ARRAY_BUFFER, vbo[4] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(v4Tangent), v4Tangent, GL_STATIC_DRAW);
	vTangent = glGetAttribLocation(program,"vTangent");
	glEnableVertexAttribArray(vTangent);
	glVertexAttribPointer(vTangent,4,GL_FLOAT,GL_FALSE,0,0);

	vSpecularColor = glGetUniformLocation(program,"vSpecularColor");
	vSpecularExponent = glGetUniformLocation(program,"vSpecularExponent");


	model_view = glGetUniformLocation(program,"model_view");
	projection = glGetUniformLocation(program,"projection");

	lightSun.position			=	 glGetUniformLocation(program,"lightSun.position");
	lightSun.color				=	 glGetUniformLocation(program,"lightSun.color");
	lightSun.direction			=	 glGetUniformLocation(program,"lightSun.direction");

	glfRotAngle = 0.0;



	ILuint ilTexID[4]; /* ILuint is a 32bit unsigned integer.
    //Variable texid will be used to store image name. */

	ilInit(); /* Initialization of OpenIL */
	ilGenImages(4, ilTexID); /* Generation of ONE FOR NOW image names for OpenIL image loading */
	glGenTextures(4, gluiTexName); //and we eventually want the data in an OpenGL texture

	//EARTH
	gluiTexMap[0] = glGetUniformLocation(program, "textureEarth");
	glUniform1i(gluiTexMap[0], 0);//assign this one to texture unit 0

	ilBindImage(ilTexID[0]); /* Binding of IL image name */
	TextureOpenIL::loadTexFile("images/Earth.png");
	glBindTexture(GL_TEXTURE_2D, gluiTexName[0]); //bind OpenGL texture name

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   //Note how we depend on OpenIL to supply information about the file we just loaded in
   glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),0,
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

   glGenerateMipmap(GL_TEXTURE_2D);

   //SPECULAR
	gluiTexMap[1] = glGetUniformLocation(program, "textureSpec");
	glUniform1i(gluiTexMap[1], 1);//assign this one to texture unit 1

	ilBindImage(ilTexID[1]); /* Binding of IL image name */
	TextureOpenIL::loadTexFile("images/EarthSpec.png");
	glBindTexture(GL_TEXTURE_2D, gluiTexName[1]); //bind OpenGL texture name

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   //Note how we depend on OpenIL to supply information about the file we just loaded in
   glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),0,
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

   //NIGHT
	gluiTexMap[2] = glGetUniformLocation(program, "textureNight");
	glUniform1i(gluiTexMap[2], 2);//assign this one to texture unit 2

	ilBindImage(ilTexID[2]); /* Binding of IL image name */
	TextureOpenIL::loadTexFile("images/EarthNight.png");
	glBindTexture(GL_TEXTURE_2D, gluiTexName[2]); //bind OpenGL texture name

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   //Note how we depend on OpenIL to supply information about the file we just loaded in
   glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),0,
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

   glGenerateMipmap(GL_TEXTURE_2D);

   //NORMAL

   	gluiTexMap[3] = glGetUniformLocation(program, "textureNormal");
	glUniform1i(gluiTexMap[3], 3);//assign this one to texture unit 2

	ilBindImage(ilTexID[3]); /* Binding of IL image name */
	TextureOpenIL::loadTexFile("images/EarthNormal.png");
	glBindTexture(GL_TEXTURE_2D, gluiTexName[3]); //bind OpenGL texture name

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   //Note how we depend on OpenIL to supply information about the file we just loaded in
   glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),0,
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

	 glGenerateMipmap(GL_TEXTURE_2D);

     ilDeleteImages(4, ilTexID); //we're done with OpenIL, so free up the memory

   gluiMapMode = glGetUniformLocation(program,"mapMode");

   SetRx(90.0);

   SetMap(GraphObject::FINAL);


}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Earth
//	Function:	Draw
//	Inputs:		none
//	Output:		none
//	Purpose:	Draw Earth
//******************************************************************
void Earth::Draw()
{
	if (rx > 360.0)
		rx-= 360.0;

	if (ry > 360.0)
		ry-= 360.0;

	if (rz > 360.0)
		rz-= 360.0;

	mv = mv * Translate(tx,ty,tz);
	mv = mv * RotateX(rx);
	mv = mv * RotateY(ry);
	mv = mv * RotateZ(rz);

	

	glUniformMatrix4fv(model_view,1,GL_TRUE,mv);

	glUniformMatrix4fv(projection,1,GL_TRUE,p);

	glUniform4fv(vSpecularColor,1,GetSpecularColor());
	glUniform1f(vSpecularExponent,GetSpecularExponent());

	vec4 pos = LightSourceManager::GetInstance()->GetLightNumber(0)->GetPosition();
	vec4 color = LightSourceManager::GetInstance()->GetLightNumber(0)->GetColor();
	vec4 dir = LightSourceManager::GetInstance()->GetLightNumber(0)->GetDirection();
	GLfloat  anlge = LightSourceManager::GetInstance()->GetLightNumber(0)->GetCutoffAngle();


	glUniform4fv(lightSun.position,1,LightSourceManager::GetInstance()->GetLightNumber(0)->GetPosition());		
	glUniform4fv(lightSun.color,1,LightSourceManager::GetInstance()->GetLightNumber(0)->GetColor());		
	glUniform4fv(lightSun.direction,1,LightSourceManager::GetInstance()->GetLightNumber(0)->GetDirection());		


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gluiTexName[0]); 

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gluiTexName[1]); 

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gluiTexName[2]); 

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gluiTexName[3]); 


	if (GetMap() == FINAL)
	{
		glUniform1i(gluiMapMode,4);
	}
	else if (GetMap() == SURFACE)
	{
		glUniform1i(gluiMapMode,0);
	}
	else if (GetMap() == SPEC)
	{
		glUniform1i(gluiMapMode,1);
	}
	else if (GetMap() == NIGHT)
	{
		glUniform1i(gluiMapMode,2);
	}
	else if (GetMap() == NORMAL)
	{
		glUniform1i(gluiMapMode,5);
	}
	else if (GetMap() == NONE)
	{
		glUniform1i(gluiMapMode,6);
	}

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES,0,4800);

}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Earth
//	Function:	Rotate
//	Inputs:		none
//	Output:		none
//	Purpose:	Logic handles rotating Earth
//******************************************************************
void Earth::Rotate(double rot)
{
	rz -= GLfloat(rot);

	rz = Utility::Lim360(rz);

	glfRotAngle = rz;
}




