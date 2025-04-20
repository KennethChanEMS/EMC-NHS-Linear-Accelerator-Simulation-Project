import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("/Users/student/Desktop/geant4/Linac_V2/data.csv")

mass = (55 * 30 * 15.0)/1000

avg_by_depth = df.groupby("Depth (cm)")["Energy Absorbed (MeV)"].mean().reset_index()
avg_energy = np.array(avg_by_depth["Energy Absorbed (MeV)"].tolist())
depths = np.array(avg_by_depth["Depth (cm)"].tolist())

avg_energy = avg_energy * 1.6e-13

Dose = avg_energy / mass

Dose = (Dose / d_max)*100

plt.plot(depths, Dose, marker='o')
plt.show()