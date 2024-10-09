#shader vertex
#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float minHeight;
uniform float maxHeight;

out vec4 Color;
out vec2 Tex;
out vec3 worldPos;
out vec3 Normal;

void main(){
    gl_Position = projection * view * vec4(aPos, 1.0);

    float delta = maxHeight - minHeight;

    float ratio = (aPos.y - minHeight) / delta;

    float c = ratio * 0.8 + 0.2;

    Color = vec4(c, c, c, 1.0);

    Tex = aTexCoords;

    worldPos = aPos;

    Normal = aNormal;
}


#shader fragment
#version 330

layout (location = 0) out vec4 FragColor;

uniform mat4 view;

in vec4 Color;
in vec2 Tex;
in vec3 worldPos;
in vec3 Normal;

uniform sampler2D gTextureHeight0;
uniform sampler2D gTextureHeight1;
uniform sampler2D gTextureHeight2;
uniform sampler2D gTextureHeight3;

uniform float gHeight0;
uniform float gHeight1;
uniform float gHeight2;
uniform float gHeight3;

uniform vec3 gReversedLightDir;

vec4 CalcTexColor()
{
    vec4 TexColor;

    float Height = worldPos.y;

    if (Height < gHeight0) {
       TexColor = texture(gTextureHeight0, Tex);
    } else if (Height < gHeight1) {
       vec4 Color0 = texture(gTextureHeight0, Tex);
       vec4 Color1 = texture(gTextureHeight1, Tex);
       float Delta = gHeight1 - gHeight0;
       float Factor = (Height - gHeight0) / Delta;
       TexColor = mix(Color0, Color1, Factor);
    } else if (Height < gHeight2) {
       vec4 Color0 = texture(gTextureHeight1, Tex);
       vec4 Color1 = texture(gTextureHeight2, Tex);
       float Delta = gHeight2 - gHeight1;
       float Factor = (Height - gHeight1) / Delta;
       TexColor = mix(Color0, Color1, Factor);
    } else if (Height < gHeight3) {
       vec4 Color0 = texture(gTextureHeight2, Tex);
       vec4 Color1 = texture(gTextureHeight3, Tex);
       float Delta = gHeight3 - gHeight2;
       float Factor = (Height - gHeight2) / Delta;
       TexColor = mix(Color0, Color1, Factor);
    } else {
       TexColor = texture(gTextureHeight3, Tex);
    }

    return TexColor;
}

void main()
{
   vec4 TexColor = CalcTexColor();

       // Calculate flat shading for sharp triangle appearance
       vec3 norm = normalize(Normal);

       // Increase the sharpness of the lighting to enhance triangle separation
       float Diffuse = max(0.1, -dot(norm, gReversedLightDir));

       // Sharper shading effect by clamping and enhancing contrast
       if (Diffuse > 0.7) {
           Diffuse = 1.0;  // Strong light side
       } else if (Diffuse > 0.4) {
           Diffuse = 0.7;  // Medium light side
       } else {
           Diffuse = 0.4;  // Darker shade for sharper contrast
       }

       // Multiply color with the texture and the enhanced lighting
       FragColor = Color * TexColor * Diffuse;



}
