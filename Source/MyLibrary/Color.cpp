#include "Color.h"
#include <algorithm>
#include <math.h>
#include "../Play/Area.h"

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

MY_HSV Color::RGBtoHSV(MY_RGB rgb)
{
	float r = rgb.red / 255.0f;
	float g= rgb.green / 255.0f;
	float b= rgb.blue / 255.0f;

	float maxVal = max(r, max(g, b));
	float minVal = min(r, min(g, b));
	float diff = maxVal - minVal;

	MY_HSV hsv;
	hsv.h = 0.0f;
	if (diff == 0)
	{
		hsv.h = 0; // ñ≥ç êF
	}
	else
	{
		if (maxVal == r)
		{
			hsv.h = 60 * fmod(((g - b) / diff), 6.0f);
		}
		else if (maxVal == g)
		{
			hsv.h = 60 * (b - r) / diff + 2.0f;
		}
		else if (maxVal == b)
		{
			hsv.h = 60 * (r - g) / diff + 4.0f;
		}

		if (hsv.h < 0)
		{
			hsv.h += 360.0f;
		}
	}

	if (maxVal == 0.0f)
	{
		hsv.s = 0.0f;
	}
	else
	{
		hsv.s = diff / maxVal;
	}

	hsv.v = maxVal;

	return hsv;
}

int Color::GetColorMYRGB(MY_RGB myRGB)
{
	int ret = GetColor(myRGB.red, myRGB.green, myRGB.blue);
	return ret;
}

point Color::GetH(MY_RGB myRGB)
{

	return point();
}
