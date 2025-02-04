#include "lmath.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

const LMMat4 LMMat4_identity = 
{
	{1.f, 0.f, 0.f, 0.f},
	{0.f, 1.f, 0.f, 0.f},
	{0.f, 0.f, 1.f, 0.f},
	{0.f, 0.f, 0.f, 1.f}
};
const LMMat4i LMMat4i_identity =
{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};
const LMMat3 LMMat3_identity =
{
	{1.f, 0.f, 0.f},
	{0.f, 1.f, 0.f},
	{0.f, 0.f, 1.f}
};
const LMMat3i LMMat3i_identity =
{
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};
const LMMat2 LMMat2_identity = 
{
	{1.f, 0.f},
	{0.f, 1.f}
};
const LMMat2i LMMat2i_identity =
{
	{1, 0},
	{0, 1}
};

float lmMat2Determinant(LMMat2 a) {
	return (a.i.x * a.j.y) - (a.i.y * a.j.x);
}
float lmMat2iDeterminant(LMMat2i a) {
	return (a.i.x * a.j.y) - (a.i.y * a.j.x);
}

static void mat3SubMats(LMMat3 a, LMMat2 subs[]) {
		subs[0] = (LMMat2){{a.j.y, a.j.z}, {a.k.y, a.k.z}};
		subs[1] = (LMMat2){{a.i.y, a.i.z}, {a.k.y, a.k.z}};
		subs[2] = (LMMat2){{a.i.y, a.i.z}, {a.j.y, a.j.z}};
}
static void mat3iSubMats(LMMat3i a, LMMat2i subs[]) {
		subs[0] = (LMMat2i){{a.j.y, a.j.z}, {a.k.y, a.k.z}};
		subs[1] = (LMMat2i){{a.i.y, a.i.z}, {a.k.y, a.k.z}};
		subs[2] = (LMMat2i){{a.i.y, a.i.z}, {a.j.y, a.j.z}};
}

float lmMat3Determinant(LMMat3 a) {
	LMMat2 subMat[3];
	mat3SubMats(a, subMat);

	return (a.i.x * lmMat2Determinant(subMat[0]))
		- (a.j.x * lmMat2Determinant(subMat[1]))
		+ (a.k.x * lmMat2Determinant(subMat[2]));
}
float lmMat3iDeterminant(LMMat3i a) {
	LMMat2i subMat[3];
	mat3iSubMats(a, subMat);

	return (a.i.x * lmMat2iDeterminant(subMat[0]))
		- (a.j.x * lmMat2iDeterminant(subMat[1]))
		+ (a.k.x * lmMat2iDeterminant(subMat[2]));
}

static void mat4SubMats(LMMat4 a, LMMat3 subs[]) {
		subs[0] = (LMMat3){
			{a.j.y, a.j.z, a.j.w},
			{a.k.y, a.k.z, a.k.w},
			{a.l.y, a.l.z, a.l.w}};

		subs[1] = (LMMat3){
			{a.i.y, a.i.z, a.i.w},
			{a.k.y, a.k.z, a.k.w},
			{a.l.y, a.l.z, a.l.w}};

		subs[2] = (LMMat3){
			{a.i.y, a.i.z, a.i.w},
			{a.j.y, a.j.z, a.j.w},
			{a.l.y, a.l.z, a.l.w}};

		subs[3] = (LMMat3){
			{a.i.y, a.i.z, a.i.w},
			{a.j.y, a.j.z, a.j.w},
			{a.k.y, a.k.z, a.k.w}};
}
static void mat4iSubMats(LMMat4i a, LMMat3i subs[]) {
		subs[0] = (LMMat3i){
			{a.j.y, a.j.z, a.j.w},
			{a.k.y, a.k.z, a.k.w},
			{a.l.y, a.l.z, a.l.w}};

		subs[1] = (LMMat3i){
			{a.i.y, a.i.z, a.i.w},
			{a.k.y, a.k.z, a.k.w},
			{a.l.y, a.l.z, a.l.w}};

		subs[2] = (LMMat3i){
			{a.i.y, a.i.z, a.i.w},
			{a.j.y, a.j.z, a.j.w},
			{a.l.y, a.l.z, a.l.w}};

		subs[3] = (LMMat3i){
			{a.i.y, a.i.z, a.i.z},
			{a.j.y, a.j.z, a.j.z},
			{a.k.y, a.k.z, a.k.z}};
}
float lmMat4Determinant(LMMat4 a) {
	LMMat3 subMat[4];
	mat4SubMats(a, subMat);

	return (a.i.x * lmMat3Determinant(subMat[0]))
		- (a.j.x * lmMat3Determinant(subMat[1]))
		+ (a.k.x * lmMat3Determinant(subMat[2]))
		- (a.l.x * lmMat3Determinant(subMat[3]));
}
float lmMat4iDeterminant(LMMat4i a) {
	LMMat3i subMat[4];
	mat4iSubMats(a, subMat);

	return (a.i.x * lmMat3iDeterminant(subMat[0]))
		- (a.j.x * lmMat3iDeterminant(subMat[1]))
		+ (a.k.x * lmMat3iDeterminant(subMat[2]))
		- (a.l.x * lmMat3iDeterminant(subMat[3]));
}

