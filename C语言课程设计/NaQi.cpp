#include<conio.h>
int IsLeapYear(int); 
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
# include <io.h>

#define I 8
#define R 150

//# include "student.h" 
typedef struct dbf1 {
	char ver;     //版本号 
	char date[3];    //创建年月日
	unsigned long record_num;//记录个数 
	unsigned short stru_byte_num;//结构说明和字段说明,共占的字节数+1
	unsigned short record_byte_num;//记录字节个数
	char unse[20];//保留 
}DBFH;

typedef struct dbf2 {
	char field_name[11]; //字段名ASCII码 
	char field_type; //字段类型 
	long unse1; //字段在记录中的位置 
	char field_len; //字段长度的二进制数 
	char decimal;//小数点后位数的2进制数 
	char unse2[2];//保留 
	char work_area;//工作区标志 
	char unse3[11];//保留 

}DBFSTRU;
void appe_rec();
void key_read();
void create_dbf();
void insert_rec();
void display();
void delete_rec();
void find_rec();
void print();
void qj();
void hj();
void rili();
void qingp();
void time();
int menu_select();
HWND GetConsoleHwnd(void);

DBFH dbf_head;
DBFSTRU fields[128];
FILE *dbfp;
char *cc;
#define MAX 68
#define MIN 70
void print(int n)
{
 int m = n;
 while(m--)
  printf(" ");
 printf("       (___)\n");
 m = n;
 while(m--)
  printf(" ");
 printf(" \\_____(o o)\n");
m = n;
 while(m--)
  printf(" ");
 printf("/      ` @@\n");
m = n;
 while(m--)
  printf(" ");
 printf("\\ ,____ /\n");
m = n;
 while(m--)
  printf(" ");
 printf(" \\\\    \\\\\n");
m = n;
 while(m--)
  printf(" ");
 printf("  ^^    ^^");
}
HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
HWND hwndFound; // This is what is returned to the caller.
char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
char pszOldWindowTitle[MY_BUFSIZE]; // Contains original

GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);//获取控制台标题存入pszOldWindowTitle中
//设置控制台的标题为 时间数 进程ID
wsprintf(pszNewWindowTitle,"%d/%d",//把获取的数目，和当前进程ID输出到缓冲区pszNewwindowtitle中
GetTickCount(),//用于获取操作系统启动后的毫秒数
GetCurrentProcessId());//获取当前进程ID

SetConsoleTitle(pszNewWindowTitle);//更改控制台的标题为新内容

Sleep(40);

hwndFound=FindWindow(NULL, pszNewWindowTitle);//获取控制台的HWND号

SetConsoleTitle(pszOldWindowTitle);//更改控制台的标题为原始内容

return(hwndFound);//返回句柄
}


