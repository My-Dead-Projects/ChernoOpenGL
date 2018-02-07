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

void main()
{
  frag_color = vec4(0.5, 0.0, 0.5, 1.0);
}
