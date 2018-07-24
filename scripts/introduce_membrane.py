#!/usr/bin/env python

import cv2
import numpy as np

img = cv2.imread('../segmentation_bw_original.png', 0)
print type(img), img.shape

# img = img / 255
# print img.tolist()

it =  np.nditer(img, op_flags=['readwrite'], order='C')

prev = 127
while not it.finished:
    dif = abs(prev - it[0])
    if dif == 255 or dif == 1:
        it[0] = 127
    prev = it[0]
    it.iternext()

it =  np.nditer(img, op_flags=['readwrite'], order='F')

prev = 127
while not it.finished:
    dif = abs(prev - it[0])
    if dif == 255 or dif == 1:
        it[0] = 127
    prev = it[0]
    it.iternext()

cv2.imwrite('../segmentation_bw_new.png', img)

# cv2.imshow('image', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