void drawXY()//绘制X和Y轴
{
HWND hWnd=GetConsoleHwnd();//获取控制台窗口句柄，用于设置画笔颜色
HDC hDC=GetDC(hWnd);
COORD dwSize;//记录窗体大小，用于设定坐标轴远点
HPEN hNewPen=CreatePen(PS_SOLID,1,RGB(255,0,0));//创建画笔对象
HPEN hOldPen=(HPEN)SelectObject(hDC,hNewPen);//选取画笔对象进行绘图
CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口信息
HANDLE Hout=GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
GetConsoleScreenBufferInfo(Hout, &bInfo );//获取控制台信息
dwSize=bInfo.dwMaximumWindowSize ;//获取窗口大小,此时获得的是字符模式下
//从字符到图像放大坐标轴8倍
dwSize.X *=8;
dwSize.Y*=8;
SetBkMode(hDC, TRANSPARENT);SetTextColor(hDC,255*255);
//绘制X轴各个特殊坐标
TextOut(hDC,dwSize.X-15,dwSize.Y/2-15,"X",1);
//Arc(hDC,100,100,300,300,350,500,350,500);//画圆 其中hDC表示画图句柄，100，100，300，300表示所使用的矩形区域，350，500表示画弧线的起点，350，500表明画弧线的终点 ;
//绘制Y轴各个特殊坐标
TextOut(hDC,dwSize.X/2,0,"Y",1);
MoveToEx(hDC,0,dwSize.Y /2,NULL);
LineTo(hDC,dwSize.X,dwSize.Y/2);
MoveToEx(hDC,dwSize.X/2,0,NULL);
LineTo(hDC,dwSize.X/2,dwSize.Y);
ReleaseDC(hWnd,hDC);
}
void draw(double p)
{
int i;
double x,y;
HWND hWnd=GetConsoleHwnd();//获取控制台窗口句柄，用于设置画笔颜色
HDC hDC=GetDC(hWnd);
COORD dwSize;//记录窗体大小，用于设定坐标轴远点
HPEN hNewPen=CreatePen(PS_SOLID,1,RGB(255,0,0));//创建画笔对象
HPEN hOldPen=(HPEN)SelectObject(hDC,hNewPen);//选取画笔对象进行绘图
CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口信息
HANDLE Hout=GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
GetConsoleScreenBufferInfo(Hout, &bInfo );//获取控制台信息
dwSize=bInfo.dwMaximumWindowSize ;//获取窗口大小,此时获得的是字符模式下
//从字符到图像放大坐标轴8倍
dwSize.X *=8;
dwSize.Y*=8;
//MoveToEx(hDC,0,dwSize.Y/2,NULL);
for(i=-180;i<=180;i++)
{
x=16*pow(sin(i*3.1415926/180),3.0)*p;
y=(13*cos(i*3.1415926/180)-5*cos(2*i*3.1415926/180)-2*cos(3*i*3.1415926/180)-cos(4*i*3.1415926/180))*p;


x=(x+16)*dwSize.X/32/2+dwSize.X/4;
y=-y/16*dwSize.Y/2.3+dwSize.Y/2;


x=x;
y=y;
MoveToEx(hDC,x,y,NULL);
LineTo(hDC,x+1,y+1);


}
}
void time()
{  
time_t rawtime;  
struct tm * timeinfo;  
time ( &rawtime );  
timeinfo = localtime ( &rawtime );  
printf ( "The current date/time is: %s", asctime (timeinfo) );  
}
int main()
{	system("color 0b");
//printf("\n");
	int i = 2;
 for(;i<MAX;i=i+1)
 {
  system("cls");
  print(i);
 }printf("            201441010107        计科1班            那琦          \n");
      printf("\n");	
 printf("           彩 色 的 动 态 画 面 即 将 展 现，睁 大 眼 睛 !!!!  \n");
  printf("              _______╮(╯▽╰)╭________\n");//表情纯属娱乐.......

 Sleep(2000);
 double p;
drawXY();
for(p=0.6;p<=1;p=p+0.01)
draw(p);
system("PAUSE");
system("cls");
system("color 0b");
printf("               计科一班   那琦   制作       \n");
 for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
            float a = x * x + y * y - 1;system("color 0d");
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
	
	/* for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
			system("color 0D");
            float z = x * x + y * y - 1;
            float f = z * z * z - x * x * y * y * y;
            putchar(f <= 0.0f ? "C+++++++"[(int)(f * -8.0f)] : ' ');
        }
        putchar('\n');
    }*/
system("cls");
   int i1,j,e; 
    int a; 
    int t1;
    for(i1=1,a=I;i1<=I/2;i1++,a--){ 
        t1=6;	system("color 0D");
        while(t1--)printf(" ");
        
        for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
            printf(" "); 
        for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*"); 
   for(j=(int) (   2*( I-sqrt(I*I-(a-i1)*(a-i1)) )   );j>0;j--) 
            printf(" ");
   for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*");
   for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
            printf(" ");
   
   t1= (int) (   I-sqrt(I*I-(a-i1)*(a-i1))   ) ;
   t1= 2*t1;
   t1+=(int) ( 2*sqrt(I*I-(a-i1)*(a-i1)) );
   t1=20-t1;
  
   while(t1--){ 	system("color 0D");printf(" ");}

   for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
   {	system("color 0b");printf(" "); }
        for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*"); 
   for(j=(int) (   2*( I-sqrt(I*I-(a-i1)*(a-i1)) )   );j>0;j--) 
   {	system("color 0b");printf(" "); }
   for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*");
   for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
   {	system("color 0c");printf(" "); }
   
        printf("\n"); 
    } 
    
    for(i1=11;i1<=R/2;i1++){ 
  	system("color 0a");
        if(i1%2||i1%3)continue;
        
        t1=6;
        if(i1==6)printf(">>----");
        else while(t1--)printf(" ");
      	system("color 0b");
        for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
   {	system("color 0a");printf(" "); }
        for(e=1;e<=2*( sqrt(R*R-i1*i1) - (R-2*I) );e++) 
            printf("*"); 	system("color 0c");
   for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
            printf(" "); 	system("color 0b");
            
        t1= (int)(   R-sqrt(R*R-i1*i1)   );
        t1=2*t1;	system("color 0c");
        t1+= (int)(2*( sqrt(R*R-i1*i1) - (R-2*I) ));
        t1=35-t1;	system("color 0b");
   
   if(i1==6){printf("LOVE");}
   else if(i1==48){printf("\b\b\b C语言!!");	system("color 0b");}
   else 
               while(t1--) printf(" "); 
       for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
            printf(" "); 	system("color 0c");
        for(e=1;e<=2*( sqrt(R*R-i1*i1) - (R-2*I) );e++) 
            printf("*"); 	system("color 0c");
   for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
            printf(" "); 
   
   if(i1==6)printf("----->"); 
        printf("\n"); 
    }       
	Sleep(1000);
      system("cls");
	printf("\n");
  	printf("\n");
	printf("\n");
	system("color 0b");
	printf("                      10 个 月 的 C 语 言 学 习             \n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                  让  我 学  到 了 很  多 知  识   ^U^        \n ");
	system("color 0e");
	printf("\n\n\n\n\n\n\n\n\t\t\t");
	printf("C");
	system("color 0c");
	Sleep(500);
	printf("语");
	system("color 0b");
	Sleep(1000);
	printf("言");
	system("color 0c");
	Sleep(1000);
	printf("真的");
	system("color 0f");
	Sleep(1000);
	printf("不");
	system("color 0a");
	Sleep(1000);
	printf("简");
	system("color 0d");
	Sleep(1000);
	printf("单");
	system("color 0f");
	Sleep(1000);
	printf("!!!");
	Sleep(1000);
	printf("什么");
	system("color 0b");
	Sleep(1000);
	printf("都能");
	system("color 0c");
	Sleep(1000);
	printf("做");
	system("color 0f");
	Sleep(1000);
	printf("出");
	system("color 0a");
	Sleep(1000);
	printf("来");
	system("color 0d");
	Sleep(1000);
	printf("啊");
	system("color 0f");
	Sleep(1000);
	printf("!!!");
	Sleep(1000);
	system("cls");
//	heartFlashOne();
//	paintHeart(6);
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t");
	Sleep(200);
	printf("有");
	system("color 0a");
	Sleep(200);
	printf("光");
	system("color 0b");
	Sleep(200);
	printf("的");
	system("color 0c");
	Sleep(200);
	printf("地");
	system("color 0d");
	Sleep(200);
	printf("方");
	system("color 0e");
	Sleep(200);
	printf("必");
	system("color 0f");
	Sleep(200);
	printf("有");
	system("color 0c");
	Sleep(200);
	printf("阴");
	system("color 0d");
	Sleep(200);
	printf("影");
	system("color 0e");
	Sleep(200);
	printf("!");
	system("color 0f");
	Sleep(200);
	printf("至");
	system("color 0a");
	Sleep(200);
	printf("上");
	system("color 0b");
	Sleep(200);
	printf("励");
	system("color 0c");
	Sleep(200);
	printf("合\n\n");
	system("color 0c");
	Sleep(200);
	printf("你要");
	system("color 0b");
	Sleep(200);
	printf("努力");
	system("color 0c");
	Sleep(200);
	printf(",");
	system("color 0d");
	Sleep(200);
	printf("你想");
	system("color 0e");
	Sleep(200);
	printf("要的!!!");
	system("color 0f");
	Sleep(200);
	printf("-----");
	system("color 0c");
	Sleep(200);
	printf("要你自己给自己!!!!");
	system("color 0b");
	Sleep(200);
	printf("献给");
	system("color 0c");
	Sleep(200);
	printf("正在");
	system("color 0d");
	Sleep(200);
	printf("努力");
	system("color 0e");
	Sleep(200);
	printf("的");
	system("color 0f");
	Sleep(200);
	printf("自己!!!");
	system("color 0d");
	Sleep(200);
	printf("加油");
	system("color 0e");
	Sleep(200);
	printf("!!!");
	system("color 0f");
	Sleep(200);
	printf(" 嘻嘻 !");
	system("color 0c");
	Sleep(200);
	system("color 0d");
	Sleep(200);
	system("color 0e");
	Sleep(200);
	system("color 0f");
	Sleep(500);
	system("color 0a");
	printf("\n");
/* printf("****************************************************************************\n");
 printf("**                                                                        **\n");
 time();
 printf("**                                                                        **\n");
 printf("****************************************************************************\n");
 system("color 0e");
printf("\n");
printf("\n");*/
 system("cls");
 printf("\n");
 printf("*********************欢迎访问C语言模拟数据库系统***************************\n");
 printf("   *********************************************************************\n");
 	system("color 1e");
	for (;;)
	switch(menu_select()) {
		case 1:
			create_dbf();
			break;
		case 2:
			insert_rec();
			break;
		case 3:
			display();
			break;
		case 4:
			delete_rec();
			break;
		case 5:
			find_rec();
			break;
		case 6:
			appe_rec();
			break;
		case 7:
			printf("退出运行，再见！\n");
			exit(0);
		case 8:
			qj();
			break;
        case 9:
			hj();
			break;
		case 10:
			{
				printf("****************************************************************************\n");
                printf("**                                                                        **\n");
				time();
				printf("**                                                                        **\n");
                printf("****************************************************************************\n");
			}
			break;
        case 11:
			rili();
			break;
			}
	return 0;
}

