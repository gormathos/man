#!/usr/bin/env python

import cv2
import numpy as np

def count_colored_rectangles(image_path):
    # Зчитати зображення
    image = cv2.imread(image_path)

    # Перетворити BGR до RGB
    rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Змінити форму зображення для k-means
    pixels = rgb_image.reshape((-1, 3))

    # Використовуємо k-means для кластеризації кольорів
    k = 5  # Можна змінити кількість кластерів відповідно до зображення
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.2)
    _, labels, centers = cv2.kmeans(np.float32(pixels), k, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)

    # Перетворити центри кластерів у вигляд кольорів зі значеннями [0, 255]
    centers = np.uint8(centers)

    # Відновити зображення на основі кластеризації
    segmented_image = centers[labels.flatten()]

    # Перетворити зображення обратно до вигляду
    segmented_image = segmented_image.reshape(rgb_image.shape)

    # Перетворити в відтінки сірого для подальшої обробки
    gray_image = cv2.cvtColor(segmented_image, cv2.COLOR_RGB2GRAY)

    # Бінаризація для виділення контурів
    _, binary = cv2.threshold(gray_image, 1, 255, cv2.THRESH_BINARY)

    # Знаходження контурів
    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

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
result = count_colored_rectangles(image_path)
print("Кількість кольорових прямокутників на зображенні:", result)

