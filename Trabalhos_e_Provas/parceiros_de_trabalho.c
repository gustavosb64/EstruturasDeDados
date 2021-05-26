#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parceiros_de_trabalho.h"

//~ESTRUTURAS
struct node_{
    struct user_ *user; //aponta ao usuário em questão
    struct node_ *next; //aponta ao próximo nó da lista
};

struct message_{
    char *info;     //contém a mensagem propriamente dita
    User *sender;   //aponta ao usuário que enviou a mensagem
};

struct user_{
    char *nickname;             //string de apelido
    char *name;                 //string de nome

    struct list_ *requests;     //aponta à lista de REQUISIÇÕES do usuário em questão
    struct list_ *coworkers;    //aponta à lista de PARCEIROS do usuário em questão

    Message **messages;         //ponteiro duplo: cada elemento aponta a uma struct message_
    int n_messages;             //quantidade de mensagens recebidas pelo usuário
};

struct list_{
    Node *first;    //aponta ao primeiro nó
    Node *last;     //aponta ao último nó
};

//~FUNÇÕES
List* CreateList(){
    List *list = (List *) malloc(sizeof(List));
    //Ponteiros first e last são setados em NULL quando lista vazia por padrão
    list->first = NULL;
    list->last = NULL;

    return list;
}

int IsEmpty(List *list){
    if (list == NULL || list->first == NULL) return 1;
    else return 0;
}

//Retorna o endereço do usuário encontrado; NULL caso não encontre
User* SearchUser(List *list, char *nickname){
    if (list == NULL) return NULL;

    Node *aux_node = list->first;
    while (aux_node != NULL){
        if (!strcmp(aux_node->user->nickname,nickname)) return aux_node->user;
        aux_node = aux_node->next;
    }

    return NULL;
}

//Adiciona o usuário user ao final da lista list. 
  //Aloca memória com CreateList, caso necessário (motivo do retorno ser List*)
List* AddUser(User *user, List *list){
    Node *node = (Node *) malloc(sizeof(Node));
    if(node == NULL) return NULL;

    node->user = user;
    node->next = NULL;

    if (list == NULL)
        list = CreateList(); 

    if (IsEmpty(list)) 
        list->first = node;
    else 
        list->last->next = node; 

    list->last = node;

    return list;
}

//Remove o nó referente a user da lista list.
List* RemoveNode(User *user, List *list){

    if (list == NULL) return NULL;
        
    Node *aux_node = list->first;
    
    if(aux_node->user == user){
        list->first = aux_node->next;
        aux_node->next = NULL;
        free(aux_node);

        //Caso o nó liberado seja o primeiro, liberar a memória de list e fazê-la apontar a NULL
        if(list->first == NULL){
            free(list);
            list = NULL;
        }
        
        return list;
    }

    while (aux_node != NULL){
        if (aux_node->next->user == user){
            Node *aux_node2 = aux_node->next;
            aux_node->next = aux_node2->next;
            aux_node2->next = NULL;
            free(aux_node2);

            return list;
        }
        aux_node = aux_node->next;
    }

    return list;
}

//Função de cadastro
int SignUp(char *name, char *nickname, List *allList){

    //Garantindo que string não seja vazia. 32 equivale ao espaço em branco em ASCII
    int i;
    for (i=0; i < strlen(name); i++) 
        if (name[i] != 32) break;
    if (i == strlen(name)) return 3;

    for (i=0; i < strlen(nickname); i++) 
        if (nickname[i] != 32) break;
    if (i == strlen(nickname)) return 3;

    //Checando se usuário já não foi cadastrado
    if (SearchUser(allList, nickname) != NULL) return 1;

    User *user = (User *) malloc(sizeof(User));
    if (user == NULL) return 2;

    user->nickname = nickname;
    user->name = name;

    //Todas as sublistas do usuário, quando vazias, apontam a NULL por padrão
    user->requests = NULL;
    user->coworkers = NULL;
    user->messages = NULL;
    user->n_messages = 0;

    allList = AddUser(user, allList);

    return 0;
}

