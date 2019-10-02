#version 120
uniform sampler2D bg;
varying vec2 texCoord0;
void main()
{
	//gl_FragColor = texture2D(bg, texCoord0);
	gl_FragColor = vec4(1.f,1.f,0.,1.0);
}