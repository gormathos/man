#!/usr/bin/env python

import pandas as pd

df = pd.read_csv('input.csv', delimiter=';', header=0)
lang = {
    1: "Pascal",
    2: "Python",
    3: "C++",
    4: "Java",
    5: "C#"
}

lang_stat = df.groupby('lang_id').agg(
    users=('user_id', 'nunique'),
    total_solutions=('sol_id', 'count'),
    perfect_solutions=('score', lambda x: (x == 100).sum()),
    zero_solutions=('score', lambda x: (x == 0).sum())
)

lang_stat = lang_stat.rename(index=lang)

# print(lang_stat)

for index, row in lang_stat.iterrows():
    print(f"{index}: {row['users']} {row['total_solutions']} {row['perfect_solutions']} {row['zero_solutions']}")
