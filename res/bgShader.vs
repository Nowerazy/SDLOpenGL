#version 120
attribute vec3 position;
varying vec2 texCoord0;
void main()
{
    gl_Position =  vec4(position,1.0);
	texCoord0 = (position.xy+1.0)/2;
	texCoord0.y=1.0-texCoord0.y;
}
