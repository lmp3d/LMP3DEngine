#version 130

//input data from the VBO. Each vert is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;

void main() {
	//Set the XY position
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	//Set the z position
	gl_Position.z = 0.0;
	//set the W to 1
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	
	fragmentColor = vertexColor;
	
	fragmentUV = vertexUV;
}