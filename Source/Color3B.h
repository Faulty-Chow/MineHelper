#ifndef _COLOR3B_
#define _COLOR3B_

typedef struct _Color3B
{
	BYTE r;
	BYTE g;
	BYTE b;
} Color3B;


//! helper macro that creates an Color3B type
static inline Color3B
	ccc3(const BYTE r, const BYTE g, const BYTE b)
{
	Color3B c = {r, g, b};
	return c;
}

/** returns true if both Color3B are equal. Otherwise it returns false.
 */
static inline bool c3BEqual(const Color3B &col1, const Color3B &col2)
{
    return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}



#endif