static int getSign(int i, int j) { return powf(-1, (i + j)); }

LMMat2 lmMat2Cofators(LMMat2 a) {
	return(LMMat2) {
		{getSign(0,0) * a.j.y, getSign(0,1) * a.j.x},
		{getSign(1,0) * a.i.y, getSign(1,1) * a.i.x}};
}
LMMat2i lmMat2iCofators(LMMat2i a) {
	return(LMMat2i) {
		{getSign(0,0) * a.j.y, getSign(0,1) * a.j.x},
		{getSign(1,0) * a.i.y, getSign(1,1) * a.i.x}};
}

static LMMat2 mat3SubMatrix(LMMat3 a, int i, int j) {
	float* vals = (float*)&a;
	float c[4];
	int ind = 0;
	for (int col = 0; col < 3; col++) {
		if (col == j) { continue; }
		for (int row = 0; row < 3; row++) {
			if (row == i || col == j) { continue; }
			int t = (col * 3) + row;
			assert(t < 9);
			c[ind++] = vals[t];
		}
	}

	return (LMMat2) {
		{c[0], c[1]},
		{c[2], c[3]}};
}
static LMMat2i mat3iSubMatrix(LMMat3i a, int i, int j) {
	int* vals = (int*)&a;
	int c[4];
	int ind = 0;
	for (int col = 0; col < 3; col++) {
		if (col == j) { continue; }
		for (int row = 0; row < 3; row++) {
			if (row == i || col == j) { continue; }
			int t = (col * 3) + row;
			assert(t < 9);
			c[ind++] = vals[t];
		}
	}

	return (LMMat2i) {
		{c[0], c[1]},
		{c[2], c[3]}};
}
LMMat3 lmMat3Cofators(LMMat3 a) {
#define Entry(r,c) getSign(r,c) * lmMat2Determinant(mat3SubMatrix(a, r, c))
	return (LMMat3) {
		{ Entry(0,0), Entry(1,0), Entry(2,0) },
		{ Entry(0,1), Entry(1,1), Entry(2,1) },
		{ Entry(0,2), Entry(1,2), Entry(2,2) },
	};
#undef Entry
}
LMMat3i lmMat3iCofators(LMMat3i a) {
#define Entry(r,c) getSign(r,c) * lmMat2iDeterminant(mat3iSubMatrix(a, r, c))
	return (LMMat3i) {
		{ Entry(0,0), Entry(1,0), Entry(2,0) },
		{ Entry(0,1), Entry(1,1), Entry(2,1) },
		{ Entry(0,2), Entry(1,2), Entry(2,2) },
	};
#undef Entry
}
static LMMat3 mat4SubMatrix(LMMat4 a, int i, int j) {
	float* vals = (float*)&a;
	float c[9];
	int ind = 0;
	for (int col = 0; col < 4; col++) {
		if (col == j) { continue; }
		for (int row = 0; row < 4; row++) {
			if (row == i || col == j) { continue; }
			int t = (col * 4) + row;
			assert(t < 16);
			c[ind++] = vals[t];
		}
	}

	assert(ind == 9);
	return (LMMat3) {
		{c[0], c[1], c[2]},
		{c[3], c[4], c[5]},
		{c[6], c[7], c[8]}};
}
static LMMat3i mat4iSubMatrix(LMMat4i a, int i, int j) {
	int* vals = (int*)&a;
	int c[9];
	int ind = 0;
	for (int col = 0; col < 4; col++) {
		if (col == j) { continue; }
		for (int row = 0; row < 4; row++) {
			if (row == i || col == j) { continue; }
			int t = (col * 4) + row;
			assert(t < 16);
			c[ind++] = vals[t];
		}
	}

	assert(ind == 9);

	return (LMMat3i) {
		{c[0], c[1], c[2]},
		{c[3], c[4], c[5]},
		{c[6], c[7], c[8]}};
}
LMMat4 lmMat4Cofators(LMMat4 a) {
#define Entry(r,c) getSign(r,c) * lmMat3Determinant(mat4SubMatrix(a, r, c))
	return (LMMat4) {
		{ Entry(0,0), Entry(1,0), Entry(2,0), Entry(3,0) },
		{ Entry(0,1), Entry(1,1), Entry(2,1), Entry(3,1) },
		{ Entry(0,2), Entry(1,2), Entry(2,2), Entry(3,2) },
		{ Entry(0,3), Entry(1,3), Entry(2,3), Entry(3,3) },
	};
#undef Entry
}
LMMat4i lmMat4iCofators(LMMat4i a) {
#define Entry(r,c) getSign(r,c) * lmMat3iDeterminant(mat4iSubMatrix(a, r, c))
	return (LMMat4i) {
		{ Entry(0,0), Entry(1,0), Entry(2,0), Entry(3,0) },
		{ Entry(0,1), Entry(1,1), Entry(2,1), Entry(3,1) },
		{ Entry(0,2), Entry(1,2), Entry(2,2), Entry(3,2) },
		{ Entry(0,3), Entry(1,3), Entry(2,3), Entry(3,3) },
	};
#undef Entry
}

