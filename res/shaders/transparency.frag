uniform float u_Opacity;

uniform sampler2D u_Texture;

void main()
{
    vec4 color = texture2D(u_Texture, gl_TexCoord[0].xy);
    color.a *= u_Opacity;
    gl_FragColor = color;
}