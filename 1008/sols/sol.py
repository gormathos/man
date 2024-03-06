#!/usr/bin/env python
import cv2
import numpy as np

def count_rectangles(image_path):
    # Зчитати зображення
    image = cv2.imread(image_path)

    # Перетворення до відтінків сірого
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Розмиття для зменшення шуму та полегшення виявлення контурів
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)

    # Детектор країв
    edges = cv2.Canny(blurred, 50, 150)

    # Пошук контурів
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Порахувати кількість прямокутників
    rectangle_count = 0

    for contour in contours:
        # Апроксимація контуру прямокутником
        epsilon = 0.02 * cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, epsilon, True)

        # Якщо контур має більше 3 вершин, то він може бути прямокутником
        if len(approx) >= 3:
            # Виявлення прямокутників
            rect = cv2.minAreaRect(contour)
            box = cv2.boxPoints(rect)
            box = np.int0(box)

            # Вираховуємо відстані між вершинами
            dist1 = np.linalg.norm(box[0] - box[1])
            dist2 = np.linalg.norm(box[1] - box[2])

            # Якщо відстані схожі, то це може бути прямокутник
            if abs(dist1 - dist2) < 10:
                rectangle_count += 1

    return rectangle_count

# Задайте шлях до вашого зображення
image_path = 'input.png'

# Викликати функцію та вивести результат
result = count_rectangles(image_path)
print(result)