// Mat Inverse
LMMat2 lmMat2Inverse(LMMat2 a) {
	float determinant = lmMat2Determinant(a);
	assert(determinant != 0);
	return lmMat2Scale(lmMat2Transpose(lmMat2Cofators(a)), 1.0f / determinant);
}
LMMat2i lmMat2iInverse(LMMat2i a) {
	float determinant = lmMat2iDeterminant(a);
	assert(determinant != 0);
	return lmMat2iScale(lmMat2iTranspose(lmMat2iCofators(a)), 1.0f / determinant);
}

LMMat3 lmMat3Inverse(LMMat3 a) {
	float determinant = lmMat3Determinant(a);
	assert(determinant != 0);
	return lmMat3Scale(lmMat3Transpose(lmMat3Cofators(a)), 1.0f / determinant);
}
LMMat3i lmMat3iInverse(LMMat3i a) {
	float determinant = lmMat3iDeterminant(a);
	assert(determinant != 0);
	return lmMat3iScale(lmMat3iTranspose(lmMat3iCofators(a)), 1.0f / determinant);
}

LMMat4 lmMat4Inverse(LMMat4 a) {
	float determinant = lmMat4Determinant(a);
	assert(determinant != 0);
	LMMat4 cf = lmMat4Cofators(a);
	return lmMat4Scale(lmMat4Transpose(cf), 1.0f / determinant);
}
LMMat4i lmMat4iInverse(LMMat4i a) {
	float determinant = lmMat4iDeterminant(a);
	assert(determinant != 0);
	return lmMat4iScale(lmMat4iTranspose(lmMat4iCofators(a)), 1.0f / determinant);
}

LMMat2 lmMat2Transpose(LMMat2 a) {
	return (LMMat2){
		{a.i.x, a.j.x},
		{a.i.y, a.j.y}};
}
LMMat2i lmMat2iTranspose(LMMat2i a){
	return (LMMat2i){
		{a.i.x, a.j.x},
		{a.i.y, a.j.y}};
}

LMMat3 lmMat3Transpose(LMMat3 a){
	return (LMMat3){
		{a.i.x, a.j.x, a.k.x},
		{a.i.y, a.j.y, a.k.y},
		{a.i.z, a.j.z, a.k.z}};
}
LMMat3i lmMat3iTranspose(LMMat3i a){
	return (LMMat3i){
		{a.i.x, a.j.x, a.k.x},
		{a.i.y, a.j.y, a.k.y},
		{a.i.z, a.j.z, a.k.z}};
}

LMMat4 lmMat4Transpose(LMMat4 a){
	return (LMMat4){
		{a.i.x, a.j.x, a.k.x, a.l.x},
		{a.i.y, a.j.y, a.k.y, a.l.y},
		{a.i.z, a.j.z, a.k.z, a.l.z},
		{a.i.w, a.j.w, a.k.w, a.l.w}};
}
LMMat4i lmMat4iTranspose(LMMat4i a){
	return (LMMat4i){
		{a.i.x, a.j.x, a.k.x, a.l.x},
		{a.i.y, a.j.y, a.k.y, a.l.y},
		{a.i.z, a.j.z, a.k.z, a.l.z},
		{a.i.w, a.j.w, a.k.w, a.l.w}};
}

// Vec2 Addition
LMVec2 	lmVec2Add	(LMVec2 a,	LMVec2 b)
{
	LMVec2 v = {a.x + b.x, a.y + b.y};
	return v;
}
LMVec2i lmVec2iAdd	(LMVec2i a,	LMVec2i b)
{
	LMVec2i v = {a.x + b.x, a.y + b.y};
	return v;
}

// Vec3 Addition
LMVec3 	lmVec3Add	(LMVec3 a,	LMVec3 b)
{
	LMVec3 v = {a.x + b.x, a.y + b.y, a.z + b.z};
	return v;
}
LMVec3i lmVec3iAdd	(LMVec3i a,	LMVec3i b)
{
	LMVec3i v = {a.x + b.x, a.y + b.y, a.z + b.z};
	return v;
}

// Vec4 Addition
LMVec4 	lmVec4Add	(LMVec4 a,	LMVec4 b)
{
	LMVec4 v = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	return v;
}
LMVec4i lmVec4iAdd	(LMVec4i a,	LMVec4i b)
{
	LMVec4i v = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	return v;
}

// Mat2 Addition
LMMat2 	lmMat2Add	(LMMat2 a,	LMMat2 b)
{
	LMMat2 m = {lmVec2Add(a.i, b.i), lmVec2Add(a.j, b.j)};
	return m;
}
LMMat2i lmMat2iAdd	(LMMat2i a,	LMMat2i b)
{
	LMMat2i m = {lmVec2iAdd(a.i, b.i), lmVec2iAdd(a.j, b.j)};
	return m;
}

// Mat3 Addition
LMMat3 	lmMat3Add	(LMMat3 a,	LMMat3 b)
{
	LMMat3 m = {lmVec3Add(a.i, b.i), lmVec3Add(a.j, b.j), lmVec3Add(a.k, b.k)};
	return m;
}
LMMat3i lmMat3iAdd	(LMMat3i a,	LMMat3i b)
{
	LMMat3i m = {lmVec3iAdd(a.i, b.i), lmVec3iAdd(a.j, b.j), lmVec3iAdd(a.k, b.k)};
	return m;
}

