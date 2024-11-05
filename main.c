#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

// Função para mostrar as estatísticas
void mostrarEstatisticas(int comparacoes, int trocas, float tempoExecucao)
{
	printf("\nNúmero de comparações: %i\n", comparacoes);
	printf("Número de trocas de posição: %i\n", trocas);
	printf("Tempo (em segundos): %f\n\n", tempoExecucao);
}

// Função para imprimir o array
void imprimirArray(int lista[], int tamanho)
{
	printf("\n[");
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d", lista[i]);
		if (i < tamanho - 1)
		{
			printf(", ");
		}
	}
	printf("]\n");
}

// Função Bubble Sort
void bubbleSort(int vetor[], int tamanho, int *trocas, int *comparacoes)
{
	int aux, i, j;
	for (j = tamanho - 1; j >= 1; j--)
	{
		for (i = 0; i < j; i++)
		{
			(*comparacoes)++;
			if (vetor[i] > vetor[i + 1])
			{
				(*trocas)++;
				aux = vetor[i];
				vetor[i] = vetor[i + 1];
				vetor[i + 1] = aux;
			}
		}
	}
}

// Função Merge Sort
void merge(int arr[], int esquerda, int meio, int direita, int *trocas, int *comparacoes)
{
	int i, j, k;
	int n1 = meio - esquerda + 1;
	int n2 = direita - meio;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
	{
		L[i] = arr[esquerda + i];
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = arr[meio + 1 + j];
	}

	i = 0;
	j = 0;
	k = esquerda;
	while (i < n1 && j < n2)
	{
		(*comparacoes)++;
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		(*trocas)++;
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int esquerda, int direita, int *trocas, int *comparacoes)
{
	if (esquerda < direita)
	{
		int meio = esquerda + (direita - esquerda) / 2;
		mergeSort(arr, esquerda, meio, trocas, comparacoes);
		mergeSort(arr, meio + 1, direita, trocas, comparacoes);
		merge(arr, esquerda, meio, direita, trocas, comparacoes);
	}
}

// Função QuickSort
void quickSort(int *a, int esquerda, int direita, int *trocas, int *comparacoes)
{
	int i, j, x, y;
	i = esquerda;
	j = direita;
	x = a[(esquerda + direita) / 2];
	(*trocas) += 3;
	while (i <= j)
	{
		while (a[i] < x && i < direita)
		{
			i++;
			(*comparacoes)++;
			(*trocas)++;
		}
		while (a[j] > x && j > esquerda)
		{
			j--;
			(*comparacoes)++;
			(*trocas)++;
		}
		if (i <= j)
		{
			y = a[i];
			a[i] = a[j];
			a[j] = y;
			(*trocas) += 3;
			i++;
			j--;
		}
	}
	if (j > esquerda)
	{
		quickSort(a, esquerda, j, trocas, comparacoes);
	}
	if (i < direita)
	{
		quickSort(a, i, direita, trocas, comparacoes);
	}
}

// Função Heap Sort
void heapify(int arr[], int n, int i, int *comparacoes, int *trocas)
{
	int maior = i;
	int esquerda = 2 * i + 1;
	int direita = 2 * i + 2;

	(*comparacoes)++;
	if (esquerda < n && arr[esquerda] > arr[maior])
		maior = esquerda;

	(*comparacoes)++;
	if (direita < n && arr[direita] > arr[maior])
		maior = direita;

	if (maior != i)
	{
		(*trocas)++;
		int temp = arr[i];
		arr[i] = arr[maior];
		arr[maior] = temp;
		heapify(arr, n, maior, comparacoes, trocas);
	}
}

void heapSort(int arr[], int n, int *comparacoes, int *trocas)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i, comparacoes, trocas);

	for (int i = n - 1; i >= 0; i--)
	{
		(*trocas)++;
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0, comparacoes, trocas);
	}
}

