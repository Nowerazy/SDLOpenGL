#version 120
uniform sampler2D diffuse;
uniform float iTime; 
varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 lightway;
void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0)*
	clamp(dot(lightway,normal0) , 0.5 , 1.0);
}