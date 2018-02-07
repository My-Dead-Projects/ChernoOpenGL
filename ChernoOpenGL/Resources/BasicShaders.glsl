#shader vertex

#version 400

in vec4 position;

void main()
{
  gl_Position = position;
}



#shader fragment

#version 400

out vec4 frag_color;

uniform vec4 u_color;

void main()
{
  frag_color = u_color;
}
