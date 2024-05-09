#!/usr/bin/env python

import pandas as pd

def convertTimestampToDateTime(timestamp):
    return pd.to_datetime(timestamp, unit='s').strftime('%d.%m.%Y %H:%M:%S')

df = pd.read_csv('input.csv', delimiter=';', header=0)

perfect_scores = df[df['score'] == 100.00]['posted_time'].apply(convertTimestampToDateTime)

print(len(perfect_scores))
for timestamp in perfect_scores:
    print(timestamp)
