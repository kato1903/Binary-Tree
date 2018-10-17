#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>



typedef struct n{
	int x;
    struct	n * next;
}node;

typedef struct SosyalAg
{
    int TC;
    char* adSoyad;
    node *ark;
    struct SosyalAg* left;
    struct SosyalAg* right;
}SosyalAg;

void sortedArrayToBinarySearchTreeArray(int *a, int bas, int son,int *b);

SosyalAg * insertNewUser (SosyalAg *,int,char*); // TCsi verilen kiþiyi Sosyal Aða ekler 

int maxBul(SosyalAg*); // Aðaçtaki maksimum Tcyi bulur

int minBul(SosyalAg *); // Aðaçtaki minimum Tcyi bulur

SosyalAg * deleteUser(SosyalAg*,int); // Tcsi verilen kiþiyi aðaçtan siler

int contains(SosyalAg *,int); // Tcsi verilen kiþiyi aðaçta arayýp mevcutsa adýný ve soyadýýný yazdýrýr

int dolas(SosyalAg*tree,int x); // contains fonksiyonunun recursive olmayaný varsa 1 yoksa -1

void printInOrder(SosyalAg *); // Aðaçtaki Tcleri Inorder olarak yazýdýrýr (küçükten büyüðe)

void Friends(SosyalAg *,int); // Tcsi verilen kiþinin varsa arkadaþlarýný yazdýrýr.

int size(SosyalAg*); // Aðaçtaki node sayýsýný verir

void printNext(SosyalAg*,int); // Tcsi verilen kiþiden küçük olan kiþileri yazdýrýr
	
void printGreater(SosyalAg*,int); // Tcsi verilen kiþiden büyük olan kiþileri yazdýrýr

node * ekle(node * A , int x); // struct icindeki linked liste eleman eklerken kullandým
	
void arkadasEkle(SosyalAg* tree,int x,int y); // TCsi verilen kisiye(x) TCsi verilen kisiyi(y) arkadas olarak ekleyen fonksiyon

SosyalAg *dosyaOku(FILE* input2,SosyalAg* tree); // Problem 2 input formatýna uygun okuyan fonksiyon

int main()
{	
	int d;
	printf("Problem 1 icin 1 \nProblem 2 icin 2 \n");
	scanf("%d",&d);
	if(d==1){
		FILE* input = fopen("input1.txt","r");
	
	if(input==NULL){
		printf("Dosya Okunamadi");
		exit(1);
	}
	
	int a,i=0,j=0;
	int* dizi = (int*) malloc (sizeof(int));
	while(!feof(input)){
		fscanf(input,"%d",&a);
		dizi[i] = a;
		i++;
		dizi = (int*) realloc(dizi,(i+1)*sizeof(int));
		getc(input);
		printf("%d ",a);
	}
	
	int* dizi2 = (int*) malloc(sizeof(int)*i);
	
	sortedArrayToBinarySearchTreeArray(dizi,0,i-1,dizi2);
	
	printf("\nikili arama agacýna ait dengeli yeni dizi \n");
	
	for(j=0;j<i;j++)
        printf("%d ",dizi2[j]);
	}
	else if(d==2){
		SosyalAg *tree = NULL;
	FILE* input2 = fopen("input2.txt","r");
	if(input2==NULL){
		printf("Dosya Okunamadi");
		exit(1);
	}
	tree = dosyaOku(input2,tree);
	int i=0,j,k;
	while(i==0){
		printf("\n 1 - Delete User");
        printf("\n 2 - contains");
        printf("\n 3 - Friends");
        printf("\n 4 - size");
        printf("\n 5 - printNext");
        printf("\n 6 - printGreater");
        printf("\n 7 - printInOrder");
        printf("\n 8 - Cikmak icin ");
        printf("\n seciminizi yapin ... ");
        scanf("%d",&j);
        switch(j)
    {
        case 1:

            printf("\n Silinecek Kisinin TCsi");
            scanf("%d", &k);
            deleteUser(tree,k);
            break;
        case 2:
            printf("\n Aramak istediginiz Kisinin TCsi");
            scanf("%d", &k);
            contains(tree,k);
            break;
        case 3:
            printf("\n arkadaslarini gormek istediginiz Kisinin TCsi");
            scanf("%d", &k);
            Friends(tree,k);
            break;
        case 4:
            printf("%d\n",size(tree));
            break;
        case 5:
            printf("\n printNext gormek istediginiz Kisinin TCsi");
            scanf("%d", &k);
            printNext(tree,k);
            break;
        case 6:
            printf("\n printNext gormek istediginiz Kisinin TCsi");
            scanf("%d", &k);
            printGreater(tree,k);
            break;
        case 7:
            printInOrder(tree);
            break;
        case 8:
			i = 1;    

    }
}
		}	
		
		
		
    
	return 0;
}

SosyalAg * insertNewUser (SosyalAg *tree,int x,char* ad){
	if(tree == NULL){
		SosyalAg *root= (SosyalAg *)malloc(sizeof(SosyalAg));
		root->left = NULL;
		root->right = NULL;
		root->TC = x;
		root->adSoyad = ad; 
		root->ark = NULL; 
		return root;
	}

	if(tree->TC < x){
		tree->right = insertNewUser(tree->right,x,ad);
		return tree;
	}
	tree->left = insertNewUser (tree->left,x,ad);
	return tree;
}

