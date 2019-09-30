#version 120
attribute vec3 bgPosition;
varying vec2 texCoord0;
void main()
{
    gl_Position =  vec4(bgPosition,1.0);
	texCoord0 = (bgPosition.xy+1.0)/2;
	texCoord0.y=1.0-texCoord0.y;
}