// Função Insertion Sort
void insertionSort(int arr[], int n, int *trocas, int *comparacoes)
{
	for (int i = 1; i < n; i++)
	{
		int chave = arr[i];
		int j = i - 1;

		(*comparacoes)++;
		while (j >= 0 && arr[j] > chave)
		{
			(*comparacoes)++;
			(*trocas)++;
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = chave;
		(*trocas)++;
	}
}

// Função para gerar um relatório
void gerarRelatorio(FILE *relatorio, const char *algoritmo, int comparacoes, int trocas, float tempo, int lista[], int tamanho)
{
	fprintf(relatorio, "Algoritmo: %s\n", algoritmo);
	fprintf(relatorio, "Número de comparações: %i\n", comparacoes);
	fprintf(relatorio, "Número de trocas de posição: %i\n", trocas);
	fprintf(relatorio, "Tempo (em segundos): %f\n\n", tempo);

	fprintf(relatorio, "Base de dados ordenada: [");
	for (int i = 0; i < tamanho; i++)
	{
		fprintf(relatorio, "%d", lista[i]);
		if (i < tamanho - 1)
		{
			fprintf(relatorio, ", ");
		}
	}
	fprintf(relatorio, "]\n\n");
}

// Função para abrir um arquivo e retornar o ponteiro para ele, com tratamento de erros
FILE *abrirArquivo(const char *caminho, const char *modo)
{
	FILE *arquivo = fopen(caminho, modo);
	if (arquivo == NULL)
	{
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}
	return arquivo;
}

int main()
{
	int valor, tamanho;
	int trocas = 0, comparacoes = 0;
	int sairPrograma = 0; // Variável de controle para sair do programa
	float tempo; // Variável para armazernar o tempo de execução

	setlocale(LC_ALL, "Portuguese");

	printf("\n=== Programa de Análise de Algoritmos de Ordenação ===\n");
	printf("Este programa permite analisar o desempenho de algoritmos de ordenação.\n");

	while (!sairPrograma)
	{
		char *tamanhos[] = {"1k", "5k", "10k", "50k", "100k"};
		int tamanhosInteiros[] = {1000, 5000, 10000, 50000, 100000};
		char *duplicidade[] = {"Com Duplicidade", "Sem Duplicidade"};
		char *ordem[] = {"Concavo-DecresceCresce", "Convexo-CresceDescresce", "Crescente", "Descrescente"};
		char *abreviacoesOrdem[] = {"concv", "convx", "cresc", "decre"};
		char *duplicidadeOrdem[] = {"dup", "uni"};

		printf("Selecione o tamanho da base de dados:\n\n");
		for (int i = 0; i < 5; i++)
		{
			printf("%d. %s\n", i + 1, tamanhos[i]);
		}
		printf("\nNúmero do tamanho (1-5): ");
		scanf("%d", &valor);

		if (valor < 1 || valor > 9)
		{
			printf("\nOpção inválida!\n\n");
			continue; // Volta ao início do loop para escolher um tamanho válido
		}

		printf("\nSelecione a duplicidade:\n\n");
		printf("1. Com Duplicidade\n");
		printf("2. Sem Duplicidade\n");
		printf("\nNúmero da duplicidade (1-2): ");
		int duplicidadeValor;
		scanf("%d", &duplicidadeValor);

		if (duplicidadeValor < 1 || duplicidadeValor > 2)
		{
			printf("Opção inválida!\n");
			return 1;
		}

		printf("Selecione a ordem:\n\n");
		printf("1. Concavo-DecresceCresce\n");
		printf("2. Convexo-CresceDescresce\n");
		printf("3. Crescente\n");
		printf("4. Descrescente\n\n");
		printf("Número da ordem (1-4): ");
		int ordemValor;
		scanf("%d", &ordemValor);

		if (ordemValor < 1 || ordemValor > 4)
		{
			printf("Opção inválida!\n");
			return 1;
		}

		printf("\nSelecione o sufixo do arquivo (0 a 9): ");
		int arquivoSufixo;
		scanf("%d", &arquivoSufixo);

		if (arquivoSufixo < 0 || arquivoSufixo > 9)
		{
			printf("Sufixo inválido!\n");
			return 1;
		}

		tamanho = tamanhosInteiros[valor - 1];

		// Constrói o caminho do arquivo de dados com base nas seleções do usuário
		char caminhoArquivo[256];
		snprintf(caminhoArquivo, sizeof(caminhoArquivo), "dados/%s/%s/%s/dt%s%s%s%d.txt",
		 tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1], abreviacoesOrdem[ordemValor - 1],
		 tamanhos[valor - 1], duplicidadeOrdem[duplicidadeValor - 1], arquivoSufixo);

		printf("\nBase de dados selecionada com tamanho %s, %s e %s.\n\n", tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1]);

		// Abre o arquivo
		FILE *arqNome = abrirArquivo(caminhoArquivo, "r");

		int *lista = (int *)malloc(tamanho * sizeof(int));

		// Variáveis para armazenar tempo
		float beginBubble, endBubble, tempoBubble;
		float beginMerge, endMerge, tempoMerge;
		float beginQuick, endQuick, tempoQuick;

		// Verificação se o arquivo foi devidamente selecionado
		if (arqNome == NULL)
		{
			printf("Erro ao abrir o arquivo. Certifique-se de que o caminho e o nome do arquivo estão corretos.\n");
			return 1; // Encerra o programa com um código de erro
		}

		// O arquivo foi aberto com sucesso, podemos continuar a leitura
		int i = 0;
		int numeroLido;

		while (i < tamanho && fscanf(arqNome, "%d", &numeroLido) != EOF)
		{
			if (numeroLido != 0)
			{
				lista[i] = numeroLido;
				i++;
			}
		}

		tamanho = i;

		char *nomeDoArquivo = strrchr(caminhoArquivo, '//');
		if (nomeDoArquivo != NULL)
		{
			nomeDoArquivo++; // Avance para o primeiro caractere após a última barra invertida
		}
		else
		{
			// Se não houver barra invertida no caminho, use o caminho inteiro como nome do arquivo
			nomeDoArquivo = caminhoArquivo;
		}

		// Imprime a base de dados selecionada
		printf("Dados da base de dados: [");
		for (int i = 0; i < tamanho; i++)
		{
			printf("%d", lista[i]);
			if (i < tamanho - 1)
			{
				printf(", ");
			}
		}
		printf("]\n\n");

		// Adicionar a extensão ".txt" ao nome do arquivo
		char nomeDoRelatorio[256];
		snprintf(nomeDoRelatorio, sizeof(nomeDoRelatorio), "relatorios\\relatorio_%s.txt", nomeDoArquivo);

		FILE *relatorio = abrirArquivo(nomeDoRelatorio, "w");
		fprintf(relatorio, "Relatório de Análise de Algoritmos de Ordenação\n\n");
		fprintf(relatorio, "Base de dados selecionada com tamanho %s, %s e %s.\n\n", tamanhos[valor - 1], duplicidade[duplicidadeValor - 1], ordem[ordemValor - 1]);
		fprintf(relatorio, "Caminho do arquivo: %s\n\n", caminhoArquivo);
		fprintf(relatorio, "Base de dados original: [");
		for (int i = 0; i < tamanho; i++)
		{
			fprintf(relatorio, "%d", lista[i]);
			if (i < tamanho - 1)
			{
				fprintf(relatorio, ", ");
			}
		}
		fprintf(relatorio, "]\n\n");
		fclose(relatorio);

		int sairBaseDados = 0;

		while (!sairBaseDados)
		{
			printf("Selecione o algoritmo de organização:\n");
			printf("1. Bubble Sort;\n");
			printf("2. Merge Sort;\n");
			printf("3. Quick Sort;\n");
			printf("4. Heap Sort;\n");
			printf("5. Insertion Sort;\n");
			printf("\nNúmero do algoritmo (ou 0 para sair da base de dados atual): ");

			if (scanf("%d", &valor) != 1)
			{
				printf("\nEntrada inválida! Insira um número correspondente à opção desejada.\n\n");
				while (getchar() != '\n')
					; // Limpa o buffer de entrada
				continue;
			}

			// Extrair o nome do arquivo do caminho
			char *nomeDoArquivo = strrchr(caminhoArquivo, '//');
			if (nomeDoArquivo != NULL)
			{
				nomeDoArquivo++; // Avance para o primeiro caractere após a última barra invertida
			}
			else
			{
				// Se não houver barra invertida no caminho, use o caminho inteiro como nome do arquivo
				nomeDoArquivo = caminhoArquivo;
			}

			// Adicionar a extensão ".txt" ao nome do arquivo
			char nomeDoRelatorio[256];
			snprintf(nomeDoRelatorio, sizeof(nomeDoRelatorio), "relatorios\\relatorio_%s.txt", nomeDoArquivo);

			FILE *relatorio = abrirArquivo(nomeDoRelatorio, "a"); // Abra o arquivo de relatório em modo de anexação
			fprintf(relatorio, "Algoritmo: ");					  // Indique qual algoritmo está sendo registrado
			switch (valor)
			{
			case 1:
				// Chama Bubble Sort e inicia timer
				beginBubble = clock();
				bubbleSort(lista, tamanho, &trocas, &comparacoes);
				imprimirArray(lista, tamanho);
				endBubble = clock();
				tempoBubble = (float)(endBubble - beginBubble) / CLOCKS_PER_SEC;

				gerarRelatorio(relatorio, "Bubble Sort", comparacoes, trocas, tempoBubble, lista, tamanho);
				mostrarEstatisticas(comparacoes, trocas, tempoBubble);

				break;

			case 2:
				// Chama o Merge Sort e inicia o timer
				beginMerge = clock();
				mergeSort(lista, 0, tamanho - 1, &trocas, &comparacoes);
				imprimirArray(lista, tamanho);
				endMerge = clock();
				tempoMerge = (float)(endMerge - beginMerge) / CLOCKS_PER_SEC;

				gerarRelatorio(relatorio, "Merge Sort", comparacoes, trocas, tempoMerge, lista, tamanho);
				mostrarEstatisticas(comparacoes, trocas, tempoMerge);
				break;

			case 3:
				// Chama o Quick Sort e inicia o timer
				beginQuick = clock();
				quickSort(lista, 0, tamanho - 1, &trocas, &comparacoes);
				imprimirArray(lista, tamanho);
				endQuick = clock();
				tempoQuick = (float)(endQuick - beginQuick) / CLOCKS_PER_SEC;

				gerarRelatorio(relatorio, "Quick Sort", comparacoes, trocas, tempoQuick, lista, tamanho);
				mostrarEstatisticas(comparacoes, trocas, tempoQuick);

				break;


			case 4:
				heapSort(lista, tamanho, &trocas, &comparacoes);
			mostrarEstatisticas(comparacoes, trocas, tempo);
			break;

			case 5:
				insertionSort(lista, tamanho, &trocas, &comparacoes);
			mostrarEstatisticas(comparacoes, trocas, tempo);
			break;
			case 0:
				sairBaseDados = 1; // Define a variável "sair" como 1 para sair do loop
				break;


			default:
				printf("\nOpção inválida! Escolha as opções listadas (apenas o número).\n\n");
				break;
			}


			// Pergunta ao usuário se deseja selecionar outra base de dados
			printf("Deseja selecionar outra base de dados? (0 para sair ou qualquer outro número para continuar): ");
			int resposta;
			scanf("%d", &resposta);
			if (resposta == 0)
			{
				sairBaseDados = 1; // Define a variável "sairBaseDados" como 1 para sair do loop
			}
		}

		// Fecha o arquivo utilizado
		fclose(arqNome);

		// Reinicie as variáveis de controle para selecionar uma nova base de dados
		trocas = 0;
		comparacoes = 0;

		// Libera a memória alocada dinamicamente quando não for mais necessária
		free(lista);

		printf("\nDeseja sair do programa? (0 para sair ou qualquer outro número para continuar): ");
		int resposta;
		scanf("%d", &resposta);
		if (resposta == 0)
		{
			sairPrograma = 1;
		}
	}

	printf("\nObrigado por usar o nosso programa! Esperamos que tenha sido útil.\n");

	return 0; // Encerra o programa
}
