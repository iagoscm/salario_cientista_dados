import pandas as pd

# Lê o arquivo csv
df = pd.read_csv('ds_salaries.csv')

# Tira colunas desnecessárias
newdf = df[['salary_in_usd']]
newdf.to_csv('arquivo_tratado.csv')
