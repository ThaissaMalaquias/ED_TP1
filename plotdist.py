import pandas as pd
import matplotlib.pyplot as plt

# Lista de arquivos CSV e seus títulos
csv_files = ["Q_mem_access.csv", "M_mem_access.csv", "S_mem_access.csv"]
titles = ["QuickSort Memory Access", "MergeSort Memory Access", "SelectionSort Memory Access"]

# Para armazenar distâncias de pilha
stack_distances = {}

# Processar cada arquivo CSV
for file, title in zip(csv_files, titles):
    # Carrega o CSV
    data = pd.read_csv(file, names=["Time", "Address"])
    
    # Converte tempo para milissegundos
    data["Time"] = data["Time"] / 1e3
    
    # Calcular distâncias de pilha como diferença entre tempos consecutivos
    data["Time_diff"] = data["Time"].diff().fillna(0)  # Substituir NaN (primeira entrada) com 0
    
    # Adicionar à lista de distâncias de pilha para este algoritmo
    stack_distances[title] = data["Time_diff"].tolist()

# Criar os gráficos
fig, axes = plt.subplots(len(stack_distances), 1, figsize=(10, 12))
for (title, distances), ax in zip(stack_distances.items(), axes):
    ax.plot(distances, marker='o', linestyle='-', alpha=0.6)
    ax.set_title(title)
    ax.set_xlabel("Access Number")
    ax.set_ylabel("Time Difference (ms)")
    ax.grid(True)

# Salvar o gráfico
plt.tight_layout()
plt.savefig("stack_distance_comparison.png")
plt.close()

print("Gráfico salvo em stack_distance_comparison.png")