int menu_select()
{
	char s[2];
	int cn;
//system("cls");
	printf("      ****************************************************************\n");
	printf("        【-------------- 1.创建数据库结构--------       C        】\n");
	printf("        【-------------- 2.插入记录--------------      语    O O 】\n");
	printf("        【-------------- 3.显示记录--------------      言     V  】\n");
	printf("        【-------------- 4.删除记录--------------      真        】\n");
	printf("        【-------------- 5.查找记录--------------      有    O O 】\n");	
	printf("        【-------------- 6.追加记录--------------      意     -  】\n");	
	printf("        【-------------- 7.退出运行！------------      思        】\n");
   	printf("        【-------------- 8.改变前景颜色！------------  ,         】\n");
   	printf("        【-------------- 9.改变后景颜色！------------  哈    O O 】\n");
	printf("        【-------------- 10.显示当前日期！------------ 哈     V  】\n");
    printf("        【-------------- 11.任选年份日历增项！^v^-----------     】\n");
	printf("     ***************************************************************\n");
	printf("\n");
	printf("        【-------------------请选择1-11:----------------------    】\n");
   //system("color 0D");
	for (;;)
	{
		gets(s);
		cn=atoi(s);
		if (cn<1||cn>11) printf("\n选择错误，重选1-11：");
		else break;
	}system("color 0a"); system("cls");
	printf("                       *******     C    *******\n");
    printf("                      *******     语     *******\n");
	printf("                       *********  言  ******** \n");
    printf("                        *******   数   *******\n");
	printf("                         ******   据   ******   \n");
    printf("                             ***  库  ***\n");
    printf("                                ******\n");
    printf("                                  **\n");
		return cn;
}
 	
