import os
import time
import numpy as np
from random import random
from math import floor
import linecache
import time
import matplotlib.pyplot as plt








def build_random_sudoku(arquivo, tam):
	
	for i in range(floor(tam**(1/2)), tam, 1):
		if(tam%i == 0):
			quad_n = tam/i
			quad_m = i


	arquivo.write(str(tam)+" "+str(int(quad_n))+" "+str(int(quad_m))+ "\n")
	posicoes = []
	for i in range(tam):
		x = floor(random()*tam)
		y = floor(random()*tam)
		posicoes.append((x,y))

	sudo = np.zeros((tam,tam))

	for p in posicoes: 
		sudo[p[0],p[1]] = floor(random()*tam+1)

	for i in range(sudo.shape[0]):
		for j in sudo[i,:]:
			arquivo.write(str(int(j)) + " ")
		arquivo.write('\n')
	print(sudo)




#FAZENDO OS ARQUIVOS DE TESTE
matriz = np.zeros((4,5))
matriz_std = np.zeros((4,5))

nums = [22,66,88,99]
for i in range(0,len(nums)):
	for j in range(1,6):
		nome_arquivo= str(nums[i])+str(j)+".txt"
		#entrada_escrita = open(nome_arquivo,"w")

		#Chama a função de pra alterar a entrada.
		#build_random_sudoku(entrada_escrita, tam)


		#entrada_escrita.close()

	#RODANDO CADA UM DELES 10 VEZES

		tempos = np.zeros(100)
		for k in range(100):	
			begin = time.time()
			os.system("main.exe " + nome_arquivo)
			tempo = time.time() - begin
			tempos[k]= tempo


		matriz[i,j-1] = np.array(tempos).mean()
		matriz_std[i,j-1] =  np.array(tempos).std()

print(matriz.mean(axis = 1))
print(matriz_std.mean(axis = 1))
	

plt.title('Tempo de Execução')
plt.plot(['4x4','6x6','8x8','9x9'], matriz.mean(axis = 1))
plt.show()

plt.title('Desvio Padrão')
plt.plot(['4x4','6x6','8x8','9x9'],matriz_std.mean(axis = 1))
plt.show()

# nome_arquivo="entrada.txt"
# entrada_escrita = open(nome_arquivo,"w")

# #Chama a função de pra alterar a entrada.
# build_random_sudoku(entrada_escrita, int(input("Digite tam: ")))


# entrada_escrita.close()

