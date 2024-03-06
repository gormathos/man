#!/usr/bin/env python

import pandas as pd
import numpy as np

data = pd.read_csv('input.csv', sep=';', header=None)

# Функція для перевірки, чи є значення цілим числом
def is_number(x):
    try:
        float_x = float(x)
        return float_x.is_integer() if isinstance(float_x, float) else False
    except ValueError:
        return False


# Заміна значень, якщо вони є цілими числами
cleaned_data = data.applymap(lambda x: int(float(x)) if is_number(x) else np.nan)

#print(cleaned_data)

cleaned_data = cleaned_data.dropna(how='any')

# Перевіряємо, чи всі значення у кожному стовпці однакові
for column in cleaned_data.columns:
    unique_values_count = cleaned_data[column].nunique()
    if unique_values_count == 1:
        cleaned_data.drop(column, axis=1, inplace=True)

# Вивід результату або збереження у файл
#print(cleaned_data.astype(int))
if cleaned_data.empty:
  with open('output.csv', 'w') as file:
    file.write("Empty DataFrame\n")
else:
  cleaned_data.astype(int).to_csv('output.csv', sep=';', index=False, header=False)

