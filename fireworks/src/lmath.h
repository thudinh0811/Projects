#ifndef LINALG_DEF_H
#define LINALG_DEF_H

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

typedef struct LMVec2
{
	float x;
	float y;
} LMVec2;

typedef struct LMVec2i
{
	int x;
	int y;
} LMVec2i;

typedef struct LMVec3
{
	float x;
	float y;
	float z;
} LMVec3;

typedef struct LMVec3i
{
	int x;
	int y;
	int z;
} LMVec3i;

typedef struct LMVec4
{
	float x;
	float y;
	float z;
	float w;
} LMVec4;

typedef struct LMVec4i
{
	int x;
	int y;
	int z;
	int w;
} LMVec4i;

typedef struct LMMat2
{
	LMVec2 i;
	LMVec2 j;
} LMMat2;

typedef struct LMMat2i
{
	LMVec2i i;
	LMVec2i j;
} LMMat2i;

typedef struct LMMat3
{
	LMVec3 i;
	LMVec3 j;
	LMVec3 k;
} LMMat3;

typedef struct LMMat3i
{
	LMVec3i i;
	LMVec3i j;
	LMVec3i k;
} LMMat3i;

typedef struct LMMat4
{
	LMVec4 i;
	LMVec4 j;
	LMVec4 k;
	LMVec4 l;
} LMMat4;

typedef struct LMMat4i
{
	LMVec4i i;
	LMVec4i j;
	LMVec4i k;
	LMVec4i l;
} LMMat4i;

extern const LMMat4 	LMMat4_identity;
extern const LMMat4i 	LMMat4i_identity;
extern const LMMat3 	LMMat3_identity;
extern const LMMat3i 	LMMat3i_identity;
extern const LMMat2 	LMMat2_identity;
extern const LMMat2i 	LMMat2i_identity;

LMMat2 lmMat2Transpose(LMMat2 a);
LMMat2i lmMat2iTranspose(LMMat2i a);
LMMat3 lmMat3Transpose(LMMat3 a);
LMMat3i lmMat3iTranspose(LMMat3i a);
LMMat4 lmMat4Transpose(LMMat4 a);
LMMat4i lmMat4iTranspose(LMMat4i a);

LMMat2 lmMat2Inverse(LMMat2 a);
LMMat2i lmMat2iInverse(LMMat2i a);
LMMat3 lmMat3Inverse(LMMat3 a);
LMMat3i lmMat3iInverse(LMMat3i a);
LMMat4 lmMat4Inverse(LMMat4 a);
LMMat4i lmMat4iInverse(LMMat4i a);

LMMat2 lmMat2Cofators(LMMat2 a);
LMMat2i lmMat2iCofators(LMMat2i a);
LMMat3 lmMat3Cofators(LMMat3 a);
LMMat3i lmMat3iCofators(LMMat3i a);
LMMat4 lmMat4Cofators(LMMat4 a);
LMMat4i lmMat4iCofators(LMMat4i a);

float lmMat2Determinant(LMMat2 a);
float lmMat2iDeterminant(LMMat2i a);
float lmMat3Determinant(LMMat3 a);
float lmMat3iDeterminant(LMMat3i a);
float lmMat4Determinant(LMMat4 a);
float lmMat4iDeterminant(LMMat4i a);

LMVec2 	lmVec2Add 	(LMVec2 a,	LMVec2 b);
LMVec2i lmVec2iAdd	(LMVec2i a,	LMVec2i b);
LMVec3 	lmVec3Add 	(LMVec3 a,	LMVec3 b);
LMVec3i lmVec3iAdd	(LMVec3i a,	LMVec3i b);
LMVec4 	lmVec4Add 	(LMVec4 a,	LMVec4 b);
LMVec4i lmVec4iAdd	(LMVec4i a,	LMVec4i b);

