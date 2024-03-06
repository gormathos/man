#!/usr/bin/env python

import cv2
import numpy as np

def count_rectangles(image_path):
    image = cv2.imread(image_path)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (1, 1), 0)
    edges = cv2.Canny(blurred, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    rectangle_count = 0
    for contour in contours:
        epsilon = 0.085 * cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, epsilon, True)
        cv2.drawContours(image, [approx], 0, (0, 255, 0), 2)
        if len(approx) == 4 and cv2.contourArea(contour) > 0.01:
            rectangle_count += 1

    cv2.drawContours(image, [approx], 0, (0, 255, 0), 2)
    #cv2.imshow('Detected Rectangles', image)
    #cv2.waitKey(0)
    cv2.destroyAllWindows()

    return rectangle_count

if __name__ == "__main__":
    #for i in range(1, 16):
    image_path = "input.png"
    count = count_rectangles(image_path)
    print(count)
