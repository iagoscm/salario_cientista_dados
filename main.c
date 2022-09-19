#include <stdio.h>
#include <stdlib.h>


typedef struct Cientista{
    int salario;
    int linha;
    struct Cientista *esquerda;
    struct Cientista *direita;
} Cientista;

void instala(Cientista ** dado, int salario, int linha);
void imprime(Cientista* dado, long int *linhas, char nome[50]);

int contadorLinhas();

int main(int argc, char const *argv[])
{
    int item;
    Cientista *arvore;
    char nome[50];

    // Menu de opções

    do
    {
        printf("**** Menu ****\n 1 - Carregar Arquivos de Dados\n 2 - Emitir Relatório\n 3 - Sair\n Digite o item que deseja acessar: ");
        scanf("%d", &item);

        switch (item)
        {
        case 1:
            printf("Digite o nome do arquivo que deseja carregar: ");
            scanf(" %s", nome);

            FILE *arqOriginal;
            int quantidadeLinhas;
            long int *linhas;
            char ch;
            char primeiraLinha[300];

            quantidadeLinhas = contadorLinhas(nome);

            linhas = (long int *) malloc(quantidadeLinhas * sizeof(long int));

            arqOriginal = fopen(nome, "r");
            fseek(arqOriginal, 0, SEEK_SET);
            fscanf(arqOriginal, "%s", primeiraLinha);
            linhas[0] = ftell(arqOriginal);

            // colunas do arquivo

            int id;
            int work_year, remote_ratio;
            char experience_level[10], employment_type[10], job_title[100], salary_currency[10], employee_residence[10], company_location[10], company_size[10];
            int salary, salary_in_usd;
            while (fscanf(arqOriginal, "%d,%d,%[^,],%[^,],%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%[^\n]", &id, &work_year, experience_level, employment_type, job_title, &salary, salary_currency, &salary_in_usd, employee_residence, &remote_ratio, company_location, company_size) == 12)
            {
                linhas[id+1] = ftell(arqOriginal);
                instala(&arvore,salary_in_usd,id);
            }

            break;

        case 2:
            printf("Ano de trabalho | Experiência | Tipo de emprego | Residência do empregado | Salário em USD | Título do trabalho   \n");
            imprime(arvore, linhas, nome);
            break;

        case 3:
            printf("Sair\n");
            break;

        default:
            printf("Opção inválida!!\n");
            break;
        }
    } while (item != 3);



    return 0;
}

void instala(Cientista ** dado, int salario, int linha) {
    Cientista *temp = NULL;
    if((*dado) != NULL) {
        if (salario <= (*dado)->salario)
        {
            instala(&(*dado)->esquerda, salario, linha);
        } else {
            instala(&(*dado)->direita, salario, linha);
        }
    } else {
        temp = (Cientista *) malloc(sizeof(Cientista));
        temp->esquerda = NULL;
        temp->direita = NULL;
        temp->salario = salario;
        temp->linha = linha;
        *dado = temp;
    }
};

void imprime(Cientista *raiz, long int *linhas, char nome[50]) {
    FILE *arqOriginal;
    arqOriginal = fopen(nome, "r+b");
    char linha[500];
    int id;
    int work_year, remote_ratio;
    char experience_level[10], employment_type[10], job_title[100], salary_currency[10], employee_residence[10], company_location[10], company_size[10];
    int salary, salary_in_usd;
    if(raiz){
        imprime(raiz->esquerda, linhas, nome);
        fseek(arqOriginal, linhas[raiz->linha]+1, SEEK_CUR);
        fscanf(arqOriginal, "%d,%d,%[^,],%[^,],%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%[^\n]", &id, &work_year, experience_level, employment_type, job_title, &salary, salary_currency, &salary_in_usd, employee_residence, &remote_ratio, company_location, company_size);
        printf("%d            | %s          | %s              | %s                      | %d | %s \n", work_year, experience_level, employment_type, employee_residence, salary_in_usd, job_title );
        imprime(raiz->direita, linhas, nome);
    }
}

int contadorLinhas(char nome[]) {
    FILE *fp;
    char linha[300];
    int count = 0;

    fp = fopen(nome, "r");
    fscanf(fp, "%s", linha);
    int id;
    int work_year, remote_ratio;
    char experience_level[10], employment_type[10], job_title[100], salary_currency[10], employee_residence[10], company_location[10], company_size[10];
    int salary, salary_in_usd;
    while (fscanf(fp, "%d,%d,%[^,],%[^,],%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%[^\n]", &id, &work_year, experience_level, employment_type, job_title, &salary, salary_currency, &salary_in_usd, employee_residence, &remote_ratio, company_location, company_size) == 12)
    {
        count++;
    }
    return count;
}
