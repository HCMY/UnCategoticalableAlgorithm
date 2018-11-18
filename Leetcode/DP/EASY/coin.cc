#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char left[3][7];
	char right[3][7];
	char res[3][7];
	bool isheavy(char c){
	int i;
	for(i=0;i<3;i++)
	{switch(res[i][0]){
	case 'e':if(strchr(left[i],c)!=NULL||strchr(right[i],c)!=NULL)return false;break;
	case 'u':if(strchr(left[i],c)==NULL)return false;break;
	case 'd':if(strchr(right[i],c)==NULL)return false;break;}
	}
	return true;
	}
	bool islight(char c){
	int i;
	for(i=0;i<3;i++)
		switch(res[i][0]){
		case 'e':if(strchr(left[i],c)!=NULL||strchr(right[i],c)!=NULL)return false;break;
		case 'u':if(strchr(right[i],c)==NULL)return false;break;
	    case 'd':if(strchr(left[i],c)==NULL)return false;break;}
	return true;}
int main(){
char c;
	int n;
	int i,j;
	scanf("%d",&n);
	while(n>0){
		for(i=0;i<3;i++)
			scanf("%s %s %s",left[i],right[i],res[i]);
      for(c='A';c<='L';c++)
		  if(islight(c)){printf("%c is the counterfeit coin and it is light.\n",c);break;}
		  else if(isheavy(c)){printf("%c is the counterfeit coin and it is heavy.\n",c);break;}
	n--;}
return 0;}
