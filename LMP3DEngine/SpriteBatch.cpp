#include "SpriteBatch.h"
#include <algorithm>

namespace LMP3DEngine{

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}


SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init(){
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType/* GlyphSortType::TEXTURE */) {
	_sortType = sortType;
	_renderBatches.clear();
	for (int i = 0; i < _glyphs.size(); i++){
		delete _glyphs[i];
	}
	_glyphs.clear();
}

void SpriteBatch::end() {
	sortGlyphs();
	createRenderBatches();

}

void SpriteBatch::draw(const glm::vec4& destinationRect, const glm::vec4& uvRectangle, GLuint texture, float depth, const Color& color){
	Glyph* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destinationRect.x, destinationRect.y + destinationRect.w);
	newGlyph->topLeft.setUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destinationRect.x, destinationRect.y);
	newGlyph->bottomLeft.setUV(uvRectangle.x, uvRectangle.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y);
	newGlyph->bottomRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
	newGlyph->topRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);

	_glyphs.push_back(newGlyph);

}

void SpriteBatch::renderBatch() {

	glBindVertexArray(_vao);

	for (int i = 0; i < _renderBatches.size(); i++){
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVerticies);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches() {
	std::vector <Vertex> verticies;
	verticies.resize(_glyphs.size() * 6);

	if (_glyphs.empty()) {
		return;
	}
	int offset = 0;
	int cv = 0; //current vertex
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	verticies[cv++] = _glyphs[0]->topLeft;
	verticies[cv++] = _glyphs[0]->bottomLeft;
	verticies[cv++] = _glyphs[0]->bottomRight;
	verticies[cv++] = _glyphs[0]->bottomRight;
	verticies[cv++] = _glyphs[0]->topRight;
	verticies[cv++] = _glyphs[0]->topLeft;
	offset += 6;

	for (int cg = 1; cg < _glyphs.size(); cg++) {
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		} else {
			_renderBatches.back().numVerticies += 6;
		}
		verticies[cv++] = _glyphs[cg]->topLeft;
		verticies[cv++] = _glyphs[cg]->bottomLeft;
		verticies[cv++] = _glyphs[cg]->bottomRight;
		verticies[cv++] = _glyphs[cg]->bottomRight;
		verticies[cv++] = _glyphs[cg]->topRight;
		verticies[cv++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	//upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticies.size() * sizeof(Vertex), verticies.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray() {

	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);

	if (_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

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

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs() {
	switch (_sortType){
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
		break;

	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){
	return (a->texture < b->texture);
}

}