// Mat4 Addition
LMMat4 	lmMat4Add	(LMMat4 a,	LMMat4 b)
{
	LMMat4 m = {lmVec4Add(a.i, b.i), lmVec4Add(a.j, b.j), lmVec4Add(a.k, b.k), lmVec4Add(a.l, b.l)};
	return m;
}
LMMat4i lmMat4iAdd	(LMMat4i a,	LMMat4i b)
{
	LMMat4i m = {lmVec4iAdd(a.i, b.i), lmVec4iAdd(a.j, b.j), lmVec4iAdd(a.k, b.k), lmVec4iAdd(a.l, b.l)};
	return m;
}

// Vec2 Subtraction
LMVec2 	lmVec2Sub	(LMVec2 a,	LMVec2 b)
{
	LMVec2 v = { a.x - b.x, a.y - b.y };
	return v;
}
LMVec2i lmVec2iSub	(LMVec2i a,	LMVec2i b)
{
	LMVec2i v = { a.x - b.x, a.y - b.y };
	return v;
}

// Vec3 Subtraction
LMVec3 	lmVec3Sub	(LMVec3 a,	LMVec3 b)
{
	LMVec3 v = { a.x - b.x, a.y - b.y, a.z - b.z };
	return v;
}
LMVec3i lmVec3iSub	(LMVec3i a,	LMVec3i b)
{
	LMVec3i v = {a.x - b.x, a.y - b.y, a.z - b.z };
	return v;
}

