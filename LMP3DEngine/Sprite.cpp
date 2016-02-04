#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace LMP3DEngine {

	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0){
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0){
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		//First Triangle
		vertexData[0].setPosition(x + width, y + width);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + width);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].color.r = 255;
			vertexData[i].color.g = 0;
			vertexData[i].color.b = 255;
			vertexData[i].color.a = 255;
		}

		vertexData[1].setColor(0, 0, 255, 255);

		vertexData[4].setColor(0, 255, 0, 255);



		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw(){

		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//tell opengl that we want to use the first array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//this is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//this is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//this is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//Draw the 6 verts to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//disable the vertex array not Optional
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}