#!/usr/bin/env python

import cv2
import numpy as np

def count_rectangles(image_path):
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

    # Thresholding
    _, thresh = cv2.threshold(img, 200, 255, cv2.THRESH_BINARY_INV)

    # Dilation
    kernel = np.ones((1, 1), np.uint8)
    dilation = cv2.dilate(thresh, kernel, iterations=2)

    # Find contours
    contours, _ = cv2.findContours(
        dilation, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Additional filtering parameters
    min_contour_area = 5  # Adjust as needed
    max_contour_area = 20000  # Adjust as needed

    # Count rectangles
    rectangle_count = 0
    for contour in contours:
        area = cv2.contourArea(contour)
        if min_contour_area < area < max_contour_area:
            rectangle_count += 1

    return rectangle_count

# Path to your image
image_path = 'input.png'

# Call the function and print the result
result = count_rectangles(image_path)
print(result)

