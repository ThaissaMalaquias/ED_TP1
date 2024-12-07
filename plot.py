import pandas as pd
import matplotlib.pyplot as plt

# Lista de arquivos CSV e seus títulos
csv_files = ["Q_mem_access.csv", "M_mem_access.csv", "S_mem_access.csv"]
titles = ["QuickSort Memory Access", "MergeSort Memory Access", "SelectionSort Memory Access"]

# Gerar um gráfico separado para cada arquivo
for file, title in zip(csv_files, titles):
    # Carrega o CSV
    data = pd.read_csv(file, names=["Time", "Address"])
    
    # Converte tempo para milissegundos
    data["Time"] = data["Time"] / 1e3

    # Criar o gráfico
    plt.figure(figsize=(10, 6))
    plt.scatter(data["Time"], data["Address"], alpha=0.6)
    plt.title(title)
    plt.xlabel("Time (ms)")
    plt.ylabel("Address")
    plt.grid(True)

    # Salvar o gráfico como imagem
    output_file = file.replace(".csv", ".png")  # Substitui .csv por .png no nome do arquivo
    plt.savefig(output_file)
    plt.close()

    print(f"Gráfico salvo em {output_file}")
