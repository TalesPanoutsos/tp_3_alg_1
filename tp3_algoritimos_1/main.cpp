#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono> 
using namespace std::chrono; 
using namespace std;

std::string text_of_file(std::string nome_arq){
	std::fstream arq;
	arq.open(nome_arq);
	std::string text= "";
	while(!arq.eof()){
		std::string aux;
		std::getline(arq,aux);
		text=text + aux + ' ';
	}
	arq.close();
	return text;
}


void print_matriz(int **matriz, int N){
	//printando a matriz
	cout<<endl;
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			std::cout<<matriz[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool resolvido(int **matriz, int N){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			if(matriz[i][j] == 0)
				return 0;
		}
	}
	return 1;
}


void inicializa_nums(int N, int nums[]){
	for(int i = 0; i < N; ++i)
		nums[i] = 1;
}

void copiar_matriz(int **matriz1, int **matriz2, int N){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			matriz2[i][j] = matriz1[i][j];
		}
	}

}

int* verifica_linha(int **matriz, int N, int I, int J, int nums[]){
	
	for (int i = 0; i < N; ++i)
		nums[N] = i+1;

	for (int j = 0; j < N; ++j){
		if(matriz[I][j] != 0 and matriz[I][j]!= matriz[I][J])
			nums[matriz[I][j]-1] = 0;
	}
	return nums;
}

int* verifica_coluna(int **matriz, int N, int I, int J, int nums[]){
	
	for (int i = 0; i < N; ++i)
		nums[N] = i+1;

	for (int i = 0; i < N; ++i){
		if(matriz[i][J] != 0 and matriz[i][J]!= matriz[I][J])
			nums[matriz[i][J]-1] = 0;
	}
	return nums;
}

int* verifica_quadrante(int **matriz, int N, int I, int J, int nums[], int quad_n , int quad_m){
	int quad_i, quad_j;
	quad_i = int(I/quad_n);
	quad_j = int(J/quad_m);

	quad_i = quad_i*quad_n;
	quad_j = quad_j*quad_m;

	for (int i = quad_i; i < quad_i+quad_n; ++i){
		for (int j = quad_j; j < quad_j+quad_m; ++j){
			if(matriz[i][j] != 0 and matriz[i][j]!= matriz[I][J])
				nums[matriz[i][j]-1] = 0;
		}
	}

	return nums;

}

int verificador(int **matriz, int N, int I, int J, int nums[], int quad_n , int quad_m){
	if (matriz[I][J]!=0){
		for(int i = 0; i < N; ++i)
			nums[i] = 0;
		return 0;
	}
	int poss=0;

	verifica_linha(matriz, N, I, J, nums);
	verifica_coluna(matriz, N, I, J, nums);
	verifica_quadrante(matriz, N, I, J, nums, quad_n, quad_m);

	for(int i = 0; i < N; ++i){
		if(nums[i]==1)
			poss++;
	}
	return poss;
}


int* decisor_de_posicao(int **matriz, int N, int nums[], int quad_n , int quad_m){
	int menor = N+1;
	int *position = new int[2];

	int i_escolhido, j_escolhido;
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			int nums_aux[N];
			inicializa_nums(N, nums_aux);
			int poss = verificador(matriz, N, i, j, nums_aux, quad_n, quad_m);
			if(poss == 0 and matriz[i][j] == 0){
				position[0] = -1;
				return position;
			}
			if(poss<menor and poss!=0){
				inicializa_nums(N, nums);
				menor = verificador(matriz, N, i, j, nums, quad_n, quad_m);
				i_escolhido = i;
				j_escolhido = j;
			}
		}
	}
	if(menor == N+1){
		position[0] = -2;
		return position;
	}

	position[0]=i_escolhido;
	position[1]=j_escolhido;
	return position;
	
}

int **backtrack(int **matriz, int N, int quad_n, int quad_m, bool heuristico){
	int nums[N];
	inicializa_nums(N, nums);

	int **matriz_resposta;
	int **matriz_aux;
	matriz_aux = (int**)malloc(N * sizeof(*matriz_aux));
	matriz_resposta = (int**)malloc(N * sizeof(*matriz_resposta));

	for(int i=0; i<N; i++)
		matriz_resposta[i] = (int*)malloc(N * sizeof *matriz_resposta[i]);
	copiar_matriz(matriz, matriz_resposta, N);


	for(int i=0; i<N; i++)
		matriz_aux[i] = (int*)malloc(N * sizeof *matriz_aux[i]);
	copiar_matriz(matriz, matriz_aux, N);

	int *posicao;
	posicao = decisor_de_posicao(matriz_resposta, N, nums, quad_n , quad_m);
	int I = posicao[0];
	int J = posicao[1];
	if(I==-2)
		return matriz_resposta;
	


	for (int i = 0; i < N; ++i){
		if(nums[i]==1 and I!=-1){
			matriz_resposta[I][J] = i+1;
			copiar_matriz(matriz_resposta, matriz_aux, N);
			matriz_aux = backtrack(matriz_resposta, N, quad_n, quad_m, heuristico);
			if(resolvido(matriz_aux, N))
				return matriz_aux;

		}
	}

	return matriz_resposta;
}


int main(int argc, char const *argv[]){
	
	if(argc>1){
		stringstream texto(text_of_file(argv[1]));
		int N, quad_n, quad_m, num;
		texto>>N>>quad_m>>quad_n;
		int **matriz;

		matriz = (int**)malloc(N * sizeof(*matriz));
	  	for(int i=0; i<N; i++)
	    	matriz[i] = (int*)malloc(N * sizeof *matriz[i]);
		
		for (int i = 0; i < N; ++i){
			for (int j = 0; j < N; ++j){
				texto>> num;
				matriz[i][j] = num;
			}
		}	
		//Espaço pra manobra

	
		matriz = backtrack(matriz, N, quad_n, quad_m, 1);
	
		//print_matriz(matriz, N);

	}else

		printf("Nenhum arquivo no parametro");

	return 0;
}
