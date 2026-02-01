#include "Color.h"
#include <math.h>



MY_RGB Color::HSVtoRGB(float h, float s, float v) {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	int i = (int)floor(h / 60.0f) % 6;
	float f = (h / 60.0f) - floor(h / 60.0f);
	float p = v * (1.0f - s);
	float q = v * (1.0f - f * s);
	float t = v * (1.0f - (1.0f - f) * s);

	switch (i) {
	case 0:
		r = v;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = v;
		b = p;
		break;
	case 2:
		r = p;
		g = v;
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = v;
		break;
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	case 5:
		r = v;
		g = p;
		b = q;
		break;
	}
	return { (int)(r * 255), (int)(g * 255), (int)(b * 255) };
}