#version 330 core

out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float time;

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;
	//vec3 specular = light.specular * spec * vec3(vec3(1.0) - vec3(texture(material.specular, TexCoord)));  // Exercise2: here we inverse the sampled specular color. Black becomes white and white becomes black.

	// Exercise 4: emission
	//vec3 show_emission = step(vec3(1.0f), vec3(1.0f) - texture(material.specular, TexCoord).rgb);
	//vec3 emission = texture(material.emission, TexCoord).rgb * show_emission;
	vec3 emission = vec3(0.0);
	if (texture(material.specular, TexCoord).r == 0.0) // rough check for blackbox inside spec texture
	{
		// some extra fun stuff with "time uniform"
		emission = texture(material.emission, TexCoord + vec2(0.0, time*0.1)).rgb; //moving
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;  //fading
	}

	vec3 result = ambient + diffuse + specular + emission;
	FragColor = vec4(result, 1.0);
}