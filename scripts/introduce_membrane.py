#!/usr/bin/env python

import cv2
import numpy as np

img = cv2.imread('../segmentation_bw_original.png', 0)
print cv2.__version__
print type(img), img.shape

kernel = np.ones((3, 3), np.uint8)
erosion = cv2.erode(img, kernel, iterations = 1)

membrane = cv2.bitwise_xor(img, erosion)
# cells = cv2.bitwise_and(img, erosion)

membrane /= 2
out = membrane + erosion

cv2.imwrite('../segmentation_bw_new.png', out)

# cv2.imshow('image', erosion)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
