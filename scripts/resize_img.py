#!/usr/bin/env python

import cv2
import numpy as np

mult = 2

img = cv2.imread('../1.png', 0)

n_x = img.shape[1]
n_y = img.shape[0]

img_new = np.empty([n_y, n_x * mult])

print type(img), img.shape

for i in range(n_x):
    for j in range(n_y):
        for l in range(mult):
            img_new[j][mult * i + l] = img[j][i]

print type(img_new), img_new.shape

cv2.imwrite('../segmentation_bw_new.png', img_new)
# cv2.imshow('image', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
