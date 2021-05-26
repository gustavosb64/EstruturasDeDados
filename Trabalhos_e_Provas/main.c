#include <stdio.h>
#include <stdlib.h>
#include "parceiros_de_trabalho.h"

//DECLARAÇÃO DE FUNÇÕES 
char* readline();
int main_signUp(List *allList);
int main_printUsers(List *allList);
int main_sendRequest(List *allList);
int main_seeRequests(List *allList);
int main_sendMessage(List *allList);
int main_printMessages(List *allList);
int main_suggestions(List *allList);
int main_removeCoworker(List *allList);
int main_rebootSystem(List *allList);

int main(int argc, char *argv[]){

    List *allList = CreateList();   //allList é a lista geral. É criada logo ao início do programa
    int flag = 0;   //flag de opção de entrada do usuário
    while(flag != -1){
        printf("\nCaro usuário, suas opções são:\n");
        printf("\t ");
        for (int i=0; i < 55; i++) printf("-"); 
        printf("\n");
        printf("\t| 1)   cadastrar um usuário\t\t\t\t|\n");
        printf("\t| 2)   listar usuarios cadastrados e suas informacoes\t|\n");
        printf("\t| 3)   pedir para ser parceiro de um usuario\t\t|\n");
        printf("\t| 4)   avaliar lista de pedidos de parceria\t\t|\n");
        printf("\t| 5)   enviar mensagem a um parceiro\t\t\t|\n");
        printf("\t| 6)   ver novas mensagens recebidas\t\t\t|\n");
        printf("\t| 7)   sugerir novas parcerias\t\t\t\t|\n");
        printf("\t| 8)   remover um parceiro\t\t\t\t|\n");
        printf("\t| 9)   reinicializar sistema\t\t\t\t|\n");
        printf("\t| Ou digite -1 para encerrar o sistema.\t\t\t|\n");
        printf("\t ");
        for (int i=0; i < 55; i++) printf("-"); 
        printf("\n");
        printf("\nO que deseja fazer?\n");

        printf("Resposta: ");
        scanf(" %d",&flag);
        getc(stdin); //pega o caractere '\n' remanescente

        //cada opção chama sua respectiva função
        switch (flag){
            case 1:
                main_signUp(allList);
                break;
            case 2:
                main_printUsers(allList);
                break;
            case 3:
                main_sendRequest(allList);
                break;
            case 4:
                main_seeRequests(allList);
                break;
            case 5:
                main_sendMessage(allList);
                break;
            case 6:
                main_printMessages(allList);
                break;
            case 7:
                main_suggestions(allList);
                break;
            case 8:
                main_removeCoworker(allList);
                break;
            case 9:
                main_rebootSystem(allList);
                break;
            case -1:
                main_rebootSystem(allList); //também chama main_rebootSystem para liberar toda a memória na saída
                break;
            default:
                printf("Entrada inválida!\n");
                flag = 0;   //referente a nenhuma das opções, mas dentro da condição do while
                break;
        }
    }

    free(allList);

    return 0;
}

//Função de leitura de linha
#define BUFFER 4096
char *readline() {
    char *string = 0;

    int i = 0;
    do {
        if (i % BUFFER == 0)
         string = (char *) realloc(string, ( (i/BUFFER) + 1) * BUFFER);

        string[i++] = (char) fgetc(stdin); //lê caractere de stdin

    }while (string[i-1] != '\r' && string[i-1] != '\n' && !feof(stdin));

    //após a leitura, string é cortada exatamente ao tamanho usado
    string[i-1] = 0;  
    string = (char *) realloc(string, i);

    return string;
}

int main_signUp(List *allList){
    char *name, *nickname;

    printf("\tInsira seu nome: ");
    name = readline();
    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\n");

    switch(SignUp(name, nickname, allList)){
        case 1:
            printf("\tERRO! Usuário já cadastrado.\n");
            break;

        case 2:
            printf("\tERRO! Memória cheia. Tente mais tarde.\n");
            break;

        case 3:
            printf("\tERRO! Inserção vazia.\n");
            break;

        default:
            printf("Cadastro realizado com sucesso!\n\n");
            break;
    }

    /*neste caso, os campos de memória de name e nickname não são liberados, 
      pois os ponteiros do usuário recém cadastrado apontam a eles*/

    return 0;
}