void create_struct() //创建数据库结构 
{

	int i=0,field_num;
	for(;;)
	{
		memset(&fields[i],0,32);
		printf("字段名（10个字符），字段类型，字段长度，小数位数\n");
		scanf("%s",fields[i].field_name); //字段名ASCII码
		if (strcmp(fields[i].field_name,"!")==0) break;
			
		getchar();
		scanf("%c",&fields[i].field_type); //字段类型

		scanf("%d",&fields[i].field_len);  //字段长度的二进制数
		
		if (i==0) fields[i].unse1=1;
		else  fields[i].unse1=fields[i-1].unse1+fields[i-1].field_len;   //字段在记录中的位置 
		
		dbf_head.record_byte_num+=fields[i].field_len;             //记录长度 
		
		scanf("%d",&fields[i].decimal);    //小数点后位数的2进制数
		fseek(dbfp,32+i*32,0);
		fwrite(&fields[i],32,1,dbfp);
		i++;
	}
		field_num=i;
		fseek(dbfp,32+i*32,0);
		fputc(13,dbfp);
		for (i=0;i<263;i++)
			fputc(0,dbfp);
	
/*		printf("%s","现在添加记录吗？（y/n）");
		char ch=getchar();
		if (ch=='y'||ch=='Y') 
		{
			appe_rec();
			return;
		}*/
		fputc(0x1A,dbfp);
		dbf_head.stru_byte_num=32+32*field_num+1+263;//字段数据在内存中的地址32（文件头）+32*字段个数+1（结束标志）+263
		dbf_head.record_byte_num++;  //记录长度 
		return ;

}

