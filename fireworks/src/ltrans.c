#include "ltrans.h"
#include "lmath.h"
#include <math.h>

LMMat4 ltRTransform(RadialTransform *rtransform) {
	LMMat4 t = ltTranslate(0, 0, rtransform->r);
	LMMat4 r = ltRotateY(rtransform->alpha);
	LMMat4 z = ltRotateX(rtransform->theta);
	LMMat4 g = ltRotateZ(rtransform->gamma);
	LMMat4 m;
	m = lmMat4Mult(z, t);
	m = lmMat4Mult(g, m);
	m = lmMat4Mult(r, m);
	return m;
}

LMMat4 ltTransform(Transform* transform) {
	LMMat4 m = ltTranslate_v(transform->position);
	LMMat4 t = ltRotate_v(transform->rotation);
	m = lmMat4Mult(m , t);
	t = ltScale_v(transform->scale);
	m = lmMat4Mult(m , t);
	return m;
}

LMMat4 ltTranslate_v(LMVec3 v)
{
	return ltTranslate(v.x, v.y, v.z);
}

LMMat4 ltTranslate(float x, float y, float z)
{
	LMMat4 m =
	{
		{ 1, 0, 0, 0},
		{ 0, 1, 0, 0},
		{ 0, 0, 1, 0},
		{ x, y, z, 1}
	};
	return m;
}

LMVec3 ltGetTranslate(LMMat4 m) {
	LMVec3 v = { .x = m.l.x, .y = m.l.y, .z = m.l.z };
	return v;
}

LMMat4 ltScale_v(LMVec3 v)
{
	return ltScale(v.x, v.y, v.z);
}
LMMat4 ltScale(float x, float y, float z)
{
	LMMat4 m = 
	{
		{ x, 0, 0, 0},
		{ 0, y, 0, 0},
		{ 0, 0, z, 0},
		{ 0, 0, 0, 1}
	};
	return m;
}

LMVec3 ltVectorToRotation(LMVec3 v) {
	v = lmVec3Normalize(v);
	float x = -asinf(v.y);
	return (LMVec3) {
		.x = isnan(x) ? 0 : x,
		.y = atan2f(v.x, v.z),
		.z = asin(v.z)
	};
}

LMMat4 ltRotate_v(LMVec3 v)
{
	return ltRotate(v.x, v.y, v.z);
}
LMMat4 ltRotate(float x, float y, float z)
{
	LMMat4 rotz = ltRotateZ(z);
	LMMat4 rotx = ltRotateX(x);
	LMMat4 roty = ltRotateY(y);

	LMMat4 rm = lmMat4Mult(rotz, roty);
	rm = lmMat4Mult(rm, rotx);
	return rm;
}

LMMat4 ltRotateX(float r) {
	return (LMMat4) {
		{1, 0, 0, 0},
		{0, cos(r), sin(r), 0},
		{0, -sin(r), cos(r), 0},
		{0, 0, 0, 1}
	};
}

LMMat4 ltRotateY(float r) {
	return (LMMat4) {
		{cos(r),	0, -sin(r), 0},
		{0, 		1, 0, 		 0},
		{sin(r), 	0, cos(r), 	 0},
		{0, 0, 		0,			 1}
	};
}

LMMat4 ltRotateZ(float r) {
	return (LMMat4) {
		{cos(r), sin(r), 0, 0},
		{-sin(r), cos(r), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
}

LMVec3 ltSphereTangent(LMVec3 v) {
	LMVec3 a = { 0, 1, 0 };
	LMVec3 d = lmVec3CrossProduct(a, ltSphereNormal(v, (LMVec3){0, 0, 0}));
	return lmVec3Normalize(d);
}

LMVec3 ltSphereNormal(LMVec3 v, LMVec3 spherePos) {
	return lmVec3Normalize(lmVec3Sub(v, spherePos));
}

LMMat4 ltOrthographic(LTOrthographicDescriptor* desc) {
	LMVec3 tra = {
	  -((desc->right + desc->left) / (desc->right - desc->left)),
	  -((desc->top + desc->bottom) / (desc->top - desc->bottom)),
	  -((desc->far + desc->near) / (desc->far - desc->near))
	};

	LMMat4 o = {
		{2.0f / (desc->right - desc->left), 0, 0, 0},
		{0, 2.0f / (desc->top - desc->bottom), 0, 0},
		{0, 0, -2.0f / (desc->far - desc->near), 0},
		{tra.x, tra.y, tra.z, 1.0f}
	};

	return o;
}

LMMat4 ltPerspective(LTPerspectiveDescriptor* desc) {
	float fov = M_PI / 180.f * desc->fov;
	float top = tan(fov / 2.0f);
	float right = top * desc->aspect;
	LMMat4 m = {
		{desc->near / right, 0, 0, 0},
		{0, desc->near / top, 0, 0},
		{0, 0, (-(desc->far + desc->near))/(desc->far - desc->near), -1.0f},
		{0, 0, (-2 * desc->far * desc->near) / (desc->far - desc->near), 0.0f}
	};

	return m;
}