int main_printUsers(List *allList){
    if (PrintList(allList)) 
        printf("\tNENHUM USUÁRIO CADASTRADO!\n");

    return 0;
}

int main_sendRequest(List *allList){
    char *nickname, *nickname2;

    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\tInsira o apelido de quem deseja estabelecer uma parceria: ");
    nickname2 = readline();
    printf("\n");
                                                                            
    switch(Request(nickname, nickname2, allList)){
        case 1:
            printf("\tNENHUM USUÁRIO CADASTRADO!\n");
            break;
                                                                            
        case 2:
            printf("\tERRO! %s não cadastrado!\n", nickname2);
            break;
                                                                            
        case 3:
            printf("\tERRO! %s não cadastrado!\n", nickname);
            break;
                                                                            
        default:
            printf("\tRequisição enviada com sucesso!\n", nickname);
            break;
    }
    free(nickname);                                                     
    free(nickname2);

    return 0;
}

int main_seeRequests(List *allList){
    char *nickname;
    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\n");
    
    switch(SeeRequests(nickname, allList)){
        case 1:
            printf("\tERRO! Lista vazia!\n");
            break;
                                                         
        case 2:
            printf("\tERRO! Usuário cadastrado!\n");
            break;
                                                         
        case 3:
            printf("\tNENHUMA REQUISIÇÃO NO MOMENTO\n");
            break;
    }
    free(nickname);

    return 0;
}

int main_sendMessage(List *allList){
    char *nickname, *nickname2;

    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\tInsira o apelido de quem deseja enviar uma mensagem: ");
    nickname2 = readline();
                                                                       
    char *string;
    printf("\tEscreva sua mensagem: \n\t");
    string = readline();
                                                                       
    switch(SendMessage(string, nickname, nickname2, allList)){
        case 1:
            printf("\tLista vazia!\n");
            break;
                                                                       
        case 2:
            printf("\tUsuário %s não encontrado\n",nickname2);
            break;
                                                                       
        case 3:
            printf("\tUsuário %s não encontrado\n",nickname);
            break;
                                                                       
        case 4:
            printf("\tVocê e %s não são parceiros!\n", nickname2);
            break;
                                                                       
        default:
            printf("\n\tMensagem enviada com sucesso!\n",nickname);
            break;
    }
    free(nickname);
    free(nickname2);

    return 0;
}

int main_printMessages(List *allList){
    char *nickname;

    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\n");
                                                  
    if(PrintMessages(nickname, allList))
        printf("ERRO! Usuário não cadastrado\n");
                                                  
    free(nickname);

    return 0;
}

int main_suggestions(List *allList){
    char *nickname;

    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\n");
                                                             
    printf("\tSUGESTÕES DE PARCERIA:\n");
    switch(Suggestions(nickname, allList)){
        case 1:
            printf("\tERRO! Lista vazia!\n");
            break;
                                                             
        case 2:
            printf("\tERRO! Usuário não cadastrado!\n");
            break;
                                                             
        case 3:
            printf("\t|-> [Nenhuma sugestão no momento]\n");
            break;
                                                             
        default:
            break;
    }
    free(nickname);
    
    return 0;
}

int main_removeCoworker(List *allList){
    char *nickname, *nickname2;

    printf("\tInsira seu apelido: ");
    nickname = readline();
    printf("\tInsira o apelido de qual parceiro deseja remover: ");
    nickname2 = readline();
                                                                    
    switch(RemoveCoworker(nickname, nickname2, allList)){
        case 1:
            printf("\tNENHUM USUÁRIO CADASTRADO!\n");
            break;
                                                                    
        case 2:
            printf("\tERRO! %s não cadastrado!\n", nickname2);
            break;
                                                                    
        case 3:
            printf("\tERRO! %s não é seu parceiro!\n", nickname);
            break;
    
        default:
           printf("\tParceiro removido com sucesso!\n");
           break;
    }
    free(nickname);
    free(nickname2);

    return 0;
}

int main_rebootSystem(List *allList){
    RebootSystem(allList);
    printf("SISTEMA REINICIADO!\n");

    return 0;
}
