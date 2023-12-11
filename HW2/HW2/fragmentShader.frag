#version 330 core

in vec2 texCoord;
in vec4 worldPos;
in vec3 normal;

uniform sampler2D ourTexture;
uniform int color;
out vec4 FragColor;

void main()
{
	vec3 lightPos = vec3(5, 10, 10);
	vec3 n_normal = normalize(normal);
	vec3 light = (normalize(vec4(lightPos, 1.0) - worldPos)).xyz;

	float diffuse = max(dot(light, n_normal), 0.0);
    if(color==0){
    
        FragColor = texture(ourTexture,texCoord);

    }
    else{
        FragColor = texture(ourTexture,texCoord);
        if(FragColor.r+FragColor.g+FragColor.b<0.8){
            FragColor=vec4(0.2,0.0,0.0,1.0);
        }
    }
   
    

    

}