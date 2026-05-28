// Include important libraries here
#include <SFML/Graphics.hpp>
#include <math.h>
#include <concepts> // for std::same_as
#include <iostream>

// Make code easier to type with "using namespace" 
using namespace sf;


#define uSizeX 3840
#define uSizeY 2160

#define fSizeX (float)uSizeX
#define fSizeY (float)uSizeY

#define uMaxX (uSizeX - 1)
#define uMaxY (uSizeY - 1)

#define fMaxX ((float)uMaxX)
#define fMaxY ((float)uMaxY)

#define fMidX (((float)uSizeX / 2.0f))
#define fMidY (((float)uSizeY / 2.0f))

const Vector2u screenDimensions = { 3840, 2160 };

const Color axisColor = Color::Green;
const Color pointColor = Color::Red;
const Color lineColor = Color::Yellow;

const Vertex baseAxis = Vertex{ .color{axisColor}, .texCoords{1.0f, 1.0f} };
const Vertex basePoint = Vertex{ .color{pointColor}, .texCoords{1.0f, 1.0f} };

const float fLimitNaturalPositiveX = fMidX;
const float fLimitNaturalPositiveY = fMidY;
const float fLimitNaturalNegativeX = -fMidX;
const float fLimitNaturalNegativeY = -fMidY;

const int iLimitNaturalPositiveX = (int)truncf(fMidX);
const int iLimitNaturalPositiveY = (int)truncf(fMidY);
const int iLimitNaturalNegativeX = -(int)truncf(fMidX);
const int iLimitNaturalNegativeY = -(int)truncf(fMidY);

const unsigned int defaultStepSize = 20;
const Color defaultGraphicColor = Color::Magenta;


float getScreenX(float fNaturalX) {

	if (fNaturalX < fLimitNaturalNegativeX) {
		__debugbreak();
		return -fMaxX;
	}

	if (fNaturalX > fLimitNaturalPositiveX) {
		__debugbreak();
		return fMaxX;
	}

	return fNaturalX + fMidX;
}

float getScreenY(float fNaturalY) {
	if (fNaturalY < fLimitNaturalNegativeY) {
		__debugbreak();
		return -fMaxY;
	}

	if (fNaturalY > fLimitNaturalPositiveY) {
		__debugbreak();
		return fMaxY;
	}

	return fSizeY - (fNaturalY + fMidY);
}


VertexArray getAxis(Color color = axisColor) {
	const Vertex baseVertex = Vertex{ .color{color}, .texCoords{1.0f, 1.0f} };

	Vertex xAxisLeft = Vertex{ .position{0.0f, fMidY-1}, .color{baseVertex.color}, .texCoords{baseVertex.texCoords} };
	Vertex xAxisRight = Vertex{ .position{fMaxX, fMidY-1}, .color{baseVertex.color}, .texCoords{baseVertex.texCoords} };

	Vertex yAxisTop = Vertex{ .position{fMidX+1, 0.0f}, .color{baseVertex.color}, .texCoords{baseVertex.texCoords} };
	Vertex yAxisBottom = Vertex{ .position{fMidX+1, fMaxY}, .color{baseVertex.color}, .texCoords{baseVertex.texCoords} };

	VertexArray axis = VertexArray::VertexArray(PrimitiveType::Lines, 2);
	axis.append(xAxisLeft);
	axis.append(xAxisRight);
	axis.append(yAxisTop);
	axis.append(yAxisBottom);

	return axis;
}

VertexArray getPoint(float fNaturalX, float fNaturalY, Color color = pointColor) {
	float fScreenX = getScreenX(fNaturalX);
	float fScreenY = getScreenY(fNaturalY);

	VertexArray va = VertexArray::VertexArray(PrimitiveType::Points, 1);
	va.append(Vertex{ .position{fScreenX, fScreenY}, .color{color}, .texCoords{1.0f, 1.0f} });
	return va;
}

VertexArray getLeftY(Color color = pointColor) {
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Points, uSizeY);
	const float fX = getScreenX(-1.0f);
	for (int i = iLimitNaturalNegativeY; i < iLimitNaturalPositiveY; ++i) {
		float fY = getScreenY((float)i);
		va.append(Vertex{ .position{fX, fY}, .color{color}, .texCoords{1.0f, 1.0f} });
	}
	return va;
}

