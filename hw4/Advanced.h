#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

IMAGE *AddNoise(IMAGE *image, int n);

IMAGE *Sharpen(IMAGE *image);

IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);

IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount);

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H);

IMAGE *Resize(IMAGE *image, int percentage);

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image);

#endif /* ADVANCED_H_INCLUDED_ */