//Função para enviar pedidos de parceria
int Request(char *srcNickname, char *destNickname, List *allList){

    if (IsEmpty(allList)) return 1; 

    User *destUser = SearchUser(allList, destNickname); //usuário a quem será enviado o pedido
    if (destUser == NULL) return 2;

    User *srcUser = SearchUser(allList, srcNickname);   //usuário que enviou o pedido
    if (srcUser == NULL) return 3;

    //Checa se há pedido repetido
    if (SearchUser(destUser->requests, srcUser->nickname) == NULL){

        //Checa se o destUser já pediu parceria a srcUser
        if (SearchUser(srcUser->requests, destUser->nickname) == NULL)
            destUser->requests = AddUser(srcUser, destUser->requests);

        //Caso o pedido já tenha sido feito, ambos tornam-se parcieiros automaticamente
        else{
            srcUser->coworkers = AddUser(destUser, srcUser->coworkers);
            destUser->coworkers = AddUser(srcUser, destUser->coworkers);

            srcUser->requests = RemoveNode(destUser, srcUser->requests);

            printf("\n\t%s já havia requisitado parceria, portanto foi adicionado à lista de parceiros.\n\n",destNickname);
        }
    }
    else printf("\tPedido já feito e aguardando avaliação.\n\n");

    return 0;
}

//Função para avaliar os pedidos de parceria
int SeeRequests(char *srcNickname, List *allList){

    if (IsEmpty(allList)) return 1;
 
    User *srcUser = SearchUser(allList, srcNickname);   //usuário que pediu para ver os pedidos de parceria
    if (srcUser == NULL) return 2;

    if (srcUser->requests == NULL) return 3;

    char op; //armazena a opção do usuário
    while (srcUser->requests != NULL){ 
        User *destUser = srcUser->requests->first->user; //primeiro usuário da lista de pedidos

        printf("\t%s deseja ser seu(ua) parceiro(a). Aceitar? (Y/n)\n\t", destUser->nickname);
        scanf(" %c",&op);

        //Caso aceite, srcUser é adicionado à lista de parceiros de destUser e vice-versa
        if (op == 'y' || op == 'Y'){
            srcUser->coworkers = AddUser(destUser, srcUser->coworkers);
            destUser->coworkers = AddUser(srcUser, destUser->coworkers);
            op = -1;
        }
        else if (op == 'n' || op == 'N') op = -1;
        
        //Caso a entrada seja inválida, retornar ao início do while sem alterar a lista
        if (op != -1) printf("\tERRO! Opcao invalida!\n");

        //Senão, remover o usuário da lista de pedidos de srcUser
        else{
            Node *aux = srcUser->requests->first->next;
            free(srcUser->requests->first);
            srcUser->requests->first = aux;

            //Caso o usuário removido seja o primeiro, srcUser->requests passa a apontar a NULL (padrão estabelecido ao código)
            if (srcUser->requests->first == NULL){
                free(srcUser->requests);
                srcUser->requests = NULL;
            }

        }

    } 
    printf("\n");

    return 0;
}

//Função de remover parceiro
int RemoveCoworker(char *srcNickname, char *destNickname, List *allList){

    if (IsEmpty(allList)) return 1; 

    User *srcUser = SearchUser(allList, srcNickname);   //usuário que deseja remover um parceiro
    if (srcUser == NULL) return 2;
    
    //Procura o usuário de apelido destNickname na lista de parceiros de srcUser
    User *destUser = SearchUser(srcUser->coworkers, destNickname);  
    if(destUser == NULL) return 3;

    //Caso encontre, remove o nó referente ao destUser de srcUser->coworkers e vice-versa
    srcUser->coworkers = RemoveNode(destUser, srcUser->coworkers);
    destUser->coworkers = RemoveNode(srcUser, destUser->coworkers);
    
    return 0;
}

//Função de enviar mensagens
int SendMessage(char *string, char *srcNickname, char *destNickname, List *allList){

    if (IsEmpty(allList)) return 1; 

    User *destUser = SearchUser(allList, destNickname); //usuário a quem a mensagem será enviada
    if (destUser == NULL) return 2;

    User *srcUser = SearchUser(allList, srcNickname);   //usuário que envia a mensagem
    if (srcUser == NULL) return 3;

    //Pode-se apenas enviar mensagens a parceiros
    if (SearchUser(destUser->coworkers, srcNickname) == NULL) return 4;

    //Checa se mensagem não é vazia
    int k;
    for (k=0; k < strlen(string); k++) 
        if (string[k] != 32) break;
    if (k == strlen(string)) return 3;

    //Realoação de memória é feita a cada mensagem recebida
    if (destUser->messages == NULL)
        destUser->messages = (Message **) malloc(sizeof(Message *));
    else{
        destUser->messages = (Message **) 
            realloc(destUser->messages, (destUser->n_messages + 1) * sizeof(Message *));
    }

    int i = destUser->n_messages;
    destUser->messages[i] = (Message *) malloc(sizeof(Message));

    destUser->messages[i]->info = string;
    destUser->messages[i]->sender = srcUser;
    
    destUser->n_messages++;
        
    return 0;
}