// Vec4 Subtraction
LMVec4 	lmVec4Sub	(LMVec4 a,	LMVec4 b)
{
	LMVec4 v = { a.x -b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return v;
}
LMVec4i lmVec4iSub	(LMVec4i a,	LMVec4i b)
{
	LMVec4i v = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return v;
}

// Mat2 Subtraction
LMMat2 	lmMat2Sub	(LMMat2 a,	LMMat2 b)
{
	LMMat2 m = { lmVec2Sub(a.i, b.i), lmVec2Sub(a.j, b.j) };
	return m;
}
LMMat2i m_sub_m2i	(LMMat2i a,	LMMat2i b)
{
	LMMat2i m = { lmVec2iSub(a.i, b.i), lmVec2iSub(a.j, b.j) };
	return m;
}

// Mat3 Subtraction
LMMat3 	lmMat3Sub	(LMMat3 a,	LMMat3 b)
{
	LMMat3 m = { lmVec3Sub(a.i, b.i), lmVec3Sub(a.j, b.j), lmVec3Sub(a.k, b.k) };
	return m;
}
LMMat3i lmMat3iSub	(LMMat3i a,	LMMat3i b)
{
	LMMat3i m = { lmVec3iSub(a.i, b.i), lmVec3iSub(a.j, b.j), lmVec3iSub(a.k, b.k) };
	return m;
}

// Mat4 Subtraction
LMMat4 	lmMat4Sub	(LMMat4 a,	LMMat4 b)
{
	LMMat4 m = { lmVec4Sub(a.i, b.i), lmVec4Sub(a.j, b.j), lmVec4Sub(a.k, b.k), lmVec4Sub(a.l, b.l) };
	return m;
}
LMMat4i lmMat4iSub	(LMMat4i a, LMMat4i b)
{
	LMMat4i m = { lmVec4iSub(a.i, b.i), lmVec4iSub(a.j, b.j), lmVec4iSub(a.k, b.k), lmVec4iSub(a.l, b.l) };
	return m;
}

float 	lmVec2Dot		(LMVec2 a,	LMVec2 b) 	{ return a.x * b.x + a.y * b.y; }
int 		lmVec2iDot	(LMVec2i a,	LMVec2i b)	{ return a.x * b.x + a.y * b.y; }
float 	lmVec3Dot		(LMVec3 a,	LMVec3 b)	{ return a.x * b.x + a.y * b.y + a.z * b.z; }
int 		lmVec3iDot	(LMVec3i a,	LMVec3i b)	{ return a.x * b.x + a.y * b.y + a.z * b.z; }
float 	lmVec4Dot		(LMVec4 a,	LMVec4 b)	{ return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
int			lmVec4iDot	(LMVec4i a,	LMVec4i b)	{ return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; } 

// Mat2 Multiplication
LMMat2 	lmMat2Mult	(LMMat2 a,	LMMat2 b)
{
	LMVec2 a1 = { a.i.x, a.j.x };
	LMVec2 a2 = { a.i.y, a.j.y };
	LMMat2 m = 
	{
		{ lmVec2Dot(a1, b.i), lmVec2Dot(a2, b.j) },
		{ lmVec2Dot(a1, b.i), lmVec2Dot(a2, b.j) }
	};
	return m;
}
LMMat2i lmMat2iMult	(LMMat2i a,	LMMat2i b)
{
	LMMat2i m = 
	{
		{ lmVec2iDot(a.i, b.i), lmVec2iDot(a.i, b.j) },
		{ lmVec2iDot(a.j, b.i), lmVec2iDot(a.j, b.j) }
	};
	return m;
}

// Mat3 Multiplication
LMMat3 	lmMat3Mult	(LMMat3 a,	LMMat3 b)
{
	LMVec3 a1 = { a.i.x, a.j.x, a.k.x };
	LMVec3 a2 = { a.i.y, a.j.y, a.k.y };
	LMVec3 a3 = { a.i.z, a.j.z, a.k.z };

	LMMat3 m =
	{
		{ lmVec3Dot(a1, b.i), lmVec3Dot(a2, b.i), lmVec3Dot(a3, b.i) },
		{ lmVec3Dot(a1, b.j), lmVec3Dot(a2, b.j), lmVec3Dot(a3, b.j) },
		{ lmVec3Dot(a1, b.k), lmVec3Dot(a2, b.k), lmVec3Dot(a3, b.k) },
	};
	return m;
}
LMMat3i lmMat3iMult	(LMMat3i a,	LMMat3i b)
{
	LMVec3i a1 = { a.i.x, a.j.x, a.k.x };
	LMVec3i a2 = { a.i.y, a.j.y, a.k.y };
	LMVec3i a3 = { a.i.z, a.j.z, a.k.z };

	LMMat3i m =
	{
		{ lmVec3iDot(a1, b.i), lmVec3iDot(a2, b.i), lmVec3iDot(a3, b.i) },
		{ lmVec3iDot(a1, b.j), lmVec3iDot(a2, b.j), lmVec3iDot(a3, b.j) },
		{ lmVec3iDot(a1, b.k), lmVec3iDot(a2, b.k), lmVec3iDot(a3, b.k) },
	};
	return m;
}

// Mat4 Multiplication
LMMat4 	lmMat4Mult	(LMMat4 a,	LMMat4 b)
{
	LMVec4 a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	LMVec4 a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	LMVec4 a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	LMVec4 a4 = { a.i.w, a.j.w, a.k.w, a.l.w };

	LMMat4 m =
	{
		{ lmVec4Dot(a1, b.i), lmVec4Dot(a2, b.i), lmVec4Dot(a3, b.i), lmVec4Dot(a4, b.i) },
		{ lmVec4Dot(a1, b.j), lmVec4Dot(a2, b.j), lmVec4Dot(a3, b.j), lmVec4Dot(a4, b.j) },
		{ lmVec4Dot(a1, b.k), lmVec4Dot(a2, b.k), lmVec4Dot(a3, b.k), lmVec4Dot(a4, b.k) },
		{ lmVec4Dot(a1, b.l), lmVec4Dot(a2, b.l), lmVec4Dot(a3, b.l), lmVec4Dot(a4, b.l) },
	};
	return m;
}
LMMat4i	lmMat4iMult	(LMMat4i a,	LMMat4i b)
{
	LMVec4i a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	LMVec4i a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	LMVec4i a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	LMVec4i a4 = { a.i.w, a.j.w, a.k.w, a.l.w };

	LMMat4i m =
	{
		{ lmVec4iDot(a1, b.i), lmVec4iDot(a2, b.i), lmVec4iDot(a3, b.i), lmVec4iDot(a4, b.i) },
		{ lmVec4iDot(a1, b.j), lmVec4iDot(a2, b.j), lmVec4iDot(a3, b.j), lmVec4iDot(a4, b.j) },
		{ lmVec4iDot(a1, b.k), lmVec4iDot(a2, b.k), lmVec4iDot(a3, b.k), lmVec4iDot(a4, b.k) },
		{ lmVec4iDot(a1, b.l), lmVec4iDot(a2, b.l), lmVec4iDot(a3, b.l), lmVec4iDot(a4, b.l) },
	};
	return m;
}

// Matrix * Vector Multiplication
LMVec2 	lmMat2VecMult	(LMMat2 a,	LMVec2 b)
{
	LMVec2 a1 = { a.i.x, a.j.x };
	LMVec2 a2 = { a.i.y, a.j.y };
	LMVec2 v = { lmVec2Dot(a1, b), lmVec2Dot(a2, b) };
	return v;
}
LMVec2i lmMat2iVecMult	(LMMat2i a,	LMVec2i b)
{
	LMVec2i a1 = { a.i.x, a.j.x };
	LMVec2i a2 = { a.i.y, a.j.y };
	LMVec2i v = { lmVec2iDot(a1, b), lmVec2iDot(a2, b) };
	return v;
}

LMVec3 	lmMat3VecMult	(LMMat3 a,	LMVec3 b)
{
	LMVec3 a1 = { a.i.x, a.j.x, a.k.x };
	LMVec3 a2 = { a.i.y, a.j.y, a.k.y };
	LMVec3 a3 = { a.i.z, a.j.z, a.k.z };
	LMVec3 v = { lmVec3Dot(a1, b), lmVec3Dot(a2, b), lmVec3Dot(a3, b) };
	return v;
}
LMVec3i lmMat3iVecMult	(LMMat3i a, LMVec3i b)
{
	LMVec3i a1 = { a.i.x, a.j.x, a.k.x };
	LMVec3i a2 = { a.i.y, a.j.y, a.k.y };
	LMVec3i a3 = { a.i.z, a.j.z, a.k.z };
	LMVec3i v = { lmVec3iDot(a1, b), lmVec3iDot(a2, b), lmVec3iDot(a3, b) };
	return v;
}

LMVec4 	lmMat4VecMult	(LMMat4 a,	LMVec4 b)
{
	LMVec4 a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	LMVec4 a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	LMVec4 a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	LMVec4 a4 = { a.i.w, a.j.w, a.k.w, a.l.w };
	LMVec4 v = { lmVec4Dot(a1, b), lmVec4Dot(a2, b), lmVec4Dot(a3, b), lmVec4Dot(a4, b) };
	return v;
}
LMVec4i	lmMat4iVecMult	(LMMat4i a, LMVec4i b)
{
	LMVec4i a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	LMVec4i a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	LMVec4i a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	LMVec4i a4 = { a.i.w, a.j.w, a.k.w, a.l.w };
	LMVec4i v = { lmVec4iDot(a1, b), lmVec4iDot(a2, b), lmVec4iDot(a3, b), lmVec4iDot(a4, b) };
	return v;
}

LMVec2 	lmVec2MatMult	(LMVec2 a, 	LMMat2 b)
{
	LMVec2 v = { lmVec2Dot(a, b.i), lmVec2Dot(a, b.j) };
	return v;
}
LMVec2i lmVec2iMatMult	(LMVec2i a, LMMat2i b)
{
	LMVec2i v = { lmVec2iDot(a, b.i), lmVec2iDot(a, b.j) };
	return v;
}
LMVec3 	lmVec3MatMult	(LMVec3 a, 	LMMat3 b)
{
	LMVec3 v = { lmVec3Dot(a, b.i), lmVec3Dot(a, b.j), lmVec3Dot(a, b.k) };
	return v;
}
LMVec3i lmVec3iMatMult	(LMVec3i a, LMMat3i b)
{
	LMVec3i v = { lmVec3iDot(a, b.i), lmVec3iDot(a, b.j), lmVec3iDot(a, b.k) };
	return v;
}
LMVec4 	lmVec4MatMult	(LMVec4 a, 	LMMat4 b)
{
	LMVec4 v = { lmVec4Dot(a, b.i), lmVec4Dot(a, b.j), lmVec4Dot(a, b.k), lmVec4Dot(a, b.l) };
	return v;
}
LMVec4i	lmVec4iMatMult	(LMVec4i a, LMMat4i b)
{
	LMVec4i v = { lmVec4iDot(a, b.i), lmVec4iDot(a, b.j), lmVec4iDot(a, b.k), lmVec4iDot(a, b.l) };
	return v;
}

LMVec2 	lmVec2Scale	(LMVec2 a, float s)
{
	LMVec2 v = { a.x * s, a.y * s };
	return v;
}
LMVec2i lmVec2iScale	(LMVec2i a, int s)
{
	LMVec2i v = { a.x * s, a.y * s };
	return v;
}
LMVec3 	lmVec3Scale	(LMVec3 a, float s)
{
	LMVec3 v = { a.x * s, a.y * s, a.z * s };
	return v;
}
LMVec3i lmVec3iScale	(LMVec3i a, int  s)
{
	LMVec3i v = { a.x * s, a.y * s, a.z * s };
	return v;
}
LMVec4 	lmVec4Scale	(LMVec4 a, float s)
{
	LMVec4 v = { a.x * s, a.y * s, a.z * s, a.w * s };
	return v;
}
LMVec4i	lmVec4iScale	(LMVec4i a, int  s)
{
	LMVec4i v = { a.x * s, a.y * s, a.z * s, a.w * s };
	return v;
}

LMMat2 	lmMat2Scale	(LMMat2 a, float s)
{
	LMMat2 m = 
	{
		lmVec2Scale(a.i, s),
		lmVec2Scale(a.j, s)
	};
	return m;
}
LMMat3 	lmMat3Scale	(LMMat3 a, float s)
{
	LMMat3 m = 
	{
		lmVec3Scale(a.i, s),
		lmVec3Scale(a.j, s),
		lmVec3Scale(a.k, s)
	};
	return m;
}
LMMat4 	lmMat4Scale	(LMMat4 a, float s)
{
	LMMat4 m = 
	{
		lmVec4Scale(a.i, s),
		lmVec4Scale(a.j, s),
		lmVec4Scale(a.k, s),
		lmVec4Scale(a.l, s)
	};
	return m;
}
LMMat2i lmMat2iScale	(LMMat2i a, int s)
{
	LMMat2i m =
	{
		lmVec2iScale(a.i, s),
		lmVec2iScale(a.j, s)
	};
	return m;
}
LMMat3i lmMat3iScale	(LMMat3i a, int s)
{
	LMMat3i m = 
	{
		lmVec3iScale(a.i, s),
		lmVec3iScale(a.j, s),
		lmVec3iScale(a.k, s),
	};
	return m;
}
LMMat4i	lmMat4iScale	(LMMat4i a, int s)
{
	LMMat4i m = 
	{
		lmVec4iScale(a.i, s),
		lmVec4iScale(a.j, s),
		lmVec4iScale(a.k, s),
		lmVec4iScale(a.l, s)
	};
	return m;
}

LMMat2 	lmMat2EMult	(LMMat2  a,	LMMat2 b)
{
	LMMat2 m = 
	{
		lmVec2Mult(a.i, b.i),
		lmVec2Mult(a.j, b.j)
	};
	return m;
}
LMMat2i lmMat2iEMult	(LMMat2i a,	LMMat2i b)
{
	LMMat2i m = 
	{
		lmVec2iMult(a.i, b.i),
		lmVec2iMult(a.j, b.j)
	};
	return m;
}
LMMat3 	lmMat3EMult	(LMMat3	 a,	LMMat3 b)
{
	LMMat3 m = 
	{
		lmVec3Mult(a.i, b.i),
		lmVec3Mult(a.j, b.j),
		lmVec3Mult(a.k, b.k)
	};
	return m;
}
LMMat3i lmMat3iEMult	(LMMat3i a,	LMMat3i b)
{
	LMMat3i m = 
	{
		lmVec3iMult(a.i, b.i),
		lmVec3iMult(a.j, b.j),
		lmVec3iMult(a.k, b.k)
	};
	return m;
}
LMMat4 	lmMat4EMult	(LMMat4  a,	LMMat4 b)
{
	LMMat4 m = 
	{
		lmVec4Mult(a.i, b.i),
		lmVec4Mult(a.j, b.j),
		lmVec4Mult(a.k, b.k),
		lmVec4Mult(a.l, b.l)
	};
	return m;
}
LMMat4i	lmMat4iEMult	(LMMat4i a,	LMMat4i b)
{
	LMMat4i m = 
	{
		lmVec4iMult(a.i, b.i),
		lmVec4iMult(a.j, b.j),
		lmVec4iMult(a.k, b.k),
		lmVec4iMult(a.l, b.l)
	};
	return m;
}

LMVec2 	lmVec2Mult	(LMVec2  a,	LMVec2 b)
{
	LMVec2 v = { a.x * b.x, a.y * b.y };
	return v;
}
LMVec2i lmVec2iMult	(LMVec2i a,	LMVec2i b)
{
	LMVec2i v = { a.x * b.x, a.y * b.y };
	return v;
}
LMVec3 	lmVec3Mult	(LMVec3	 a,	LMVec3 b)
{
	LMVec3 v = { a.x * b.x, a.y * b.y, a.z * b.z };
	return v;
}
LMVec3i lmVec3iMult	(LMVec3i a,	LMVec3i b)
{
	LMVec3i v = { a.x * b.x, a.y * b.y, a.z * b.z };
	return v;
}
LMVec4 	lmVec4Mult	(LMVec4  a,	LMVec4 b)
{
	LMVec4 v = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return v;
}
LMVec4i	lmVec4iMult	(LMVec4i a,	LMVec4i b)
{
	LMVec4i v = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return v;
}

float lmVec2Magnitude (LMVec2 a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
float lmVec2iMagnitude (LMVec2i a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

float lmVec3Magnitude (LMVec3 a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}
float lmVec3iMagnitude (LMVec3i a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

float lmVec4Magnitude (LMVec4 a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}
float lmVec4iMagnitude (LMVec4i a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

float lmLerp(float a, float b, float t) {
		return a + (t * (b - a));
}

LMVec2 lmVec2Lerp (LMVec2 a, LMVec2 b, float t) {
	return (LMVec2) {
		.x = a.x + (t * (b.x - a.x)),
		.y = a.y + (t * (b.y - a.y))
	};
}
LMVec2i lmVec2iLerp (LMVec2i a, LMVec2i b, float t) {
	return (LMVec2i) {
		.x = a.x + (t * (b.x - a.x)),
		.y = a.y + (t * (b.y - a.y))
	};
}

LMVec3 lmVec3Lerp (LMVec3 a, LMVec3 b, float t) {
	return (LMVec3) {
		.x = a.x + (t * (b.x - a.x)),
		.y = a.y + (t * (b.y - a.y)),
		.z = a.z + (t * (b.z - a.z))
	};
}
LMVec3i lmVec3iLerp (LMVec3i a, LMVec3i b, float t) {
	return (LMVec3i) {
		.x = a.x + (t * (b.x - a.x)),
		.y = a.y + (t * (b.y - a.y)),
		.z = a.z + (t * (b.z - a.z))
	};
}
LMVec4 lmVec4Lerp (LMVec4 a, LMVec4 b, float t) {
	return (LMVec4) {
		.x = a.x + (t * (b.x - a.x)),
		.y = a.y + (t * (b.y - a.y)),
		.z = a.z + (t * (b.z - a.z)),
		.w = a.w + (t * (b.w - a.w))
	};
}
LMVec4i lmVec4iLerp (LMVec4i a, LMVec4i b, float t) {
	return (LMVec4i) {
		.x = a.x + (t * (b.x - a.x)),
		.y = a.y + (t * (b.y - a.y)),
		.z = a.z + (t * (b.z - a.z)),
		.w = a.w + (t * (b.w - a.w))
	};
}

LMVec2 lmVec2Normalize (LMVec2 a) {
	float mag = lmVec2Magnitude(a);
	return (LMVec2){ .x = a.x / mag, .y = a.y / mag };
}

LMVec3 lmVec3Normalize (LMVec3 a) {
	float mag = lmVec3Magnitude(a);
	return (LMVec3){ .x = a.x / mag, .y = a.y / mag, .z = a.z / mag };
}

LMVec4 lmVec4Normalize (LMVec4 a) {
	float mag = lmVec4Magnitude(a);
	return (LMVec4){ .x = a.x / mag, .y = a.y / mag, .z = a.z / mag, .w = a.w / mag };
}

float lmVec2CrossProduct(LMVec2 a, LMVec2 b) {
	return a.x * b.y - a.y * b.x;
}
int lmVec2iCrossProduct(LMVec2i a, LMVec2i b) {
	return a.x * b.y - a.y * b.x;
}

LMVec3 lmVec3CrossProduct(LMVec3 a, LMVec3 b) {
	LMVec3 r = { .x = lmVec2CrossProduct((LMVec2){a.y, a.z}, (LMVec2){b.y, b.z}),
							 .y = -lmVec2CrossProduct((LMVec2){a.x, a.z}, (LMVec2){b.x, b.z}),
							 .z = lmVec2CrossProduct((LMVec2){a.x, a.y}, (LMVec2){b.x, b.y})};
	return r;
}
LMVec3i lmVec3iCrossProduct(LMVec3i a, LMVec3i b) {
	LMVec3i r = {.x = lmVec2iCrossProduct((LMVec2i){a.y, a.z}, (LMVec2i){b.y, b.z}),
							 .y = -lmVec2iCrossProduct((LMVec2i){a.x, a.z}, (LMVec2i){b.x, b.z}),
							 .z = lmVec2iCrossProduct((LMVec2i){a.x, a.y}, (LMVec2i){b.x, b.y})};
	return r;
}

int lmVec2Equals(LMVec2 a, LMVec2 b) {
	return lmApproximate(a.x, b.x) && lmApproximate(a.y, b.y);
}
int lmVec2iEquals(LMVec2i a, LMVec2i b) {
	return a.x == b.x && a.y == b.y;
}
int lmVec3Equals(LMVec3 a, LMVec3 b) { 
	return lmApproximate(a.x, b.x) && lmApproximate(a.y, b.y) && lmApproximate(a.z, b.z);
}
int lmVec3iEquals(LMVec3i a, LMVec3i b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
int lmVec4Equals(LMVec4 a, LMVec4 b) {
	return lmApproximate(a.x, b.x) && lmApproximate(a.y, b.y) && lmApproximate(a.z, b.z) && lmApproximate(a.w, b.w);
}
int lmVec4iEquals(LMVec4i a, LMVec4i b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

int lmMat2Equals(LMMat2 a, LMMat2 b) {
	return lmVec2Equals(a.i, b.i) && lmVec2Equals(a.j, b.j);
}
int lmMat2iEquals(LMMat2i a, LMMat2i b) {
	return lmVec2iEquals(a.i, b.i) && lmVec2iEquals(a.j, b.j);
}
int lmMat3Equals(LMMat3 a, LMMat3 b) {
	return lmVec3Equals(a.i, b.i) && lmVec3Equals(a.j, b.j) && lmVec3Equals(a.k, b.k);
}
int lmMat3iEquals(LMMat3i a, LMMat3i b) {
	return lmVec3iEquals(a.i, b.i) && lmVec3iEquals(a.j, b.j) && lmVec3iEquals(a.k, b.k);
}
int lmMat4Equals(LMMat4 a, LMMat4 b) {
	return lmVec4Equals(a.i, b.i) && lmVec4Equals(a.j, b.j)
		&& lmVec4Equals(a.k, b.k) && lmVec4Equals(a.l, b.l);
}
int lmMat4iEquals(LMMat4i a, LMMat4i b) {
	return lmVec4iEquals(a.i, b.i) && lmVec4iEquals(a.j, b.j)
		&& lmVec4iEquals(a.k, b.k) && lmVec4iEquals(a.l, b.l);
}

int lmApproximate(float a, float b) {
	return (fabs(a-b) < 0.0001f) ? 1 : 0;
}

void lmMat3Print(LMMat3 m)
{
	printf(	"[ %f %f %f ]\n"
			"[ %f %f %f ]\n"
			"[ %f %f %f ]\n",
			m.i.x, m.j.x, m.k.x,
			m.i.y, m.j.y, m.k.y,
			m.i.z, m.j.z, m.k.z);
}

void lmMat4Print(LMMat4 m)
{
	printf(	"[ %f %f %f %f ]\n"
			"[ %f %f %f %f ]\n"
			"[ %f %f %f %f ]\n"
			"[ %f %f %f %f ]\n", 
			m.i.x, m.j.x, m.k.x, m.l.x,
			m.i.y, m.j.y, m.k.y, m.l.y, 
			m.i.z, m.j.z, m.k.z, m.l.z, 
			m.i.w, m.j.w, m.k.w, m.l.w);
}
