#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoords;

layout(location = 0) out vec4 outColor;

void main() {
	vec4 colorAfterSampling = texture(texSampler, fragTexCoords) * fragColor;
	outColor = colorAfterSampling;
	//outColor = vec4(gl_FragCoord.a, gl_FragCoord.a, gl_FragCoord.a, colorAfterSampling.a);
	
	//if (outColor.a < 1.0)
		//discard;
}