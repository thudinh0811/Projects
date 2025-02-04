#ifndef _TRANSFORMATION_DEF_H
#define _TRANSFORMATION_DEF_H

#include "lmath.h"

#undef min
#undef max

#define min(x, y) ((x) < (y) ? x : y)
#define max(x, y) ((x) > (y) ? x : y)

struct Transform {
	LMVec3 position;
	LMVec3 rotation;
	LMVec3 scale;
};
typedef struct Transform Transform;

struct RadialTransform {
	float r;
	float theta;
	float alpha;
	float gamma;
};
typedef struct RadialTransform RadialTransform;

LMMat4 ltRTransform(RadialTransform* rtransform);
LMMat4 ltTransform(Transform* transform);

LMMat4 ltTranslate(float x, float y, float z);
LMMat4 ltTranslate_v(LMVec3 v);
LMVec3 ltGetTranslate(LMMat4 m);

LMMat4 ltScale(float x, float y, float z);
LMMat4 ltScale_v(LMVec3 v);

LMVec3 ltVectorToRotation(LMVec3 v);
LMMat4 ltRotate(float x, float y, float z);
LMMat4 ltRotate_v(LMVec3 v);
LMMat4 ltRotateX(float r);
LMMat4 ltRotateY(float r);
LMMat4 ltRotateZ(float r);

LMVec3 ltSphereTangent(LMVec3 v);
LMVec3 ltSphereNormal(LMVec3 v, LMVec3 spherePos);

typedef struct LTOrthographicDescriptor {
	float left;
	float right;
	float top;
	float bottom;
	float near;
	float far;
} LTOrthographicDescriptor;

LMMat4 ltOrthographic(LTOrthographicDescriptor* desc);

typedef struct LTPerspectiveDescriptor {
	float fov;
	float aspect;
	float near;
	float far;
} LTPerspectiveDescriptor;
LMMat4 ltPerspective(LTPerspectiveDescriptor* desc);

#endif /* _TRANSFORMATION_DEF_H */
