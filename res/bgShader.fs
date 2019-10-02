#version 120
uniform sampler2D bg;
varying vec2 texCoord0;
void main()
{
	vec4 tem=texture2D(bg, texCoord0);
	tem.a=0.5;
	gl_FragColor = tem ;
	//gl_FragColor = vec4(1.f,1.f,0.,1.0);
}