VertexArray getRightY(Color color = pointColor) {
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Points, uSizeY);
	const float fX = getScreenX(1.0f);
	for (int i = iLimitNaturalNegativeY; i < iLimitNaturalPositiveY; ++i) {
		float fY = getScreenY((float)i);
		va.append(Vertex{ .position{fX, fY}, .color{color}, .texCoords{1.0f, 1.0f} });
	}
	return va;
}

VertexArray getUpperX(Color color = pointColor) {
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Points, uSizeX);
	const float fY = getScreenY(1.0f);
	for (int i = iLimitNaturalNegativeX; i < iLimitNaturalPositiveX; ++i) {
		float fX = getScreenX((float)i);
		va.append(Vertex{ .position{fX, fY}, .color{color}, .texCoords{1.0f, 1.0f}});
	}
	return va;
}

VertexArray getLowerX(Color color = pointColor) {
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Points, uSizeX);
	const float fY = getScreenY(-1.0f);
	for (int i = iLimitNaturalNegativeX; i < iLimitNaturalPositiveX; ++i) {
		float fX = getScreenX((float)i);
		va.append(Vertex{ .position{fX, fY}, .color{color}, .texCoords{1.0f, 1.0f} });
	}
	return va;
}


bool PauseToDebug(RenderWindow& window, bool& useDebugPause, const VertexArray& va) {
	bool wasPaused = false;
	if (useDebugPause) {
		window.draw(va);
		window.display();

		bool freezeDisplay = true;
		while (window.isOpen() && freezeDisplay && useDebugPause)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::B))
			{
				__debugbreak();
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Key::R))
			{
				useDebugPause = false;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Key::S))
			{
				freezeDisplay = false;
			}

			wasPaused = true;
			sleep(milliseconds(100));
		}
	}

	return wasPaused;
}

VertexArray getQuadrantOneInside(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / stepSize);
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f, y1 = fLimitNaturalPositiveY-offset, x2 = 0.0f+offset, y2 = 0.0f; y1 >= 0; y1 -= stepSize, x2 += stepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantTwoInside(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / stepSize);
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f, y1 = fLimitNaturalNegativeY+offset, x2 = 0.0f+offset, y2 = 0.0f; y1 <= 0; y1 += stepSize, x2 += stepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantThreeInside(RenderWindow& window, bool useDebugPause = false, int uStepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / abs(uStepSize));
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f, y1 = fLimitNaturalNegativeY+offset, x2 = 0.0f-offset, y2 = 0.0f; y1 <= 0; y1 += uStepSize, x2 -= uStepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantFourInside(RenderWindow& window, bool useDebugPause = false, int uStepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / abs(uStepSize));
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f, y1 = fLimitNaturalPositiveY-offset, x2 = 0.0f-offset, y2 = 0.0f; y1 >= 0; y1 -= uStepSize, x2 -= uStepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantOneOutside(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / stepSize);
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f+offset, y1 = fLimitNaturalPositiveY, x2 = fLimitNaturalPositiveY, y2 = fLimitNaturalPositiveY-offset; y2 >= 0; x1 += stepSize, y2 -= stepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantTwoOutside(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / stepSize);
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f+offset, y1 = fLimitNaturalNegativeY, x2 = fLimitNaturalPositiveY, y2 = fLimitNaturalNegativeY+offset; y2 <= 0; y2 += stepSize, x1 += stepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantThreeOutside(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / stepSize);
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f-offset, y1 = fLimitNaturalNegativeY, x2 = fLimitNaturalNegativeY, y2 = fLimitNaturalNegativeY+offset; y2 <= 0; y2 += stepSize, x1 -= stepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}