void create_dbf() // 建立数据库文件头信息和数据库结构 
{	system("color 0b");

	char fname[20];
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"wb");
	dbf_head.ver=48;                  //版本 
	dbf_head.date[0]=15; //年 
	dbf_head.date[1]=9;	 //月 
	dbf_head.date[2]=8;  //日 
	dbf_head.record_num=0; //记录数 
	dbf_head.stru_byte_num=32+32*0+1+263;//字段数据在内存中的地址=32（文件头）+32*字段个数+1（结束标志0D）+263
	dbf_head.record_byte_num=0;//记录长度 

	for(int i=0;i<20;i++)            //20字节保留 
		dbf_head.unse[i]=0;
	dbf_head.unse[17]=0x7A;
	
	fwrite(&dbf_head,32,1,dbfp);  //写数据库文件，文件头信息的32个字节 
	
	create_struct();

	fseek(dbfp,0,0);             
	fwrite(&dbf_head,32,1,dbfp);   //关闭文件前重写文件头信息 

	fclose(dbfp);
}

void key_read()  // 记录内容存入内存空间cc中 
{
	int i,j,field_num,k;
	char ccc[255];

	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //字段数 	
	cc=(char *)malloc(dbf_head.record_byte_num);  //暂存记录 
	memset(cc,32,dbf_head.record_byte_num);  //记录内容设置为空格 
	gets(ccc);
	for (i=0;i<field_num;i++)
	{
		fseek(dbfp,(i+1)*32,0);
		fread(&fields[i],32,1,dbfp); //读取字段描述信息 
		printf("字段名：%s,类型：%c,长度：%d,小数位：%d\n",	fields[i].field_name,fields[i].field_type,fields[i].field_len,fields[i].decimal);
		if (gets(ccc)==NULL)
		{
			printf("输入内容错误！");
			exit(0);
		}
		if (strlen(ccc)>fields[i].field_len)
		{
			printf("输入内容太长，再输一次!!\n");
			i--;
		}
		else 
			if (fields[i].field_type=='I')
			{
                int n;
                n=atoi(ccc);
                *((int *)(cc+fields[i].unse1))=n;   //类型为I的数据存入cc中 
			}
			else if (fields[i].field_type=='N') 
			{
				memcpy(cc+(fields[i].unse1+fields[i].field_len-strlen(ccc)),ccc,strlen(ccc));
			}
			else
			{
				memcpy(cc+fields[i].unse1,ccc,strlen(ccc)); //字段内容复制到该字段在记录中的位置处
			}
		
	}
}
void appe_rec() //追加记录  
{
	system("color 0a");

	char fname[20];   //打开文件的文件名，临时用
	char yn;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	//fseek(dbfp,0,SEEK_SET);
	fread(&dbf_head,32,1,dbfp);
	
	for (;;)
	{
		key_read();
		dbf_head.record_num++;
	    fseek(dbfp,-1,SEEK_END);
	    if (fgetc(dbfp)==0x1A)	fseek(dbfp,-1,SEEK_END);
	    else fseek(dbfp,0,SEEK_END);
		fwrite(cc,dbf_head.record_byte_num,1,dbfp);
	
		printf("继续添加记录吗？(Y/N)");
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
	fputc(0x1A,dbfp);
	fseek(dbfp,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfp);
	fclose(dbfp);
	return; 
} 

void insert_rec()//插入数据
{
	int n1,i,field_num;
	char fname[20];   //打开文件的文件名，临时用
	char yn;
	char *records,*rec_i;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");//打开数据库
	fread(&dbf_head,32,1,dbfp);//读取头文件信息
	//fseek(dbfp,0,SEEK_SET);
    printf("请输入插入的位置\n");
    scanf("%d",&n1);
	printf("请输入插入数据\n");
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //字段数 
    fseek(dbfp,dbf_head.stru_byte_num+n1*32,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
    for (;;)
	{
		key_read();
		dbf_head.record_num++;
	    fseek(dbfp,-1,SEEK_END);
	    if (fgetc(dbfp)==0x1A)	fseek(dbfp,-1,SEEK_END);
	    else fseek(dbfp,0,SEEK_END);
		fwrite(cc,dbf_head.record_byte_num,1,dbfp);
	
		printf("继续添加记录吗？(Y/N)");
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
   
	fputc(0x1A,dbfp);
	fseek(dbfp,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfp);
    
	fclose(dbfp);
	return; 
	}


void display()
{
	char fname[20];   //打开文件的文件名，临时用
	char yn;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	
	int i,j,field_num,k;
	char *records,*rec_i;
	int offset;
	char ccc[255];
	fseek(dbfp,0,SEEK_SET);
	fread(&dbf_head,32,1,dbfp);
	
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //字段数 
	fseek(dbfp,dbf_head.stru_byte_num,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
	
	printf("记录号\t");
	for (i=0;i<field_num;i++)    
	{
		fseek(dbfp,(i+1)*32,0);
		fread(&fields[i],32,1,dbfp); //读取字段描述信息 
		printf("%s\t",	fields[i].field_name); //显示字段名 
	}
	printf("\n");
	
	offset=0;
	for (j=0;j<dbf_head.record_num;j++ )
	{
		memcpy(rec_i,records+offset,dbf_head.record_byte_num);

		printf("%3d   ",j+1);
		printf("%c",*rec_i);
		for (i=0;i<field_num;i++)
		{

			if (fields[i].field_type=='C')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf("%s",ccc);
			}
			if (fields[i].field_type=='L')
			{
				printf("%c",*(rec_i+fields[i].unse1));
			}
			if (fields[i].field_type=='I')
			{
				printf("%4d",*(rec_i+fields[i].unse1));
			}			
			if (fields[i].field_type=='N')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf("%s",ccc);
			}
			
		}
		printf("\n");
		offset+=dbf_head.record_byte_num;
	}
}

void delete_rec()
{
/*	int n1,i,field_num;
	char fname[20];   //打开文件的文件名，临时用
	char yn;
	char *records,*rec_i;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");//打开数据库
	fread(&dbf_head,32,1,dbfp);//读取头文件信息
	//fseek(dbfp,0,SEEK_SET);
    printf("请输删除的位置\n");
    scanf("%d",&n1);
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //字段数 
    fseek(dbfp,dbf_head.stru_byte_num+n1*32,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
    for (;;)
	{
		key_read();
		dbf_head.record_num++;
	    fseek(dbfp,-1,SEEK_END);
	    if (fgetc(dbfp)==0x1A)	fseek(dbfp,-1,SEEK_END);
	    else fseek(dbfp,0,SEEK_END);
		fwrite(cc,dbf_head.record_byte_num,1,dbfp);
	
		printf("继续删除记录吗？(Y/N)");
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
   
	fputc(0x1A,dbfp);
	fseek(dbfp,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfp);
    
	fclose(dbfp);
	return; */
		char fname[20],fnamels[7]="00.dbf";   //打开文件的文件名，临时用
	char yn,*xx,*yy;
	int dp,field_num;
	FILE*dbfpls;
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	fread(&dbf_head,32,1,dbfp);//读取文件头信息（32字节的文件头和数据库结构）
	yy=(char*)malloc(dbf_head.stru_byte_num-32);//开辟一个(字段信息和263)内存空间yy（调用malloc分配）
	fseek(dbfp,32,0);//文件指针指到第一个字段
    fread(yy,dbf_head.stru_byte_num-32,1,dbfp);//暂存记录 //把字段记录和263复制到yy中
	for (;;)
	{	
		printf("输入要删除第几个记录");
     	scanf("%d",&dp);
        xx=(char*)malloc(dbf_head.record_byte_num*dbf_head.record_num); //开辟一个（记录所占总字节）内存空间xx（调用malloc分配）
		fseek(dbfp,dbf_head.stru_byte_num,0);//文件指针指到第一个记录
		fread(xx,dbf_head.record_byte_num,dp-1,dbfp); //暂存记录 //把1到i条记录的复制到xx中
		dbfpls=fopen(fnamels,"wb+");
        fseek(dbfpls,dbf_head.stru_byte_num,0);//新文件指针指到第一个记录所在位置
        fwrite(xx,dbf_head.record_byte_num,dp-1,dbfpls);//内存空间xx中的数据（1到i条记录）写入新文件
		fseek(dbfp,dbf_head.stru_byte_num+dbf_head.record_byte_num*dp,0);//文件指针指到第i+1个记录所在位置
        fread(xx,dbf_head.record_byte_num,dbf_head.record_num-dp,dbfp);//把i+1到n条记录复制到xx中
		fseek(dbfpls,dbf_head.stru_byte_num+dbf_head.record_byte_num*(dp-1),0);//新文件指针指到第i+1个记录所在位置
		fwrite(xx,dbf_head.record_byte_num,dbf_head.record_num-dp,dbfpls);//内存空间xx中的数据（i+1到n条记录）写入新文件
        free(xx);
		dbf_head.record_num--;
		printf("继续删除记录吗？(Y/N)");
   		getchar();
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
	fputc(0x1A,dbfpls);
	fseek(dbfpls,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfpls); //关闭文件前重写文件头信息 
	fwrite(yy,dbf_head.stru_byte_num-32,1,dbfpls);//内存空间yy中的数据（字段记录和263）写入新文件
	free(yy);
	fclose(dbfp);
	fclose(dbfpls);
	if( access(fname,0 )== -1 )
		printf( "文件不存在\n");
	else
	{
		remove(fname);//调用system()函数删除原来的库文件
		rename(fnamels,fname);//调用system（）函数把新的库文件更名为原来的库文件
	}  
    system("pause");
	getchar();
    return;
}

void find_rec()
{
char fname[20];   //打开文件的文件名，临时用
	char yn;
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	
	int num;
	printf("请输入记录号：");
	scanf("%d",&num);

	int i,field_num,k;
	char *records,*rec_i;
	int offset;
	char ccc[255];
	fseek(dbfp,0,SEEK_SET);
	fread(&dbf_head,32,1,dbfp);
	
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //字段数 
	fseek(dbfp,dbf_head.stru_byte_num,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
	
	printf("记录号\t");
	for (i=0;i<field_num;i++)    
	{
		fseek(dbfp,(i+1)*32,0);
		fread(&fields[i],32,1,dbfp); //读取字段描述信息 
		printf("%s\t",	fields[i].field_name); //显示字段名 
	}
	printf("\n");
	
	offset=dbf_head.record_byte_num*(num-1);
		memcpy(rec_i,records+offset,dbf_head.record_byte_num);

		printf("%3d   ",num);
		printf("%c",*rec_i);
		for (i=0;i<field_num;i++)
		{

			if (fields[i].field_type=='C')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf(" %s",ccc);
			}
			if (fields[i].field_type=='L')
			{
				printf("%c",*(rec_i+fields[i].unse1));
			}
			if (fields[i].field_type=='I')
			{
				printf("%8d",*(rec_i+fields[i].unse1));
			}			
			if (fields[i].field_type=='N')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf("    %s",ccc);
			}
		
	}
	printf("\n");
	system("pause");
	getchar();
	return;
	
	
}
void qj()
{
	system("color 9b");
}
void hj()
{
    system("color 07");

}

void rili()
{
 int i;
 int day;
 int year;
 int temp;
 int temp_i;
 long int Year_days = 0;
 int Year_Start = 1;
 int Per_Year_Days;
 int month_day[]={31,28,31,30,31,30,31,31,30,31,30,31,29};
 printf("Please enter the year: ");
 scanf("%d",&year);
 while(Year_Start < year)
 {
  if( IsLeapYear( Year_Start ) )
   Per_Year_Days = 366;
  else
   Per_Year_Days = 365;
  Year_days = Year_days + Per_Year_Days;
  Year_Start++;
 }
 for( temp = 1; temp <=12; temp++ )
 {
  switch( temp )
  {
   case 1:
    printf("    January(%d)\n",year);
    break;
   case 2:
    printf("    February(%d)\n",year);
    break;
   case 3:
    printf("    March(%d)\n",year);
    break;
   case 4:
    printf("    April(%d)\n",year);
    break;
   case 5:
    printf("    May(%d)\n",year);
    break;
   case 6:
    printf("    June(%d)\n",year);
    break;
   case 7:
    printf("    July(%d)\n",year);
    break;
   case 8:
    printf("    August(%d)\n",year);
    break;
   case 9:
    printf("    September(%d)\n",year);
    break;
   case 10:
    printf("    October(%d)\n",year);
    break;
   case 11:
    printf("   November(%d)\n",year);
    break;
   case 12:
    printf("   December(%d)\n",year);
    break;
  }
  i = Year_days % 7;
  printf("Mon Tue Wed Thu Fri Sat Sun\n");
  if( i != 0 )
   for( temp_i = 0; temp_i < i; temp_i++)
    printf("    ");
  day = 1;
  if( IsLeapYear(year) && temp == 2)
   while( day <= month_day[12] )
   {
    if( day >1 )
     if( Year_days % 7 == 0 )
      printf("\n");
    if( day >= 10 )
     printf("%d  ",day);
    else
     printf("%d   ",day);
    Year_days++;
    day++;
   }
  else
   while (day <= month_day[temp-1])
   {
    if( day > 1 )
     if( Year_days % 7 == 0 )
      printf("\n");
    if( day >=10 )
     printf("%d  ",day);
    else
     printf("%d   ",day);
    Year_days++;
    day++;
   }
  printf("\n");
  if( getch() == 'q' )
   exit(0);
 }
 getch();
}

int IsLeapYear( int year )
{
 if ((year %4 == 0) && (year % 100 != 0) ||
    (year % 400 == 0) )
  return 1;
 else
  return 0;
}
void clear()
{
	system("cls");
	printf("  %c操作完成%c\n\n",2,2);
	main();
}
