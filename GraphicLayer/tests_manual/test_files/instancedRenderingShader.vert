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

void main() {
	vec3 position = inPosition;
	position.x = position.x + gl_InstanceIndex;
	//position.y = position.y + gl_InstanceIndex;
    gl_Position = mvp.proj * mvp.view * mvp.model * vec4(position, 1.0);
	fragColor = vec4(1.0, 1.0, 1.0, 1.0);
	fragTexCoords = inTexCoords;
	fragTexCoords = fragTexCoords + vec2(gl_InstanceIndex * (512.0 / 4096), 0);
}