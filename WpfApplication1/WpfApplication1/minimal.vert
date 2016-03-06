// Vertex Shader – file "minimal.vert"
//#version 120

//layout(location = 0) in
attribute vec3 in_Position;
//layout(location = 1) in
attribute vec3 in_Color;
//out
varying vec3 frag_Color;

void main(void)
{
    frag_Color = in_Color;
    gl_Position = vec4(in_Position, 1.0);
}