int maxBul(SosyalAg *tree){

	while(tree->right!=NULL)
		tree=tree->right;
	return tree->TC;
}
int minBul(SosyalAg *tree){
	while(tree->left!=NULL)
		tree=tree->left;
	return tree->TC;
}

 SosyalAg * deleteUser(SosyalAg *tree,int x){
	if(tree==NULL)
		return NULL;
	if(tree->TC == x){
		if(tree->left==NULL && tree->right==NULL)
			return NULL;
		if(tree->right!=NULL){
			tree->TC = minBul(tree->right);
			tree->right = deleteUser(tree->right, minBul(tree->right));
			return tree;
		}
		tree->TC = maxBul(tree->left);
		tree->left = deleteUser(tree->left,maxBul(tree->left));
		return tree;
	}
	if(tree->TC < x){
		tree->right = deleteUser(tree->right,x);
		return tree;
	}
	tree->left= deleteUser(tree->left,x);
	return tree;


} 

void printInOrder(SosyalAg *tree){
	if(tree == NULL)
		return;
	printInOrder(tree->left);	
    printf("Tc = %d AdSoyad = %s\n",tree->TC,tree->adSoyad);
	printInOrder(tree->right);
}

void Friends(SosyalAg *tree,int y){
	if(dolas(tree,y) == -1){
		return;
	}
	
	SosyalAg *tree2 = tree;
	while( (tree->TC != y) ){
		if(y>tree->TC){
			tree = tree->right;
		}
		if(y < tree->TC){
			tree = tree->left;
		}
	}
	if(tree->TC == y){
			
			if(tree->ark == NULL){
				return;
		}
		while(tree->ark!=NULL){
			contains(tree2,tree->ark->x);
			tree->ark = tree->ark->next;
			}
		printf("\n");		
	}	
}

int size(SosyalAg *tree){
	if (tree==NULL) 
    	return 0;
  	else    
    	return(size(tree->left) + 1 + size(tree->right));  
}

void printNext(SosyalAg *tree,int x){
	
	if(tree==NULL){
		return;
	}
	
	if(x>tree->TC){
		printNext(tree->right,x);
	}
	if(x<tree->TC) {
		printNext(tree->left,x);	
	}
	if(x==tree->TC)
		printInOrder(tree);
		
	return;
}
	
void printGreater(SosyalAg *tree,int x){
	if(tree == NULL)
		return;
	printGreater(tree->left,x);
	if(x < tree->TC)	
    printf("%d %s \n",tree->TC,tree->adSoyad);
	printGreater(tree->right,x);
}

node * ekle(node * A , int x){



    if(A==NULL){
                                       
		A = (node *) malloc (sizeof(node));
		A->next = NULL;
		A->x = x;
		return A;
	}

    node * tmp =  A;                        
                                            
    while(tmp->next!=NULL){

        tmp = tmp->next;
    }

    tmp->next = (node*)malloc(sizeof(node));
	tmp->next->x = x;
	tmp->next->next = NULL;

    return A;

}

int contains (SosyalAg *tree,int x){
	if(tree == NULL)
		return -1;
	if(tree->TC == x){
		printf("%s \n",tree->adSoyad);			
		return 1;		
	}
	if(contains(tree->right,x)==1)
		return 1;
	if(contains(tree->left,x)==1)
		return 1;
	return -1;
}

void arkadasEkle(SosyalAg* tree,int x,int y){
	
	
	
	
	if(tree == NULL)
		return;
	if(x==tree->TC)
    {	
				tree->ark = ekle(tree->ark,y);								
    }
	
	arkadasEkle(tree->right,x,y);
	arkadasEkle(tree->left,x,y);
	
}

int bul (SosyalAg* tree,int x){
	if(tree == NULL)
		return -1;
	if(tree->TC == x)
		return 1;
	if(bul(tree->right,x)==1)
		return 1;
	if(bul(tree->right,x)==1)
		return 1;
	return -1;
}

int dolas(SosyalAg*tree,int x){
	if(tree == NULL)
		return;
	while(tree!=NULL && tree->TC!=x){
		if(x > tree->TC){
			tree = tree->right;
		}
		if(x < tree->TC){
			tree = tree->left;
		}
	}
	
	if(tree == NULL)
		return;
	if(tree->TC==x)
		return 1;
		
	return -1;
}

SosyalAg *dosyaOku(FILE* input2,SosyalAg* tree){
	char ad[100];
	char dizideneme[100][100];
	int p = 0;
	char deneme[100];
	int i,j=0,k=0,TC;
	int ark[100];
	int ilkdurum = 0;
	
	
	while(!feof(input2)){
	if(ilkdurum==0){	
		TC = fgetc(input2) - 48;
	}
	ilkdurum++;
	getc(input2);
	while(dizideneme[p][j-1] != 44 )
	{	
		dizideneme[p][j] = getc(input2);
		j++;
	}
	dizideneme[p][j-1] = '\0';
	
	fscanf(input2,"%d",&ark[k]);
	
	k++;
	do{
		fscanf(input2,"%d",&ark[k]);        
		k++;
	}while(ark[k-1]<0);
		
	tree = insertNewUser(tree,TC,dizideneme[p]);
	
	for(i=0;i<k-1;i++){
		
		if(i==0){
			
		}
		
		arkadasEkle(tree,TC,fabs(ark[i]));
	}
	TC = ark[k-1];
	k = 0;
	j = 0;
	p++;
}

return tree; 
}

void sortedArrayToBinarySearchTreeArray(int *a, int bas, int son,int *b)
{
    static int i = 0;

    if (bas > son)
      return;

    int mid = (bas + son)/2;
    b[i] = a[mid];
    i++;
    sortedArrayToBinarySearchTreeArray(a, bas, mid-1, b);
    sortedArrayToBinarySearchTreeArray(a, mid+1, son, b);
}
