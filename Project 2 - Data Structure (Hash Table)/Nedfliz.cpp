#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>
#define SIZE 100

int total=0;

struct Node{
	char id[10];
	char title[100];
	char genre[100];
	float rating;
	int year;
	Node* next;
	Node* prev;
} *head[SIZE], *tail[SIZE];

int hash(const char id[]){
	int result = id[4]+id[2]-id[3];
	return result%SIZE;
}

Node* createNode(const char title[], const char genre[], float rating, int year, const char id[]){
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->title, title);
	strcpy(newNode->genre, genre);
	newNode->rating = rating;
	newNode->year = year;
	strcpy(newNode->id, id);
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

void push(const char title[], const char genre[], float rating, int year, const char id[]){
	int index =  hash(id);
	Node* newNode = createNode(title, genre, rating, year, id);
	if (head[index]==NULL)
	{
		head[index] = tail[index] = newNode;
	}
	else
	{
		tail[index]->next = newNode;
		newNode->prev = tail[index];
		tail[index] = newNode;
	}
}

void pop(const char id[]){

	int index = hash(id);
	if (head[index]==NULL)
	{
		printf("Movie not found !!!\n");
		return;
	} 
	else 
	{
		Node* temp = head[index];
		while (temp!=NULL && strcmp(temp->id, id)!=0)
		{
			temp = temp->next;
		}

		if (temp==NULL) 
		{
			printf("Movie not found !!!\n");
			return;
		} 
		else 
		{
			printf("%s - %s deleted !!!\n", temp->id, temp->title);
			if (temp == head[index] && temp == tail[index])
			{
				head[index] = tail[index] = NULL;
				free(temp);
			}
			else if (temp == head[index])
			{
				head[index] = head[index]->next;
				head[index]->prev = NULL;
				free(temp);
			}
			else if (temp == tail[index])
			{
				tail[index] = tail[index]->prev;
				tail[index]->next = NULL;
				free(temp);
			}
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
			}
		}
	}
}

void add(){
	printf("ADD NEW MOVIE\n");
	printf("-------------\n");
	char title[100];
	do{
		printf("Input Movie Title [LENGTH : 5 -20]\n> ");
		scanf("%[^\n]", title);
		getchar();
	} while (strlen(title)>20 || strlen(title)<5);
	
	char genre[100];
	do{
		printf("Input Movie Genre [Adventure | Romance | Comedies] (CASE SENSITIVE)\n> ");
		scanf("%[^\n]", genre);
		getchar();
	} while (strcmp(genre, "Adventure")!=0 && strcmp(genre, "Romance")!=0 && strcmp(genre, "Comedies")!=0);
	
	float rating;
	do{
		printf("Input Movie's Rating [RANGE : 0.0 - 5.0]\n> ");
		scanf("%f", &rating);
		getchar();
	} while (rating<0 || rating>5);
	
	int year;
	do{
		printf("Input Movie's Published Year [RANGE : 1900 - 2020]\n> ");
		scanf("%d", &year);
		getchar();
	} while (year<1900 || year>2020);
	
	char id[10];
	if (strcmp(genre, "Adventure")==0)
	{
		id[0]='A';
		id[1]='E';
	}
	else if (strcmp(genre, "Romance")==0)
	{
		id[0]='R';
		id[1]='E';
	}
	else if (strcmp(genre, "Comedies")==0)
	{
		id[0]='C';
		id[1]='S';
	}
	char id2[10];
	sprintf(id2, "%d", total);
	for (int i=4, j=strlen(id2)-1; i>1; i--, j--)
	{
		if (j>=0)
		{
			id[i] = id2[j];
		}
		else
		{
			id[i] = '0';
		}
	}
	id[5] = '\0';
	
	push(title, genre, rating, year, id);
	total++;
	printf("New movie with ID [%s] has been added!\n", id);
	printf("Press enter to continue. . .");
	getchar();
}

void view(){
	printf("LIST OF MOVIE\n");
	printf("-------------\n");
	int flag = 0;
	for (int i=0; i<SIZE; i++)
	{
		Node* current = head[i];
		while(current!=NULL)
		{
			printf("ID      : [%s]\n", current->id);
			printf("TITLE   : %s\n", current->title);
			printf("GENRE   : %s\n", current->genre);
			printf("RATING  : %.1f\n", current->rating);
			printf("YEAR    : %d\n", current->year);
			printf("\n");
			current=current->next;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("No data !!!\n");
	}
	printf("Press enter to continue. . .");
	getchar();
}

bool validID(const char id[])
{
	if ((id[0]=='A' && id[1]=='E') || (id[0]=='R' && id[1]=='E') || (id[0]=='C' && id[1]=='S'))
	{
		return true;
	}
	else
	{
		printf("ID must start with either 'AE' or 'RE' or 'CS'\n");
		return false;
	}
}

void remove(){
	printf("DELETE MOVIE\n");
	printf("------------\n");
	int flag = 0;
	for (int i=0; i<SIZE; i++)
	{
		Node* current = head[i];
		while(current!=NULL)
		{
			printf("ID      : [%s]\n", current->id);
			printf("TITLE   : %s\n", current->title);
			printf("GENRE   : %s\n", current->genre);
			printf("RATING  : %.1f\n", current->rating);
			printf("YEAR    : %d\n", current->year);
			printf("\n");
			current=current->next;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("No data !!!\n");
	}
	else
	{
		char id[10];
		do{
			printf("Choose The Movie's ID [AEXXX | REXXX | CSXXX]\n> ");
			scanf("%s", id);
			getchar();
		} while (!validID(id));
		
		 pop(id);
	}
	printf("Press enter to continue. . .");
	getchar();
}

int main(){
	while (true)
	{
		printf("NEDFLIZ\n");
		printf("1. Add New Movie\n");
		printf("2. View Movies\n");
		printf("3. Delete Movie\n");
		printf("4. Exit\n");
		int input;
		do{
			printf("Choose [1 - 4] > ");
			scanf("%d", &input);
			getchar();
		} while (input<1 || input>4);
		switch(input){
			case 1:
				add();
				break;
			case 2:
				view();
				break;
			case 3:
				remove();
				break;
			case 4:
				return 0;			
		}
	}
	return 0;
}
