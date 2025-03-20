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

out vec3 L_normal;
out vec3 H_normal;

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

	vec3 N_normal = vN;

	//vec3 tT = normalize(model_view * vTangent).xyz;

	//computing tangent on a fly in vshader
	vec3 tT = normalize(cross(N_normal,vec3(0,1,0))).xyz;
	vec3 tB = cross(N_normal,tT);
	mat4 local	= mat4(vec4(tT,0),vec4(tB,0),vec4(N_normal,0),vec4(0,0,0,1));

	L_normal = (local * vec4(normalize(lightSun.position.xyz -position),0)).xyz;

	vec3 E_normal = (local * vec4(normalize(-position),0)).xyz;
	

	H_normal = normalize(L_normal + E_normal);

}
