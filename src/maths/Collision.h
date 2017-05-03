#pragma once

#include "Vec2.h"
#include "../util/Log.h"
#include <algorithm>

struct AABB
{
	Vec2 min;
	Vec2 max;
};

struct Object
{
	AABB aabb;
	Vec2 pos;
	Vec2 velocity;
	Vec2 force;

	float density; 
	float restitution;

	float mass;
	float inv_mass;

	void initMass()
	{
		mass = (aabb.min.x + aabb.max.x) * (aabb.min.y + aabb.max.y) * density;

		if (mass == 0)
			inv_mass = 0;
		else
			inv_mass = 1 / mass;
	}
};

struct Manifold
{
	Object *A;
	Object *B;
	float penetration;
	Vec2 normal;
};

static void ResolveCollision(Manifold& m, Object A, Object B)
{
	Vec2 rv = B.velocity - A.velocity;

	float velAlongNormal = dot(rv, m.normal);

	if (velAlongNormal > 0)
		 return;

	float e = std::min(A.restitution, B.restitution);

	float j = -(1 + e) * velAlongNormal;
	j /= A.inv_mass + B.inv_mass;
	LOG_INFO(j);
	Vec2 impulse = j * m.normal;
	A.velocity += impulse * A.inv_mass;

	B.velocity += impulse * B.inv_mass;
}

static void PositionalCorrection(Manifold& m, Object A, Object B)
{
	const float percent = 0.2f;
	const float slop = 0.01f;
	Vec2 n = B.pos - A.pos;
	Vec2 correction = std::max(m.penetration - slop, 0.0f) / (A.inv_mass + B.inv_mass) * percent * n;
	A.pos -= A.inv_mass * correction;
	B.pos += B.inv_mass * correction;
}

static bool AABBtoAABB(Manifold* m)
{
	Object *A = m->A;
	Object *B = m->B;

	Vec2 n = B->pos - A->pos;

	AABB abox = A->aabb;
	AABB bbox = B->aabb;

	float a_extent = (abox.max.x - abox.min.x) / 2;
	float b_extent = (bbox.max.x - bbox.min.x) / 2;

	float x_overlap = a_extent + b_extent - abs(n.x);

	if (x_overlap > 0)
	{
		float a_extent = (abox.max.y - abox.min.y) / 2;
		float b_extent = (bbox.max.y - bbox.min.y) / 2;

		float y_overlap = a_extent + b_extent - abs(n.y);

		if (y_overlap > 0)
		{
			if (x_overlap > y_overlap)
			{
				if (n.x < 0)
					m->normal = Vec2(-1, 0);
				else
					m->normal = Vec2(0, 0);
				m->penetration = x_overlap;
				return true;
			}
			else
			{
				if (n.y < 0)
					m->normal = Vec2(0, -1);
				else
					m->normal = Vec2(0, 1);
				m->penetration = y_overlap;
				return true;
			}
		}
	}
	return false;
}