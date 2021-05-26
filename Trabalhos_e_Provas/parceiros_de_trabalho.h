#ifndef PARCEIROS_DE_TRABALHO_H
#define PARCEIROS_DE_TRABALHO_H

typedef struct node_ Node;
typedef struct message_ Message;
typedef struct user_ User;
typedef struct list_ List;

List* CreateList();
int IsEmpty(List *allList);
int SignUp(char *name, char *nickname, List *allList);
int Request(char *srcNickame, char *destNickname, List *allList);
int SeeRequests(char *srcNickname, List *allList);
int RemoveCoworker(char *srcNickame, char *destNickname, List *allList);
int SendMessage(char *string, char *srcNickname, char *destNickname, List *allList);
int PrintMessages(char *nickname, List *allList);
int Suggestions(char *nickname, List *allList);
int PrintList(List *allList);
int RebootSystem(List *allList);

#endif