LMMat2 	lmMat2Add		(LMMat2 a,	LMMat2 b);
LMMat2i lmMat2iAdd	(LMMat2i a,	LMMat2i b);
LMMat3 	lmMat3Add		(LMMat3 a,	LMMat3 b);
LMMat3i lmMat3iAdd	(LMMat3i a,	LMMat3i b);
LMMat4 	lmMat4Add		(LMMat4 a,	LMMat4 b);
LMMat4i lmMat4iAdd	(LMMat4i a,	LMMat4i b);

LMVec2 	lmVec2Sub		(LMVec2 a,	LMVec2 b);
LMVec2i lmVec2iSub	(LMVec2i a,	LMVec2i b);
LMVec3 	lmVec3Sub		(LMVec3 a,	LMVec3 b);
LMVec3i lmVec3iSub	(LMVec3i a,	LMVec3i b);
LMVec4 	lmVec4Sub		(LMVec4 a,	LMVec4 b);
LMVec4i lmVec4iSub	(LMVec4i a,	LMVec4i b);

LMMat2 	lmMat2Sub		(LMMat2 a,	LMMat2 b);
LMMat2i lmMat2iSub	(LMMat2i a,	LMMat2i b);
LMMat3 	lmMat3Sub		(LMMat3 a,	LMMat3 b);
LMMat3i lmMat3iSub	(LMMat3i a,	LMMat3i b);
LMMat4 	lmMat4Sub		(LMMat4 a,	LMMat4 b);
LMMat4i lmMat4iSub	(LMMat4i a, LMMat4i b);

float 	lmVec2Dot		(LMVec2 a,	LMVec2 b);
int 		lmVec2iDot	(LMVec2i a,	LMVec2i b);
float 	lmVec3Dot		(LMVec3 a,	LMVec3 b);
int 		lmVec3iDot	(LMVec3i a,	LMVec3i b);
float 	lmVec4Dot		(LMVec4 a,	LMVec4 b);
int			lmVec4iDot	(LMVec4i a,	LMVec4i b);

LMMat2 	lmMat2Mult		(LMMat2 a,	LMMat2 b);
LMMat2i lmMat2iMult	(LMMat2i a,	LMMat2i b);
LMMat3 	lmMat3Mult		(LMMat3 a,	LMMat3 b);
LMMat3i lmMat3iMult	(LMMat3i a,	LMMat3i b);
LMMat4 	lmMat4Mult		(LMMat4 a,	LMMat4 b);
LMMat4i	lmMat4iMult	(LMMat4i a,	LMMat4i b);

LMVec2 	lmMat2VecMult	(LMMat2 a,	LMVec2 b);
LMVec2i lmMat2iVecMult	(LMMat2i a,	LMVec2i b);
LMVec3 	lmMat3VecMult	(LMMat3 a,	LMVec3 b);
LMVec3i lmMat3iVecMult	(LMMat3i a, LMVec3i b);
LMVec4 	lmMat4VecMult	(LMMat4 a,	LMVec4 b);
LMVec4i	lmMat4iVecMult	(LMMat4i a, LMVec4i b);

LMVec2 	lmVec2MatMult	(LMVec2 a, 	LMMat2 b);
LMVec2i lmVec2iMatMult	(LMVec2i a, LMMat2i b);
LMVec3 	lmVec3MatMult	(LMVec3 a, 	LMMat3 b);
LMVec3i lmVec3iMatMult	(LMVec3i a, LMMat3i b);
LMVec4 	lmVec4MatMult	(LMVec4 a, 	LMMat4 b);
LMVec4i	lmVec4iMatMult	(LMVec4i a, LMMat4i b);

LMVec2 	lmVec2Scale		(LMVec2 a, float s);
LMVec2i lmVec2iScale	(LMVec2i a, int s);
LMVec3 	lmVec3Scale		(LMVec3 a, float s);
LMVec3i lmVec3iScale	(LMVec3i a, int  s);
LMVec4 	lmVec4Scale		(LMVec4 a, float s);
LMVec4i	lmVec4iScale	(LMVec4i a, int  s);

