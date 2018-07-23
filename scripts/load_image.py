#!/usr/bin/env python

import cv2

img = cv2.imread('../segmentation_bw.png', 0)
print type(img), img.shape

img = img / 255
# print img.tolist()

cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
