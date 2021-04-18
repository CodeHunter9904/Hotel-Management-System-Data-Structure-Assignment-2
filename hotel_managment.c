#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int roomno;
	char name[20];
	char phoneno[20];
	char address[20];
	struct node *r,*l;
}*root;


void add(void);
int insert(int);

void list(struct node *);

void del();
struct node* deleteRecord(int ,struct node *);
struct node* inpre(struct node*);
struct node* insuc(struct node*);
int HeightOfTree(struct node*);

void search(void);

void modify();

void SentToTree(void);
void InsertFromFile(int ,char [],char [],char []);
void WriteFile(int ,char [],char [],char []);

void UpdateFile(struct node *);

FILE *f;

int main()
{
    printf("WELCOME..............\n\n");
    printf("\t|| HOTEL A1 PALACE ||\n");
    printf("\t   ---------------\n");
    int i;
    SentToTree();
    while (1)
    {
            printf("\n");
            printf("\t** MAIN MENU **\n\n");
            printf("Please enter your choice for Menu:\n");
            printf("[1]. Book a room\n");
            printf("[2]. View Customer Record\n");
            printf("[3]. Delete Customer Record\n");
            printf("[4]. Search Customer Record\n");
            printf("[5]. Modify Record\n");
            printf("[6]. Exit\n");
            int choice;
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                	system("cls");
                    add();
					break;
                case 2:
                	system("cls");
                    printf("RoomNo\tName\tAddress\tPhoneNo\n");
                    printf("--------------------------------------------\n");
                    list(root);
                    printf("\nPress Any Key To Continue.....\n");
					getch();
					system("cls");
					break;
                case 3:
                	system("cls");
                    del();
                    printf("\nPress Any Key To Continue.....\n");
					getch();
					system("cls");
					break;
                case 4:
                	system("cls");
                    search();
                    printf("\nPress Any Key To Continue.....\n");
					getch();
					system("cls");
					break;
                case 5:
                	system("cls");
                	modify();
                	printf("\nPress Any Key To Continue.....\n");
					getch();
					system("cls");
                    break;
                case 6:	
                    fclose(fopen("Details.txt", "w"));
                	UpdateFile(root);
                    printf("\n\nTHANK YOU !!\n\n");
                    exit(0);
                    break;
                default:
                    system("cls");
                    printf("Incorrect Input");
                    printf("\n Press any key to continue....\n");
            }
    	}
}
void add()
{
	printf("\nEnter Room Number You Want to Book\n");
	int r;
	scanf("%d",&r);
	int f=insert(r);
	if(f==1)
	{
		printf("\nRoom Booked Sucessfully!!!\n\n");
		printf("Press Any Key To Continue.....");
		getch();
		system("cls");
	}
	else
	{
		printf("\nSORRY !!! Room You are Looking for is Already Booked....\n");
		printf("Press Any Key To Continue.....");
		getch();
		system("cls");
	}
	
}
int insert(int r)
{
	struct node *t,*parent=NULL,*p=root;
	if(root==NULL)
	{
		root=(struct node *)malloc(sizeof(struct node));
		root->roomno=r;
		printf("Enter Your Name\n");
		char n[20],add[20],ph[20];
		fflush(stdin);
		scanf("%s",n);
		printf("Enter Perminant Address\n");
		fflush(stdin);
		scanf("%s",add);
		printf("Enter Phone Number\n");
		fflush(stdin);
		scanf("%s",ph);
		int f=1;
		while(f)
		{
			if(strlen(ph)!=10)
			{
				printf("phone number not valid enter again\n");
				fflush(stdin);
				scanf("%s",ph);
			}
			else
			f=0;
		}
        WriteFile(r,n,add,ph);
	    strcpy(root->name,n);
		strcpy(root->address,add);
		strcpy(root->phoneno,ph);
		root->r=root->l=NULL;
		return 1;
	}
	else
	{
		while(p!=NULL)
		{
			parent=p;
			if(r<p->roomno)
			{
				p=p->l;
			}
			else if(r>p->roomno)
			{
				p=p->r;
			}
			else return 0;			
		}
	}
	t=(struct node *)malloc(sizeof(struct node));
	t->l=t->r=NULL;
		t->roomno=r;
		printf("\nEnter Your Details...\n");
		printf("Enter Your Name\n");
		char n[20],add[20],ph[20];
		fflush(stdin);
		scanf("%s",n);
		printf("Enter Perminant Address\n");
		fflush(stdin);
		scanf("%s",add);
		printf("Enter Phone Number\n");
		fflush(stdin);
		scanf("%s",ph);
		int f=1;
		while(f)
		{
			if(strlen(ph)!=10)
			{
				printf("Phone Number Not Valid Enter Again..\n");
				fflush(stdin);
				scanf("%s",ph);
			}
			else
			f=0;
		}
	    WriteFile(r,n,add,ph);
	    strcpy(t->name,n);
		strcpy(t->address,add);
		strcpy(t->phoneno,ph);
	if(r<parent->roomno)
	parent->l=t;
	else
	parent->r=t;
	
	return 1;
	system("cls");
}
void WriteFile(int r,char n[],char add[],char ph[])
{
	f=fopen("Details.txt","a+");
	fprintf(f,"%d\t%s\t%s\t%s\n",r,n,add,ph);
	fclose(f);
}
void list(struct node *temp)
{
	if(temp!=NULL)
	{
		list(temp->l);
		printf("%d\t",temp->roomno);
		printf("%s\t",temp->name);
		printf("%s\t",temp->address);
		printf("%s\t\n" ,temp->phoneno);
		list(temp->r);
	}
}