LMMat2 	lmMat2Scale	(LMMat2 a, float s);
LMMat2i lmMat2iScale	(LMMat2i a, int s);
LMMat3 	lmMat3Scale	(LMMat3 a, float s);
LMMat3i lmMat3iScale	(LMMat3i a, int s);
LMMat4 	lmMat4Scale	(LMMat4 a, float s);
LMMat4i	lmMat4iScale	(LMMat4i a, int  s);

LMMat2 	lmMat2EMult	(LMMat2  a,	LMMat2 b);
LMMat2i lmMat2iEMult	(LMMat2i a,	LMMat2i b);
LMMat3 	lmMat3EMult	(LMMat3	 a,	LMMat3 b);
LMMat3i lmMat3iEMult	(LMMat3i a,	LMMat3i b);
LMMat4 	lmMat4EMult	(LMMat4  a,	LMMat4 b);
LMMat4i	lmMat4iEMult	(LMMat4i a,	LMMat4i b);

LMVec2 	lmVec2Mult	(LMVec2  a,	LMVec2 b);
LMVec2i lmVec2iMult	(LMVec2i a,	LMVec2i b);
LMVec3 	lmVec3Mult	(LMVec3	 a,	LMVec3 b);
LMVec3i lmVec3iMult	(LMVec3i a,	LMVec3i b);
LMVec4 	lmVec4Mult	(LMVec4  a,	LMVec4 b);
LMVec4i	lmVec4iMult	(LMVec4i a,	LMVec4i b);

float lmVec2Magnitude (LMVec2 a);
float lmVec2iMagnitude (LMVec2i a);
float lmVec3Magnitude (LMVec3 a);
float lmVec3iMagnitude (LMVec3i a);
float lmVec4Magnitude (LMVec4 a);
float lmVec4iMagnitude (LMVec4i a);

float lmLerp(float a, float b, float t);

LMVec2 lmVec2Lerp (LMVec2 a, LMVec2 b, float t);
LMVec2i lmVec2iLerp (LMVec2i a, LMVec2i b, float t);
LMVec3 lmVec3Lerp (LMVec3 a, LMVec3 b, float t);
LMVec3i lmVec3iLerp (LMVec3i a, LMVec3i b, float t);
LMVec4 lmVec4Lerp (LMVec4 a, LMVec4 b, float t);
LMVec4i lmVec4iLerp (LMVec4i a, LMVec4i b, float t);

LMVec2 lmVec2Normalize (LMVec2 a);
LMVec3 lmVec3Normalize (LMVec3 a);
LMVec4 lmVec4Normalize (LMVec4 a);

float lmVec2CrossProduct(LMVec2 a, LMVec2 b);
int lmVec2iCrossProduct(LMVec2i a, LMVec2i b);
LMVec3 lmVec3CrossProduct(LMVec3 a, LMVec3 b);
LMVec3i lmVec3iCrossProduct(LMVec3i a, LMVec3i b);

int lmVec2Equals(LMVec2 a, LMVec2 b);
int lmVec2iEquals(LMVec2i a, LMVec2i b);
int lmVec3Equals(LMVec3 a, LMVec3 b);
int lmVec3iEquals(LMVec3i a, LMVec3i b);
int lmVec4Equals(LMVec4 a, LMVec4 b);
int lmVec4iEquals(LMVec4i a, LMVec4i b);

int lmMat2Equals(LMMat2 a, LMMat2 b);
int lmMat2iEquals(LMMat2i a, LMMat2i b);
int lmMat3Equals(LMMat3 a, LMMat3 b);
int lmMat3iEquals(LMMat3i a, LMMat3i b);
int lmMat4Equals(LMMat4 a, LMMat4 b);
int lmMat4iEquals(LMMat4i a, LMMat4i b);

void lmMat4Print(LMMat4 m);
void lmMat3Print(LMMat3 m);

int lmApproximate(float a, float b);

#endif /* LINALG_DEF_H */
