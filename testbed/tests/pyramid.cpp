// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test.h"

static void createWall(b2Body* ground, float x1, float y1, float x2, float y2) {
	b2EdgeShape shape;
	shape.SetTwoSided(b2Vec2(x1, y1), b2Vec2(x2, y2));
	ground->CreateFixture(&shape, 0.0f);
}

static void createBacterium(b2World* world, b2Vec2 position, float rectangleWidth, float rectangleHeight, float circleRadius) {
	// Define the rectangle shape
	b2PolygonShape rectangleShape;
	rectangleShape.SetAsBox(rectangleWidth / 2.0f, rectangleHeight / 2.0f);

	// Define the circle shape
	b2CircleShape circleShape;
	circleShape.m_radius = circleRadius;

	// Define the body
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = position;
	b2Body* body = world->CreateBody(&bd);

	// Attach the rectangle fixture
	body->CreateFixture(&rectangleShape, 0.001f);

	// Attach the circle fixtures at the ends of the rectangle
	circleShape.m_p.Set(0, rectangleHeight / 2.0f); // top circle
	body->CreateFixture(&circleShape, 0.001f);
	circleShape.m_p.Set(0, -rectangleHeight / 2.0f); // bottom circle
	body->CreateFixture(&circleShape, 0.001f);
}

class Pyramid : public Test
{
public:
	Pyramid()
	{
		// Create ground and walls
		b2BodyDef bd;
		b2Body* ground = m_world->CreateBody(&bd);
		createWall(ground, -50.0f, 0.0f, 50.0f, 0.0f);
		createWall(ground, -50.0f, 0.0f, -50.0f, 60.0f);
		createWall(ground, 50.0f, 0.0f, 50.0f, 60.0f);

		// Create bacterium
		b2Vec2 position(0.0f, 1.0f);
		createBacterium(m_world, position, 1.0f, 4.0f, 0.5f);
	}

	void Step(Settings& settings) override
	{
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new Pyramid;
	}
};

// Register the Pyramid test
static int testIndex = RegisterTest("Stacking", "Pyramid", Pyramid::Create);
