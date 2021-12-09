#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

in vec3 Normal;
in vec3 curPos;

uniform sampler2D tex0;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;

void main()
{
	float ambient = 0.20f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - curPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	float specularLight = .50f;
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}