#!/usr/bin/env python

import cv2
import numpy as np

img = cv2.imread('../img/segmentation_bw_original.png', 0)

print type(img), img.shape

# img = img / 255
# print img.tolist()+

# it =  np.nditer(img, op_flags=['readwrite'], order='C')
# prev = 127
# while not it.finished:
#     dif = abs(prev - it[0])
#     if dif == 255 or dif == 1:
#         it[0] = 127
#     prev = it[0]
#     it.iternext()
#
# it =  np.nditer(img, op_flags=['readwrite'], order='F')
# prev = 127
# while not it.finished:
#     dif = abs(prev - it[0])
#     if dif == 255 or dif == 1:
#         it[0] = 127
#     prev = it[0]
#     it.iternext()

prev = 127
for i in range(len(img)):
    for j in range(len(img[0])):
        dif = abs(prev - img[i][j])
        if dif == 255:
            img[i][j-1] = 127
        elif dif == 1:
            img[i][j] = 127
        prev = img[i][j]

prev = 127
for j in range(len(img[0])):
    for i in range(len(img)):
        dif = abs(prev - img[i][j])
        if dif == 255:
            img[i-1][j] = 127
        elif dif == 1:
            img[i][j] = 127
        prev = img[i][j]

cv2.imwrite('../img/segmentation_bw_new.png', img)
# cv2.imshow('image', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
