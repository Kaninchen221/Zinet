#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoords;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoords;

layout(binding = 0) uniform MVP {
    mat4 model;
    mat4 view;
    mat4 proj;
} mvp;

//layout(binding = 1) uniform TextureRegion {
//    vec4 value;
//} textureRegion;

void main() {
    gl_Position = mvp.proj * mvp.view * mvp.model * vec4(inPosition, 1.0);
    //gl_Position = vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoords = inTexCoords;
	fragTexCoords = vec2(inTexCoords.x / 2.0 + 0.25, inTexCoords.y / 2.0 + 0.25);
}