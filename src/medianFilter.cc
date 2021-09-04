#include <execution>
#include <algorithm>
#include <chrono>
#include <cmath>

#include "graphlib.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter(unsigned int kernelSize) {

	// We set the kernel width
	// (The kernel size is the width of the border of the kernel)
	unsigned int kernelWidth = kernelSize * 2 + 1;
	// We set the surface
	unsigned int kernelTotalSize = pow(kernelWidth, 2);

	// We check the kernel size
	if (kernelSize == 0) {
		throw std::runtime_error("Error : in Image::applyMedianFilter : The kernel size can't be 0");
	} else if (kernelWidth > height || kernelWidth * 2 + 1 > width) {
		throw std::runtime_error("Error : in Image::applyMedianFilter : The kernel size is to big for this image");
	}

	// We create a vector to save the new image
	// We can't compute the median for the borders of the image so we keep the old values
	std::vector<std::vector<uint8_t>> newPixels = pixels;

	auto startTime = std::chrono::high_resolution_clock::now();

	// For each line of the image...
	for (unsigned int i = kernelSize; i < (height - kernelSize); i++) {

		// For each pixel of this line...
		for (unsigned int j = kernelSize; j < (width - kernelSize); j++) {

			// For each value of this pixel...
			for (unsigned int k = 0; k < pixelSize; k++) {

				// We create a vector to store the pixel values (value per value)
				// For example for an RGB image :
				// Fist, we calculate the median of the red values of the pixels of the neighborhood
				std::vector<uint8_t> medianPixels;
				medianPixels.reserve(kernelTotalSize);

				// We add the pixels values in the vector
				for (int l = -(int(kernelSize)); l <= int(kernelSize); l++) {
					for (int m = -(int(kernelSize)); m <= int(kernelSize); m++) {
						medianPixels.push_back(pixels[i + l][(j + m) * pixelSize + k]);
					}
				}

				// We compute the median of this values
				std::sort(std::execution::par, medianPixels.begin(), medianPixels.end());
				uint8_t median = medianPixels[medianPixels.size() / 2];

				// We update the value
				newPixels[i][j * pixelSize + k] = median;
			}
		}
	}

	// We update the image
	pixels = newPixels;

	auto stopTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
	std::cout << "Execution time: " << (float(duration.count()) / 1000000) << " seconds\n";
}