void search()
{
	printf("Enter Room Number You Want To Search..\n");
	int rn;
	scanf("%d",&rn);
	struct node *t=root;
	while(t!=NULL)
		{
			if(rn==t->roomno)
			break;
			
			else if(rn<t->roomno)
			t=t->l;
			
			else
			t=t->r;
		}
		
	if(t==NULL)
	printf("\nSORRY!!!!!!! Room you are looking for not Booked!!!!!!!\n");
	else
	{
		printf("Room Detail........\n");
		printf("Room Number : %d\n",t->roomno);
		printf("Name  : %s\n",t->name);
		printf("Address : %s\n",t->address);
		printf("Phone no . : %s\n",t->phoneno);
	}
} 
void del()
{
	printf("Enter Room Number you want Delete...\n");
	int r;
	scanf("%d",&r);
	struct node *f;
	f=deleteRecord(r,root);
	if(f==NULL)
	 printf("Not Found");
	else
	 printf("Your Action Has Updated!!!!\n");
}
struct node *deleteRecord(int rn,struct node *p)
{
	struct node *q;
	if(p==NULL)
	{
		return NULL;
	}

	if(rn<p->roomno)
		p->l=deleteRecord(rn,p->l);
	else if(rn>p->roomno)
		p->r=deleteRecord(rn,p->r);
	else
	{
		if(p->l==NULL && p->r==NULL)
		{
		
				if(p==root)
				{
						root=NULL;
				}
				free(p);
				return NULL;
		}
		else if(HeightOfTree(p->l)>HeightOfTree(p->r))
		{
			q=inpre(p->l);
			p->roomno=q->roomno;
			strcpy(p->name,q->name);
			strcpy(p->address,q->address);
			strcpy(p->phoneno,q->phoneno);
			p->l=deleteRecord(q->roomno,p->l);
		}
		else
		{
			q=insuc(p->r);
			p->roomno=q->roomno;
			strcpy(p->name,q->name);
			strcpy(p->address,q->address);
			strcpy(p->phoneno,q->phoneno);
			p->r=deleteRecord(q->roomno,p->r);
		}	
	}
	return p;
}
int HeightOfTree(struct node *t)
{
	int a,b,temp;
	if(t==NULL) return 0;
	a=HeightOfTree(t->l);
	b=HeightOfTree(t->r);
	return a>b?a+1:b+1 ;

}
struct node* inpre(struct node *t)
{
	while(t && t->r!=NULL)
	{
		t=t->r;
	}
	return t;
}
struct node* insuc(struct node *t)
{
	while(t && t->l!=NULL)
	{
		t=t->l;
	}
	return t;
}

void modify()
{
	int r;
	printf("Enter Room no. You Want to Modify\n");
	scanf("%d",&r);
	struct node *p=root;
	while(p!=NULL)
	{
		if(r<p->roomno)
		p=p->l;
	    else if(r>p->roomno)
	    p=p->r;
	    else
	    break;
	}
	if(p==NULL)
	printf("Room no. not found\n");
	else
	{
		printf("Old details.....\n");
		printf("Name:%s\n",p->name);
		printf("Address:%s\n",p->address);
		printf("Phone No:%s\n\n" ,p->phoneno);
		printf("Enter New Detalis...\n");
		printf("Enter Your Name\n");
		char n[20],add[20],ph[20];
		fflush(stdin);
		scanf("%s",n);
		printf("Enter Perminant Address\n");
		fflush(stdin);
		scanf("%s",add);
		printf("Enter Phone Number\n");
		fflush(stdin);
		scanf("%s",ph);
		int f=1;
		while(f)
		{
			if(strlen(ph)!=10)
			{
				printf("Phone Number not valid Enter Again\n");
				fflush(stdin);
				scanf("%s",ph);
			}
			else
			f=0;
		}
		strcpy(p->name,n);
		strcpy(p->address,add);
		strcpy(p->phoneno,ph);
		printf("Details Modoified Successfully!!\n");
	}
}

void SentToTree()
{
	int r;
	char name[20],add[20],ph[20];
	f=fopen("Details.txt","a+");
	if(f!=NULL)
	{
	    while (!feof(f))
		{
			fscanf(f,"%d\t%s\t%s\t%s\n",&r,name,add,ph);
		    InsertFromFile(r,name,add,ph);
		}
	}
	fclose(f);
}
void InsertFromFile(int r,char n[],char add[],char ph[])
{
	struct node *t,*parent=NULL,*p=root;
	if(root==NULL)
	{
		root=(struct node *)malloc(sizeof(struct node));
		root->roomno=r;
		strcpy(root->name,n);
		strcpy(root->address,add);
		strcpy(root->phoneno,ph);
		root->r=root->l=NULL;
	}
	else
	{
		while(p!=NULL)
		{
			parent=p;
			if(r<p->roomno)
			{
				p=p->l;
			}
			else if(r>p->roomno)
			{
				p=p->r;
			}
			else 
			break;			
		}
	t=(struct node *)malloc(sizeof(struct node));
	t->l=t->r=NULL;
		t->roomno=r;
        strcpy(t->name,n);
		strcpy(t->address,add);
		strcpy(t->phoneno,ph);
	if(r<parent->roomno)
	parent->l=t;
	else
	parent->r=t;
	}
}

void UpdateFile(struct node *p)
{
 	if(p!=NULL)
 	{
 		UpdateFile(p->l);
 		WriteFile(p->roomno,p->name,p->address,p->phoneno);
 		UpdateFile(p->r);
	 }
	
}