VertexArray getQuadrantFourOutside(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {

	bool localUseDebugPause = useDebugPause;
	unsigned int uLineCount = (unsigned int)truncf(fLimitNaturalPositiveY / stepSize);
	VertexArray va = VertexArray::VertexArray(PrimitiveType::Lines, uLineCount);
	for (float x1 = 0.0f-offset, y1 = fLimitNaturalPositiveY, x2 = fLimitNaturalNegativeY, y2 = fLimitNaturalPositiveY-offset; y2 >= 0; x1 -= stepSize, y2 -= stepSize) {
		float sx1 = getScreenX(x1),
			sy1 = getScreenY(y1),
			sx2 = getScreenX(x2),
			sy2 = getScreenY(y2);
		va.append(Vertex{ .position{sx1, sy1}, .color{color}, .texCoords{1.0f, 1.0f} });
		va.append(Vertex{ .position{sx2, sy2}, .color{color}, .texCoords{1.0f, 1.0f} });

		PauseToDebug(window, localUseDebugPause, va);
	}

	return va;
}


template <typename... Args>
std::size_t getSizeOfCombinedVertexArrays(const std::same_as<VertexArray> auto&... arrays) {
	return (arrays.getVertexCount() + ...);
}

template <typename... Args>
bool allArraysHaveSamePrimitiveType(const std::same_as<VertexArray> auto&... arrays) {

	return ((arrays.getPrimitiveType() == arrays.getPrimitiveType()) && ...);
}

template <typename... Args>
VertexArray* combineVertexArrays(const std::same_as<VertexArray> auto&... arrays) {
	if (!allArraysHaveSamePrimitiveType(arrays...)) {
		return NULL;
	}
	
	// Helper lambda to get the first array from the parameter pack
	auto getFirst = [](const auto& first, const auto&...) { return first; };
	const auto& firstArray = getFirst(arrays...);
	
	std::size_t combinedSize = getSizeOfCombinedVertexArrays(arrays...);
	VertexArray* pCombinedArray = new VertexArray(firstArray.getPrimitiveType(), combinedSize);
	auto appendVertices = [pCombinedArray](const VertexArray& array) {
		for (std::size_t i = 0; i < array.getVertexCount(); ++i) {
			(*pCombinedArray).append(array[i]);
		}
	};
	(appendVertices(arrays), ...);
	return pCombinedArray;
}


VertexArray* getGraphic(RenderWindow& window, bool useDebugPause = false, unsigned int stepSize = defaultStepSize, Color color = defaultGraphicColor, float offset = 0.0f) {
	VertexArray quadOneInside = getQuadrantOneInside(window, false, 20U, color, offset);
	VertexArray quadTwoInside = getQuadrantTwoInside(window, false, 20U, color, offset);
	VertexArray quadThreeInside = getQuadrantThreeInside(window, false, 20U, color, offset);
	VertexArray quadFourInside = getQuadrantFourInside(window, false, 20U, color, offset);
	VertexArray quadOneOutside = getQuadrantOneOutside(window, false, 20U, color, offset);
	VertexArray quadTwoOutside = getQuadrantTwoOutside(window, false, 20U, color, offset);
	VertexArray quadThreeOutside = getQuadrantThreeOutside(window, false, 20U, color, offset);
	VertexArray quadFourOutside = getQuadrantFourOutside(window, false, 20U, color, offset);
	return combineVertexArrays(quadOneInside, quadTwoInside, quadThreeInside, quadFourInside, quadOneOutside, quadTwoOutside, quadThreeOutside, quadFourOutside);
}

int main()
{
	// Create a video mode object 
	VideoMode vm(screenDimensions);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", State::Fullscreen);
	VertexArray* pGraphic01 = nullptr;
	VertexArray* pGraphic02 = nullptr;
	VertexArray* pGraphic03 = nullptr;
	VertexArray* pGraphic04 = nullptr;

	try
	{
		if (window.isOpen())
		{
			const VertexArray axis = getAxis();

			window.clear();

			VertexArray* pGraphic01 = getGraphic(window, false, 20U, Color::Magenta, 0.0f);
			VertexArray* pGraphic02 = getGraphic(window, false, 20U, Color::Cyan, 7.0f);
			VertexArray* pGraphic03 = getGraphic(window, false, 20U, Color::Yellow, 14.0f);
			VertexArray* pGraphic04 = getGraphic(window, false, 20U, Color::Green, 15.0f);

			window.draw(*pGraphic01);
			window.draw(*pGraphic02);
			window.draw(*pGraphic03);
			window.draw(*pGraphic04);

			window.draw(axis);

			window.display();

			while (window.isOpen())
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
				{
					window.close();
				}

				sleep(milliseconds(100));
			}

			window.close();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An exception occurred: " << e.what() << std::endl;
	}

	if (pGraphic01) {
		delete pGraphic01;
		pGraphic01 = nullptr;
	}
	if (pGraphic02) {
		delete pGraphic02;
		pGraphic02 = nullptr;
	}
	if (pGraphic03) {
		delete pGraphic03;
		pGraphic03 = nullptr;
	}
	if (pGraphic04) {
		delete pGraphic04;
		pGraphic04 = nullptr;
	}

	return 0;
}