int DeleteMessage(Message *message){
    
    free(message->info);
    message->sender = NULL;
    free(message);
    
    return 0;
}

//Função para imprimir mensagens
int PrintMessages(char *nickname, List *allList){
    
    User *user = SearchUser(allList, nickname); //usuário que pediu para ver as mensagens
    if (user == NULL) return 1;

    printf("\tMENSAGENS RECEBIDAS:\n");
    int i = (user->n_messages - 1);
    if (i < 0) printf("\t |-> [NENHUMA MENSAGEM NO MOMENTO]\n");
    while(i >= 0){
        printf("\t|-> %s (%s):\n",user->messages[i]->sender->nickname, user->messages[i]->sender->name);
        printf("\t    |->'%s'\n\n",user->messages[i]->info);
        DeleteMessage(user->messages[i]);
        user->messages = (Message **) 
            realloc(user->messages, (user->n_messages) * sizeof(Message *));
        user->n_messages--;
        i--;
    }
    
    return 0;
}

//Função para imprimir sugestões de parceria
int Suggestions(char *nickname, List *allList){

    if(IsEmpty(allList)) return 1;

    User *user = SearchUser(allList, nickname);
    if (user == NULL) return 2;

    if (user->coworkers == NULL) return 3;  //caso ele não possua parceiros, não há sugestões

    //flag de controle do resultado. Caso ela continue 0 ao longo de todo while, não há parceiros a serem recomendados
    int flag = 0;
    Node *aux_user = user->coworkers->first;
    while (aux_user != NULL){

        if (aux_user->user->coworkers != NULL){
            Node *aux_coworker = aux_user->user->coworkers->first;
            //percorre cada parceiro de user para verificar se ele possui parceiros NÃO em comum para recomendar
            while (aux_coworker != NULL){
                if (SearchUser(user->coworkers, aux_coworker->user->nickname) == NULL && aux_coworker->user != user){
                    printf("\t  |-> %s (%s)\n",aux_coworker->user->nickname, aux_coworker->user->name);
                    flag = 1;   //flag recebe 1 para indicar que houve recomendações
                }
                aux_coworker = aux_coworker->next;
            }
        }
        aux_user = aux_user->next;
    }
    if (!flag) return 3;    //se for 0, retorno igual ao de user->coworkers==NULL
    printf("\n");

    return 0;

}

//Função para imprimir os usuários da lista com seus respectivos parceiros
int PrintList(List *allList){

    if(IsEmpty(allList)) return 1;

    printf("Listagem de usuários e seus respectivos parceiros:\n");
    
    Node *aux_node = allList->first;
    while(aux_node!=NULL){
        if (aux_node->user->nickname != NULL)
            printf("\t %s (",aux_node->user->nickname);
        else printf("NULL NICKNAME\n");

        if (aux_node->user->name != NULL)
            printf("%s)\n",aux_node->user->name);
        else printf("NULL NAME\n");
        
        //Percorre a lista de parceiros do usuário em questão
        if (aux_node->user->coworkers != NULL){
            Node *aux_coworker = aux_node->user->coworkers->first;
            while (aux_coworker != NULL){
                printf("\t  |-> %s\n", aux_coworker->user->nickname);
                aux_coworker = aux_coworker->next;
            }
        }
        else printf("\t  |-> [NENHUM PARCEIRO NO MOMENTO]\n");
        aux_node = aux_node->next;
        printf("\n");
    }

    return 0;
}

//Função para deletar todos os nós de uma lista (usada apenas por RebootSystem)
int DeleteAllNodes(List* list){
    Node *aux_node, *aux_node2; 

    if (list != NULL) 
        aux_node = list->first;
    else aux_node = NULL;
     
    while (aux_node != NULL){
        aux_node->user = NULL;
        
        aux_node2 = aux_node; 
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(list);

    return 0;
}

//Função para reiniciar os dados da lista
int RebootSystem(List *allList){
    Node *aux_node = allList->first;

    while(aux_node != NULL){

        for (int i=0; i < aux_node->user->n_messages; i++)
            DeleteMessage(aux_node->user->messages[i]);

        free(aux_node->user->messages);
        aux_node->user->n_messages = 0;
        
        DeleteAllNodes(aux_node->user->requests);    
        DeleteAllNodes(aux_node->user->coworkers);    

        free(aux_node->user->nickname);
        free(aux_node->user->name);

        free(aux_node->user);

        Node *aux_node2 = aux_node;
        aux_node = aux_node2->next;
        free(aux_node2);
    }

    allList->first = NULL;
    allList->last = NULL;
     
    return 0;
}
