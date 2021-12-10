#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

in vec3 Normal;
in vec3 curPos;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;

vec4 pointLight() 
{
	vec3 lightVec = lightPos - curPos;
	float dist = length(lightVec);
	float a = 0.3;
	float b = 1.0;
	float inten = 1.0f / (a * dist * dist + b + dist + 1.0f);

	float ambient = 0.20f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	float specularLight = .50f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	//return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
	return (texture(tex0, texCoord) * (diffuse * inten + ambient)) * lightColor;
}

void main()
{
	FragColor = pointLight();
}
