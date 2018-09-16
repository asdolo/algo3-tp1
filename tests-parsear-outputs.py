import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

pandas_dataframe_fb = pd.read_csv('output/fuerzabruta.csv')
pandas_dataframe_bt = pd.read_csv('output/backtracking.csv')
pandas_dataframe_pd = pd.read_csv('output/programaciondinamica.csv')

finaldf = pd.concat([pandas_dataframe_fb, pandas_dataframe_bt, pandas_dataframe_pd], axis=0, join='inner').sort_index()


plot = sns.lineplot(x="n", y="tiempo (fuerzabruta)", data=pandas_dataframe_fb)
plot = sns.lineplot(x="n", y="tiempo (backtracking)", data=pandas_dataframe_bt)
plot = sns.lineplot(x="n", y="tiempo (programaciondinamica)", data=pandas_dataframe_pd)
plot.legend(["Fuerza bruta", "Backtracking", "Programacion Dinamica"])
plot.set(ylabel="Tiempo");