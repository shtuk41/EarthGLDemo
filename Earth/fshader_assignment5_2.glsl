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
in vec3 L_normal;
in vec3 H_normal;

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

	//normal from normal map
	vec3 N_normal = (texture2D(textureNormal,vTexCoord) * 2 - 1).xyz;

	//diffuse and spec lighting
	vec4 diff_normal = max(dot(L_normal,N_normal),0.0) * AmbientDiffuseColor * lightSun.color;
	vec4 spec_normal = pow( max(dot(N_normal,H_normal),0.0), 100) * lightSun.color;

	if (dot(L_normal,N_normal) < 0.0)
	{
		spec_normal = vec4(0,0,0,1);
	}

	vec4 normalK	=(ambient_light + diff_normal + spec_normal);

	float	f = dot(L,N);

	if (f < 0.0)
	{
		spec = vec4(0,0,0,1);
	}

	//surface map
	if (mapMode == 0)
	{
		fColor = texture2D(textureEarth,vTexCoord);
	}
	//spec map with lighting
	else if (mapMode == 1)
	{
		fColor = texture2D(textureSpec,vTexCoord) * (spec + ambient_light + diff);
	}
	//night map
	else if (mapMode == 2)
	{
		fColor = texture2D(textureNight,vTexCoord);
	}
	//clouds
	else if (mapMode == 3)
	{	
		fColor = texture2D(textureClouds,vTexCoord) * ((f + 1.0) * 0.2);
	}
	//combined map
	else if (mapMode == 4)
	{
		if (f >= 0.2)
			fColor = texture2D(textureEarth,vTexCoord) * normalK + spec * texture2D(textureSpec,vTexCoord) + diff * 0.5;
		else if (f <= -0.2)
		{
			fColor = texture2D(textureNight,vTexCoord) ;
		}
		else
		{
			float daypart  =  (f + 0.2) / 0.4;
			fColor = (texture2D(textureNight,vTexCoord)* ((1.0 - daypart) * (1.0 - daypart) * (1.0 - daypart)))  + (texture2D(textureEarth,vTexCoord) * normalK + 0.5 * diff) * daypart;
		
		}
	}
	//normal map with lighting no surface
	else if (mapMode == 5)
	{
		fColor = normalK;
	}
	else if (mapMode == 6)
	{
		fColor = vec4(0,0,0,1);
	}
}
