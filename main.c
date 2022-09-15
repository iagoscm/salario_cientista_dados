#include <stdio.h>
#include <stdlib.h>


typedef struct Cientista{
    int salario;
    int linha;
    struct Cientista *esquerda;
    struct Cientista *direita;
} Cientista;

void instala(Cientista ** dado, int salario, int linha);

int main(int argc, char const *argv[])
{
    int item;
    int linhas[609];
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
            char ch;
            char primeiraLinha[300];
            arqOriginal = fopen(nome, "r");
            fscanf(arqOriginal, "%s", primeiraLinha);

            // colunas do arquivo

            int id;
            int work_year, remote_ratio;
            char experience_level[10], employment_type[10], job_title[100], salary_currency[10], employee_residence[10], company_location[10], company_size[10];
            int salary, salary_in_usd;
            while (fscanf(arqOriginal, "%d,%d,%[^,],%[^,],%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%[^,]", &id, &work_year, experience_level, employment_type, job_title, &salary, salary_currency, &salary_in_usd, employee_residence, &remote_ratio, company_location, company_size) != EOF)
            {
                printf("%d\n", salary);
            }
            
            
            break;
        
        case 2:
            printf("Emitir Relatório\n");
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
