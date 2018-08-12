#!/usr/bin/env python

import cv2
import numpy as np

n_x = 200
n_y = 11

white = 255
gray = 127
black = 0

img = np.empty([n_y, n_x])

left_edge = 4 * n_x / 10
right_edge = 6 * n_x / 10
for i in range(n_x):
    for j in range(n_y):
        if i < left_edge:
            img[j][i] = white
        elif i >= left_edge and i < right_edge:
            img[j][i] = gray
        else:
            img[j][i] = black

cv2.imwrite('../segmentation_bw_new.png', img)
# cv2.imshow('image', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
