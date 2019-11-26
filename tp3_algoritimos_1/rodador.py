import os
import time
import numpy as np
from random import random
from math import floor
import linecache
#import matplotlib.pyplot as plt








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




#FAZENDO OS ARQUIVOS DE TESTE
# for tam in {4,6,8,9,10,12,14,15,16}:
# 	temp_exec=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
# 	desvio_padrao=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
	
# 	for i in range(4,101,4):
		
# 		nome_arquivo="entrada.txt"
# 		entrada_escrita = open(nome_arquivo,"w")

# 		#Chama a função de pra alterar a entrada.
# 		build_random_sudoku(entrada_escrita, tam)


# 		entrada_escrita.close()

# 	#RODANDO CADA UM DELES 10 VEZES

# 		tempos = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
# 		for j in range(10):	
# 			os.system("main.exe " + nome_arquivo + " > tempo.txt")
# 			tempo = open("tempo.txt", "r")
# 			tempos[j]= int(linecache.getline('tempo.txt', 0))


# 		print(np.array(tempos).mean(), " ", np.array(tempos).std())
		
	


nome_arquivo="entrada.txt"
entrada_escrita = open(nome_arquivo,"w")

#Chama a função de pra alterar a entrada.
build_random_sudoku(entrada_escrita, int(input("Digite tam: ")))


entrada_escrita.close()
