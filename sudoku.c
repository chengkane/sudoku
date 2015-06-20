
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define len(a) (sizeof(a)/sizeof*(a))

int find(
		int (**rs)[9],
		int *n,
		int (*data)[9],
		int (*row)[10],
		int (*col)[10],
		int *(*blo)[9],
		int x,
		int y);
int display(int (**rs)[9],int n);

int main(int argc,char *argv[])
{
	unsigned long start=clock();

	/* main data */
	static int data[9][9];
	static int row[9][10],col[9][10],blockset[9][10];
	static int *blo[9][9];
	static int (*rs[10])[9],n;

	char c;
	int i,j,k,l;

	/* input */
	for(i=0;i<9*9;)
		if(isdigit(c=getchar()))
			data[0][i]=c-'0',i++;

	/* init */
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			blo[i][j]=blockset[i/3*3+j/3];
	for(i=0;i<9;i++)
		for(j=0;j<9;j++){
			k=data[i][j];
			row[i][k]=col[j][k]=blo[i][j][k]=1;
		}

	/* search */
	find(rs,&n,data,row,col,blo,0,0);
	if(n)
		display(rs,n);
	start=clock()-start;
	printf("time used: %lu ms.\n",start);

	while(n--)
		free(rs[n]);
	//free(*rs);
	return 0;
}

int find(
		int (**rs)[9],
		int *n,
		int (*data)[9],
		int (*row)[10],
		int (*col)[10],
		int *(*blo)[9],
		int x,
		int y){
	/* is it the end */
	if(x==9){
		printf("find it!\n");
		rs[*n]=(int(*)[9])malloc(sizeof(int)*9*9);
		memcpy(rs[*n],data,sizeof(int)*9*9);
		(*n)++;
		return 1;
	}
	/* get the coordinate of the next point */
	int ntx,nty;
	if(y==8)
		ntx=x+1,nty=0;
	else
		ntx=x,nty=y+1;
	/* the process of recursion */
	if(data[x][y])
		return find(rs,n,data,row,col,blo,ntx,nty);
	else{
		int i,tmp;
		for(i=1;i<10;i++)
			if(row[x][i]==0
				&&col[y][i]==0
				&&blo[x][y][i]==0){
				data[x][y]=i;
				row[x][i]=col[y][i]=blo[x][y][i]=1;
				tmp=find(rs,n,data,row,col,blo,ntx,nty);
				data[x][y]=row[x][i]=col[y][i]=blo[x][y][i]=0;
				if(tmp)
					return 1;
			}
		return 0;
	}
}

int display(int (**rs)[9],int n){
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<9;j++){
			for(k=0;k<9;k++)
				printf("%2d",rs[i][j][k]);
			putchar('\n');
		}
		putchar('\n');
	}

	return 0;
}

