#version 150

struct Light
{
	vec4	position;
	vec4	color;
	vec4	direction;
	float	cutoffangle;
};

in vec3 position;
in vec3 vN;

in vec4 AmbientDiffuseColor;
in vec4 SpecularColor;
in float SpecularExponent;

in vec2 vTexCoord;
in vec3 tT;

uniform Light lightSun;
uniform mat4 model_view;
uniform mat4 projection;

uniform sampler2D textureEarth;
uniform sampler2D textureSpec;
uniform sampler2D textureNight;
uniform sampler2D textureClouds;
uniform sampler2D textureNormal;
uniform int		  mapMode;				//0 - surface, 1 - spec, 2 - night, 3 - final

out vec4  fColor;

vec3 CalcLVector(vec4 source_position, vec3 pos)
{
	return normalize(source_position.xyz - pos.xyz);
}

vec3 HalfAngle(vec3 l, vec3 e)
{
	return normalize(l + e);
}

vec4 Diffuse(vec3 l, vec3 n, vec4 clr, vec4 direction)
{
	vec3 d = normalize(direction).xyz;
	float co = cos(3.14);

	if (dot(-l,d) >  co) 
		return max(dot(l,n),0.0) * AmbientDiffuseColor * clr;
	else
		return vec4(0,0,0,1);
}

vec4 Specular(vec3 n, vec3 h, vec4 clr,vec3 l, vec4 direction)
{
	vec3 d = normalize(direction).xyz;
	float co = cos(3.14);

	if (dot(-l,d) >  co) 
		return pow(max(dot(n,h),0.0),100) * SpecularColor * clr;
	else
		return vec4(0,0,0,1);	
}

void
main()
{
	

	vec4 ambient_light = vec4(0.2,0.2,0.2,1.0);

	vec3 N = normalize(vN.xyz);
	vec3 E = -normalize(position.xyz);
	vec3 L = CalcLVector(lightSun.position, position);
	vec3 H = HalfAngle(L,E);

	vec4 amb = AmbientDiffuseColor * ambient_light;
	vec4 diff = Diffuse(L,N,lightSun.color,lightSun.direction);
	vec4 spec = Specular(N,H,lightSun.color,L,lightSun.direction);

	//vec3 TL = normalize(tT).xyz;
	
	//trying computing normal lighting in FSHADER
	
	//compute tangent vector on  a fly....for some reason getting vector from CPP doesn't work well
	vec3 TL = normalize(cross(vN,vec3(0,1,0))).xyz;
	
	//computer binormal
	vec3 tB = normalize(cross(normalize(vN).xyz, normalize(TL).xyz)).xyz;

	//mattrix to convert to tangent space
	mat4 local	= mat4(vec4(TL,0),vec4(tB,0),vec4(N,0),vec4(0,0,0,1));

	//normal from normal map
	vec3 N1 = (texture2D(textureNormal,vTexCoord) * 2.0 - 1.0).xyz;

	//eye in tangent space
	vec3 E1 = (local * vec4(normalize(position.xyz),0)).xyz;
	
	//lighting and half vectors in tangent space
	vec3 b1 = vec3(lightSun.position).xyz -  (position).xyz;
	vec3 L1 = (local * vec4(b1,0)).xyz;
	vec3 H1 = HalfAngle(L1,E1);

	vec4 diff1 = max(dot(L1,N1),0.0) * vec4(0.1,0.1,0.1,1.0);
	vec4 spec1 = pow( max(dot(N1,H1),0.0), 10) * lightSun.color;

	if (dot(L1,N1) < 0.0)
	{
		spec1 = vec4(0,0,0,1);
	}

	vec4 normalK	=(ambient_light + diff1 + spec1) / 5.0;

	float	f = dot(L,N);

	if (f < 0.0)
	{
		spec = vec4(0,0,0,1);
	}

	//simple mapped surface
	if (mapMode == 0)
	{
		fColor = texture2D(textureEarth,vTexCoord);
	}
	//specular  map
	else if (mapMode == 1)
	{
		fColor = texture2D(textureSpec,vTexCoord);
	}
	//night map
	else if (mapMode == 2)
	{
		fColor = texture2D(textureNight,vTexCoord);
	}
	//clouds map
	else if (mapMode == 3)
	{	
		fColor = texture2D(textureClouds,vTexCoord) * ((f + 1.0) * 0.5);
	}
	//combined map
	else if (mapMode == 4)
	{
		if (f >= 0.2)
			fColor = texture2D(textureEarth,vTexCoord) * normalK + spec * texture2D(textureSpec,vTexCoord) + diff * 0.5;
		else if (f <= -0.2)
		{
			fColor = texture2D(textureNight,vTexCoord);
		}
		else
		{
			float daypart  =  (f + 0.2) / 0.4;
			fColor = (texture2D(textureNight,vTexCoord) * ((1.0 - daypart) * (1.0 - daypart) * (1.0 - daypart)))  + (texture2D(textureEarth,vTexCoord) * normalK + 0.5 * diff) * daypart;
		
		}
	}
	//normal mappping with surface map
	else if (mapMode == 5)
	{
		fColor =texture2D(textureEarth,vTexCoord) * normalK;
	}
	else if (mapMode == 6)
	{
		fColor = vec4(0,0,0,1);
	}
}
