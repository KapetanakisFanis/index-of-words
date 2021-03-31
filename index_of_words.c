#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BUFFER_SIZE 1000


typedef struct position{
	int *row;
	int *column;
	struct position *nextposition;
}POSITION;

typedef struct myfile{
	int *nummyfile;
	struct myfile *nextmyfile;
	POSITION *nextposition;
}MYFILE;

typedef struct tree{
	char word[15];
	struct tree *left;
	struct tree *right;
	MYFILE *nextmyfile;
}TREE;



void hash(TREE *[]);
void insert(TREE *[], char *,int);
void preOrder (TREE *[],TREE *);
void findelement(TREE *,char *, int *);

int main(int argc, char *argv[]) {
TREE *pin[1024]={NULL};
int i, check;
char find[15];
hash(pin);
       
		for(i=0;i<1024;i++){
			preOrder(pin,pin[i]);
		}
		
		printf("Give a word\n");
		scanf("%s",find);
		for(i=0;i<1024;i++){
			findelement(pin[i],find,&check);
		}
		if(check!=1) {printf("Word '%s' not found!\n",find); }
		
	return 0;
}
void hash(TREE *pin[])
{
	int i,j, h=0;
   	char buf[15], namemyfile[20];
   	FILE *fp;
   	for(j=1;j<4;j++){
   		sprintf(namemyfile, "myfile%d.txt",j);
  fp = fopen(namemyfile,"r"); 
    
        while( fscanf(fp, "%s", buf) != EOF )
        {			
        for(i=1;i<=strlen(buf);i++) {
		h = h + pow(2,strlen(buf)-i)*(buf[i-1]);
	    }
	    h = h%1024;
	    insert(pin,buf,h);
  
	    h=0;		 
		} 

		fflush(stdin);
		fclose(fp);
}
}


void insert(TREE *pin[], char *buf,int h) 
{TREE *ptr, *dkt;

if(pin[h]==NULL){
pin[h] = (TREE *) malloc(sizeof(TREE));
strcpy(pin[h] -> word, buf);
pin[h] -> right = NULL;
pin[h] -> left = NULL;
pin[h] -> nextmyfile = NULL;
}
else{
ptr = pin[h];
dkt = (TREE *) malloc(sizeof(TREE));
strcpy(dkt -> word, buf);
dkt -> right = NULL;
dkt -> left = NULL;
dkt-> nextmyfile=NULL;
while(strcmp(buf, ptr -> word)!=0) 
{if (strcmp(buf, ptr -> word)<0) 
{if (ptr -> left != NULL)
ptr = ptr -> left;
else
ptr -> left = dkt; }
if (strcmp(buf, ptr -> word)>0) 
{if (ptr -> right != NULL)
ptr = ptr -> right;
else ptr -> right = dkt; }}
} 
}

void preOrder (TREE *pin[],TREE *q) 
{	 
POSITION *po;
MYFILE *ar;
int count, j, cou;
int line, col;
char str[BUFFER_SIZE], namemyfile[20];
char *pos;
FILE *fp;
    
if (q!=NULL) 
{  
for(j=1;j<4;j++)
{sprintf(namemyfile,"myfile%d.txt",j);
 line=-1; 
 col=-1;
 cou=0;
 count=0;
 fp = fopen(namemyfile,"r");	
 while ((fgets(str, BUFFER_SIZE, fp)) != NULL)
    { line += 1;
        pos = strstr(str, q->word);
        if (pos != NULL)
        {col = (pos - str);
        
       if(q->nextmyfile==NULL) {
       	q->nextmyfile = (MYFILE*)malloc(sizeof(MYFILE));
        q->nextmyfile -> nummyfile = j;
        q->nextmyfile -> nextmyfile = NULL;
        ar = q->nextmyfile;
	    cou=1;}
       
       if((ar!=NULL) && (cou==0)) {
       	  ar ->nextmyfile = (MYFILE*)malloc(sizeof(MYFILE));
       	  ar = ar->nextmyfile;
       	  ar -> nummyfile = j;
       	  ar -> nextmyfile = NULL;
		  cou=1;}
          
          
        if(count==0)
		{ 
		ar -> nextposition = (POSITION*)malloc(sizeof(POSITION));	
          ar -> nextposition -> row = line+1;
          ar -> nextposition -> column = col+1;
          ar -> nextposition -> nextposition = NULL;
          po = ar -> nextposition;
        count++;}
        else{
			po -> nextposition = (POSITION*)malloc(sizeof(POSITION));
            po = po -> nextposition; 
            po -> row = line+1;
            po -> column = col+1;
            po -> nextposition= NULL;
		    }    
}}
    
	fflush(stdin);
	fclose(fp);
}           

preOrder(pin,q->left); 
preOrder(pin,q->right); } 
}


void findelement(TREE *q,char *find, int *check)
{ if (q!=NULL)
{if(strcmp(q->word,find)==0) 
{  *check = 1; 
  printf("The word '%s' is found at:\n",find);
  while(q->nextmyfile!=NULL)
  {printf("Myfile %d: ",q->nextmyfile->nummyfile);
    while(q->nextmyfile->nextposition!=NULL)
    {printf("(line: %d and column: %d) ",q->nextmyfile->nextposition->row,q->nextmyfile->nextposition->column);
    q->nextmyfile->nextposition = q->nextmyfile->nextposition->nextposition;
    }
  q->nextmyfile = q->nextmyfile->nextmyfile;
  printf("\n");	
  } 
}

findelement(q->left,find,check); 
findelement(q->right,find,check); }
}
