#version 150

struct Light
{
	vec4	position;
	vec4	color;
	vec4	direction;
	float	cutoffangle;
};

in vec4 vPosition;
in vec4 vAmbientDiffuseColor;
in vec3 vNormal;
in vec4 vSpecularColor;
in float vSpecularExponent;
in vec2 vTexture;
in vec4 vTangent;

uniform mat4 model_view;
uniform mat4 projection;
uniform Light lightSun;


out vec3 position;
out vec3 vN;

out vec4 AmbientDiffuseColor;
out vec4 SpecularColor;
out float SpecularExponent;
out vec2 vTexCoord;
out vec3 tT;

void
main()
{

	vec4 vNormal = vec4(vNormal,0);
	vec4 veyepos = model_view * vPosition;



	AmbientDiffuseColor	=	vAmbientDiffuseColor;
	SpecularColor		=	vSpecularColor;
	SpecularExponent	=	vSpecularExponent;

	vN					= normalize(model_view * vNormal).xyz;

	position			= veyepos.xyz;

	gl_Position = projection * veyepos;

	vTexCoord	= 	vTexture;
	
	tT = normalize(model_view * vTangent).xyz;

}
