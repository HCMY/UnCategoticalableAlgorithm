#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


#include<time.h>
#define cities 144  //城市的个数
#define MAXX 10//迭代次数
#define pc 0.8 //交配概率
#define pm 0.05 //变异概率
#define num 20//种群的大小

#define MAX_DISTANCE 100000

/**
hash map
这部分代码只用于从文件中获取数据辅助生成 距离文件 (cityA,cityB, 距离)
**/
struct node{
    int key;
    int val;
    struct node *next;
};
struct table{
    int size;
    struct node **list;
};
struct table *createTable(int size){
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}
int hashCode(struct table *t,int key){
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}
void insert(struct table *t,int key,int val){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;
    while(temp){
        if(temp->key==key){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    t->list[pos] = newNode;
}
int lookup(struct table *t,int key){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while(temp){
        if(temp->key==key){
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}
///#########################################MAP END#############################################################



/**
遗传算法部分
旅行商问题(TravelingSalesmanProblem，TSP)是一个经典的组合优化问题。
经典的TSP可以描述为：一个商品推销员要去若干个城市推销商品，该推销员从一个城市出发，需要经过所有城市后，回到出发地。
具体的思想，请看维基百科


算法步骤为：

-参数的设置，确定个体的编码方式（二进制或者其他），这里参数设置为宏变量
-初始随机解的生成
-选择算子：选择父代的策略（轮盘赌策略）
-繁殖：交叉两个父代并产生新个体（TSP问题的编码，需要解决路径冲突问题，即保证每个城市有且仅遍历一次）
-变异：对新个体进行变异操作
-竞争（更新种群）：精英保留策略或者自然选择

**/

int bestsolution;////最优染色体（解决方案）
int distance[cities][cities];//城市之间的距离
struct group  //染色体的结构
{
	int city[cities];//城市的顺序
	int adapt;//适应度
	double p;//在种群中的幸存概率
}group[num],grouptemp[num];


/*
距离文件生成函数
内容为：
城市Aid，城市B id， 两城距离
*/
int distance_file(){
    FILE *fpRead=fopen("cn144_location2.txt","r");
    if(fpRead==NULL)
    {
        return 0;
    }
    while (!feof(fpRead))
    {
        int i;
        fscanf(fpRead,"%d",&i);
        if (i==0) break;
        fscanf(fpRead,"%d%d",&x[i],&y[i]);
        //printf("%d %d %d\n",i,x[i],y[i]);
    }
    fclose(fpRead);

    FILE *fp=fopen("cn144_link2.txt","r");
    if(fp==NULL)
    {
        return 0;
    }
    int i;
    for(i=0;i<1440;i++)
    {
        fscanf(fp,"%d%d",&d[i+1],&f[i+1]);
       // printf("%d %d\n",d[i+1],f[i+1]);
    }
    fclose(fp);

    FILE *fpWrite=fopen("distance_mat.csv","w");
    if(fpWrite==NULL)
    {
        return 0;
    }
    for(i=1;i<=1440;i++){
        dis[d[i]][f[i]]=sqrt((x[d[i]]-x[f[i]])*(x[d[i]]-x[f[i]])+ (y[d[i]]-y[f[i]])*(y[d[i]]-y[f[i]]));
        fprintf(fpWrite,"%d,%d,%d\n",d[i],f[i],dis[d[i]][f[i]]);
    }
    fclose(fpWrite);

    return 0;
}


/*
根据距离文件，生成邻接矩阵，可以看成图
*/
void init()
{
    distance_file();

	int i,j;
	memset(distance,127,sizeof(distance));//³ÇÊÐÖ®¼ä¾àÀë³õÊ¼ÎÞÇî´ó
	srand((unsigned)time(NULL));

    struct table *t = createTable(500);

    char buffer[1024];
    FILE *fp = fopen("distance_mat.csv","r");

    int idx = 0;
    int arr[1440][3];
    while (!feof(fp)){
        fgets(buffer,1000,fp);
        char*temp = strtok(buffer,",");
        int col = 0;
        while(temp){
            int target = atoi(temp);
            arr[idx][col] = target;
            temp = strtok(NULL,",");
            col++;
        }idx++;
    }
    fclose(fp);

    int row;
	for(row=0; row<1440;row++){
        int start_city_id = arr[row][0];
        int end_city_id = arr[row][1];
        int dis = arr[row][2];
        distance[start_city_id][end_city_id] = dis;
	}
}

//随机产生初始群
void groupproduce()
{
	int i,j,t,k,flag;
	for(i=0;i<num;i++)  //³õÊ¼»¯
	for(j=0;j<cities;j++)
	group[i].city[j]=-1;
	srand((unsigned)time(NULL));
    for(i=0;i<num;i++)
	{
		//产生10个不相同的数字
		for(j=0;j<cities;)
		{
			t=rand()%cities;
			flag=1;
			for(k=0;k<j;k++)
			{
				if(group[i].city[k]==t)
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{
				group[i].city[j]=t;
				j++;
			}
		}
	}
	//打印种群基因
	printf("³õÊ¼µÄÖÖÈº\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<cities;j++)
		printf("%4d",group[i].city[j]);
		printf("\n");
	}
}


//评价函数,找出最优染色体
void pingjia()
{
	int i,j;
	int n1,n2;
	int sumdistance,biggestsum=0;
	double biggestp=0;
	for(i=0;i<num;i++)
	{
		sumdistance=0;
		for(j=1;j<cities;j++)
		{
			n1=group[i].city[j-1];
			n2=group[i].city[j];
			sumdistance+=distance[n1][n2];
		}
		group[i].adapt=sumdistance; //每条染色体的路径总和
		biggestsum+=sumdistance; //种群的总路径
	}
	//计算染色体的幸存能力,路劲越短生存概率越大
	for(i=0;i<num;i++)
	{
		group[i].p=1-(double)group[i].adapt/(double)biggestsum;
		biggestp+=group[i].p;
	}
	for(i=0;i<num;i++)
	group[i].p=group[i].p/biggestp;  //在种群中的幸存概率,总和为1
	//求最佳路径
	bestsolution=0;
	for(i=0;i<num;i++)
	if(group[i].p>group[bestsolution].p)
	bestsolution=i;
	//打印适应度
	for(i=0;i<num;i++)
	printf("È¾É«Ìå%dµÄÂ·¾¶Ö®ºÍÓëÉú´æ¸ÅÂÊ·Ö±ðÎª%4d  %.4f\n",i,group[i].adapt,group[i].p);
	printf("µ±Ç°ÖÖÈºµÄ×îÓÅÈ¾É«ÌåÊÇ%dºÅÈ¾É«Ìå\n",bestsolution);
}
//选择
void xuanze()
{
	int i,j,temp;
	double gradient[num];//梯度概率
	double xuanze[num];//选择染色体的随机概率
	int xuan[num];//选择了的染色体
	//初始化梯度概率
	for(i=0;i<num;i++)
	{
		gradient[i]=0.0;
		xuanze[i]=0.0;
	}
	gradient[0]=group[0].p;
	for(i=1;i<num;i++)
	gradient[i]=gradient[i-1]+group[i].p;
	srand((unsigned)time(NULL));
	//随机产生染色体的存活概率
	for(i=0;i<num;i++)
	{
		xuanze[i]=(rand()%100);
		xuanze[i]/=100;
	}
	//选择能生存的染色体
	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			if(xuanze[i]<gradient[j])
			{
				xuan[i]=j; //第i个位置存放第j个染色体
				break;
			}
		}
	}
	//拷贝种群
	for(i=0;i<num;i++)
	{
		grouptemp[i].adapt=group[i].adapt;
		grouptemp[i].p=group[i].p;
		for(j=0;j<cities;j++)
		grouptemp[i].city[j]=group[i].city[j];
	}
	//数据更新
	for(i=0;i<num;i++)
	{
		temp=xuan[i];
		group[i].adapt=grouptemp[temp].adapt;
		group[i].p=grouptemp[temp].p;
		for(j=0;j<cities;j++)
		group[i].city[j]=grouptemp[temp].city[j];
	}
	
}

//交配,对每个染色体产生交配概率,满足交配率的染色体进行交配
void  jiaopei()
{
	int i,j,k,kk;
	int t;//参与交配的染色体的个数
	int point1,point2,temp;//交配断点
	int pointnum;
	int temp1,temp2;
	int map1[cities],map2[cities];
	double jiaopeip[num];//染色体的交配概率
	int jiaopeiflag[num];//染色体的可交配情况
	for(i=0;i<num;i++)//初始化
	jiaopeiflag[i]=0;
	//随机产生交配概率
	srand((unsigned)time(NULL));
	for(i=0;i<num;i++)
	{
		jiaopeip[i]=(rand()%100);
		jiaopeip[i]/=100;
	}
	//确定可以交配的染色体
	t=0;
	for(i=0;i<num;i++)
	{
		if(jiaopeip[i]<pc)
		{
			jiaopeiflag[i]=1;
			t++;
		}
	}
	t=t/2*2;//t必须为偶数
	//产生t/2个0-9交配断点
    srand((unsigned)time(NULL));
	temp1=0;
	//temp1号染色体和temp2染色体交配
	for(i=0;i<t/2;i++)
	{
		point1=rand()%cities;
		point2=rand()%cities;
		for(j=temp1;j<num;j++)
		if(jiaopeiflag[j]==1)
		{
			temp1=j;
			break;
		}
		for(j=temp1+1;j<num;j++)
		if(jiaopeiflag[j]==1)
		{
			temp2=j;
			break;
		}
		//进行基因交配
		if(point1>point2) //保证point1<=point2
		{
			temp=point1;
			point1=point2;
			point2=temp;
		}
        memset(map1,-1,sizeof(map1));
		memset(map2,-1,sizeof(map2));
		//断点之间的基因产生映射
		for(k=point1;k<=point2;k++)
		{
			map1[group[temp1].city[k]]=group[temp2].city[k];
			map2[group[temp2].city[k]]=group[temp1].city[k];
		}
		//断点两边的基因互换
		for(k=0;k<point1;k++)
		{
			temp=group[temp1].city[k];
			group[temp1].city[k]=group[temp2].city[k];
			group[temp2].city[k]=temp;
		}
		for(k=point2+1;k<cities;k++)
		{
			temp=group[temp1].city[k];
			group[temp1].city[k]=group[temp2].city[k];
			group[temp2].city[k]=temp;
		}
		//处理产生的冲突基因
		for(k=0;k<point1;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			if(group[temp1].city[k]==group[temp1].city[kk])
			{
				group[temp1].city[k]=map1[group[temp1].city[k]];
				break;
			}
		}
		for(k=point2+1;k<cities;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			if(group[temp1].city[k]==group[temp1].city[kk])
			{
				group[temp1].city[k]=map1[group[temp1].city[k]];
				break;
			}
		}
		for(k=0;k<point1;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			if(group[temp2].city[k]==group[temp2].city[kk])
			{
				group[temp2].city[k]=map2[group[temp2].city[k]];
				break;
			}
		}
		for(k=point2+1;k<cities;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			if(group[temp2].city[k]==group[temp2].city[kk])
			{
				group[temp2].city[k]=map2[group[temp2].city[k]];
				break;
			}
		}
        temp1=temp2+1;
	}
}
//变异
void bianyi()
{
	int i,j;
	int t;
	int temp1,temp2,point;
	double bianyip[num];//染色体的变异概率
	int bianyiflag[num];//染色体的变异情况
	for(i=0;i<num;i++)//初始化
	bianyiflag[i]=0;
	//随机产生变异概率
	srand((unsigned)time(NULL));
	for(i=0;i<num;i++)
	{
		bianyip[i]=(rand()%100);
		bianyip[i]/=100;
	}
	//确定可以变异的染色体
	t=0;
	for(i=0;i<num;i++)
	{
		if(bianyip[i]<pm)
		{
			bianyiflag[i]=1;
			t++;
		}
	}
	//变异操作,即交换染色体的两个节点
	srand((unsigned)time(NULL));
	for(i=0;i<num;i++)
	{
		if(bianyiflag[i]==1)
		{
	        temp1=rand()%10;
			temp2=rand()%10;
			point=group[i].city[temp1];
            group[i].city[temp1]=group[i].city[temp2];
			group[i].city[temp2]=point;
		}
	}
}
int main()
{
	int i,j,t;
    init();
	groupproduce();
	pingjia();
	t=0;
    while(t++<MAXX)
	{
	     xuanze();
		 //jiaopei();
		 bianyi();
		 pingjia();
	}
	//最终种群的评价
	//printf("\n输出最终的种群评价\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<cities;j++)
		{
			printf("%4d",group[i].city[j]);
		}
		printf("adapt:%4d, p:%.4f\n",group[i].adapt,group[i].p);
	}
	printf("最优解为%d号基因组\n",bestsolution);
	printf("解决方案为: \n");
	for(j=0;j<cities;j++)
        printf("%d->",group[bestsolution].city[j]);
    printf("\n");
	return 0;
}
