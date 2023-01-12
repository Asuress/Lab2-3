#include "MImageCalculator.h"

MImageCalculator::MImageCalculator(const std::function<float(SDL_Point pixel)>& computeFunction) :
	_computeFunction(computeFunction)
{
}

std::vector<std::vector<MImagePixelData>> MImageCalculator::GetSpaceData(SDL_Point spaceSize)
{
	// Matrix
	std::vector data(spaceSize.x, std::vector<MImagePixelData>(spaceSize.y));

	for (int x = 0; x < spaceSize.x; ++x)
	{
		for (int y = 0; y < spaceSize.y; ++y)
			data[x][y] = GetPixelData({ x, y });
	}

	return data;
}

MImagePixelData MImageCalculator::GetPixelData(SDL_Point point)
{
	int x = point.x;
	int y = point.y;

	MImagePixelData data;
	
	int x1 = x, y1 = y;
	int x2 = x, y2 = y + 1;
	int x3 = x + 1, y3 = y;
	float z1 = _computeFunction({ x1, y1 });
	float z2 = _computeFunction({ x2, y2 });
	float z3 = _computeFunction({ x3, y3 });

	// Считаем дискременанты
	float Ai = y1 * (z2 - z3) - y2 * (z1 - z3) + y3 * (z1 - z2);
	float Bi = -(x1 * (z2 - z3) - x2 * (z1 - z3) + x3 * (z1 - z2));
	float Ci = x1 * (y2 - y3) - x2 * (y1 - y3) + x3 * (y1 - y2);
	float Di = x1 * (y2 * z3 - y3 * z2) - x2 * (y1 * z3 - y3 * z1) + x3 * (y1 * z2 - y2 * z1);

	// Находим компоненты нормалей к площадке
	data.nx = Ai / std::sqrtf(Ai * Ai + Bi * Bi + Ci * Ci);
	data.ny = -Bi / std::sqrtf(Ai * Ai + Bi * Bi + Ci * Ci);
	data.nz = -Ci / std::sqrtf(Ai * Ai + Bi * Bi + Ci * Ci);
	data.nd = Di / std::sqrtf(Ai * Ai + Bi * Bi + Ci * Ci + Di * Di);

	int zoneFlag = (z1 >= 0) + (z2 >= 0) + (z3 >= 0);

	if (zoneFlag > 2)
		data.zone = Positive;
	else
		data.zone = Negative;
	
	return data;
}
