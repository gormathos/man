import pandas as pd

def verdict(p):
    if p < 60.00:
        return "Participant"
    if p < 74.00:
        return "Very Good"
    if p < 90.00:
        return "Excellent"
    return "Outstanding"

df = pd.read_csv('input.csv', delimiter=';', header=0)  # Вказуємо, що перший рядок - заголовок
df.columns = ['sol_id', 'user_id', 'task_id', 'score']

# Перетворення колонки score на числовий тип
df['score'] = pd.to_numeric(df['score'])

res = df.groupby(['user_id', 'task_id'])['score'].max().reset_index().groupby('user_id')['score'].sum()

for user_id, total_score in res.items():
    max_total_score = df[df['user_id'] == user_id]['task_id'].nunique() * 100.00
    p = total_score / max_total_score * 100
    print(f"{user_id}: {verdict(p)} [{p:.2f}%]")

