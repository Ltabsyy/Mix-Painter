/*Mix Painter Beta*/
//#define _CRT_SECURE_NO_WARNINGS//vs专属(doge)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define PI 3.14159265358979323846
#define ScreenLength 93//建议93
#define ScreenWidth 43//建议43
//屏幕49*189，y轴为行，与数学中相反
//实际使用43*(93*2)，横向x为美观宽度*2，纵向y为表示边界长度缩窄
void ShowDrawing();
void ClearDrawing(int x1,int y1,int x3,int y3);
void SaveDrawing();
void MoveDrawing(int dx,int dy);
void ReverseDrawing(char direction);
void NumberFromC(int begin);
void DrawLine(int x1,int y1,int x2,int y2);
//void DrawLineA(int x0,int y0,int r,int angle);
void DrawRectangle(int x1,int y1,int x3,int y3);
void DrawCircle(int x0,int y0,int r);
void Error();
char c[64];
int n[8]={0};
int a[ScreenLength][ScreenWidth]={0};
int main()
{
	int i;
	printf("Mix Painter Beta\n");
	printf("屏幕空间：x:0~%d y:0~%d\n", ScreenLength-1, ScreenWidth-1);
	printf("以左下角为原点(0,0)\n");
	printf("请全屏使用！请记住指令！(doge)\n");
	printf("清空       /c\n"//clear
		   "保存并退出 /s\n"//save
		   "绘制点     /d 1 [x1] [y1]\n"//draw
		   "绘制线段   /d 2 [x1] [y1] [x2] [y2]\n"//多输入坐标不生效，少输入默认为0
		   "绘制三角形 /d 3 [x1] [y1] [x2] [y2] [x3] [y3]\n"
		   "绘制矩形   /d 4 [x1] [y1] [x3] [y3]\n"//对角线坐标
		   //"绘制n边形 /d n [x1] [y1] [x2] [y2] . . .  [xn] [yn]\n"
		   "绘制圆     /d c [x0] [y0] [r]\n"
		   "擦除图画   /c [x1] [y1] [x3] [y3]\n"
		   "移动图画   /m [dx] [dy]\n"//move
		   "翻转图画   /r [x/y/z]\n");
	printf("按回车开始");
	getchar();
	while(1)
	{
		/*显示预览*/
		system("cls");
		ShowDrawing();
		/*读入指令*/
		printf(">");
		for(i=0;i<=63;i++)
		{
			c[i]=0;
		}
		for(i=0;;i++)
		{
			c[i]=getchar();
			if(c[i]=='\n') break;
		}
		/*执行指令*/
		if(c[0]=='/')
		{
			if(c[1]=='c')
			{
				if(c[2]=='\n')
				{
					ClearDrawing(0,0,ScreenLength-1,ScreenWidth-1);
				}
				else if(c[2]==' ')
				{
					NumberFromC(3);
					ClearDrawing(n[0],n[1],n[2],n[3]);//x1,y1,x3,y3
				}
				else
				{
					Error();
				}
			}
			else if(c[1]=='s'&&c[2]=='\n')
			{
				break;
			}
			else if(c[1]=='d'&&c[2]==' ')
			{
				if(c[3]=='0')
				{
					continue;
				}
				else if(c[3]=='1'&&c[4]==' ')
				{
					NumberFromC(5);
					a[n[0]][n[1]]=1;//x1,y1
				}
				else if(c[3]=='2'&&c[4]==' ')
				{
					NumberFromC(5);
					DrawLine(n[0],n[1],n[2],n[3]);//x1,y1,x2,y2
				}
				else if(c[3]=='3'&&c[4]==' ')
				{
					NumberFromC(5);
					DrawLine(n[0],n[1],n[2],n[3]);//x1,y1,x2,y2
					DrawLine(n[0],n[1],n[4],n[5]);//x1,y1,x3,y3
					DrawLine(n[2],n[3],n[4],n[5]);//x2,y2,x3,y3
				}
				else if(c[3]=='4'&&c[4]==' ')
				{
					NumberFromC(5);
					DrawRectangle(n[0],n[1],n[2],n[3]);//x1,y1,x3,y3
				}
				else if(c[3]=='c'&&c[4]==' ')
				{
					NumberFromC(5);
					DrawCircle(n[0],n[1],n[2]);//x0,y0,r
				}
				else
				{
					Error();
				}
			}
			else if(c[1]=='m'&&c[2]==' ')
			{
				NumberFromC(3);
				MoveDrawing(n[0],n[1]);//dx,dy
			}
			else if(c[1]=='r'&&c[2]==' ')
			{
				if(c[3]=='x'||c[3]=='y'||c[3]=='z')
				{
					ReverseDrawing(c[3]);
				}
				else
				{
					Error();
				}
			}
			else
			{
				Error();
			}
		}
		else
		{
			Error();
		}
	}
	SaveDrawing();
	printf(":)\n已保存到Drawing1.txt\n");
	system("pause");
	return 0;
}
void ShowDrawing()
{
	int x, y;//真正的y：ScreenWidth-1-y(doge)
	for(y=0;y<=ScreenWidth-1;y++)
	{
		if((ScreenWidth-1-y)%2==0||y==0)
		{
			printf("%2d", ScreenWidth-1-y);
		}
		else
		{
			printf("  ");
		}
		for(x=0;x<=ScreenLength-1;x++)
		{
			if(a[x][ScreenWidth-1-y]==1)
			{
				printf("**");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("  ");
	for(x=0;x<=ScreenLength-1;x++)
	{
		if(x%2==0||x==ScreenLength-1)
		{
			printf("%2d", x);
		}
		else
		{
			printf("  ");
		}
	}
	printf("\n");
}
void ClearDrawing(int x1,int y1,int x3,int y3)
{
	int x, y, temp;
	if(x1>x3)
	{
		temp=x1;
		x1=x3;
		x3=temp;
	}
	if(y1>y3)
	{
		temp=y1;
		y1=y3;
		y3=temp;
	}//使x1<=x3,y1<=y3
	for(y=y1;y<=y3;y++)
	{
		for(x=x1;x<=x3;x++)
		{
			a[x][y]=0;
		}
	}
}
void SaveDrawing()
{
	FILE *fp;
	fp=fopen("Drawing1.txt","w");
	int x, y;
	for(y=0;y<=ScreenWidth-1;y++)
	{
		for(x=0;x<=ScreenLength-1;x++)
		{
			if(a[x][ScreenWidth-1-y]==1)
			{
				fprintf(fp,"**");
			}
			else
			{
				fprintf(fp,"  ");
			}
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}
void MoveDrawing(int dx,int dy)
{
	int di, x, y, temp;
	while(dx<0)
	{
		dx+=ScreenLength;
	}
	while(dy<0)
	{
		dy+=ScreenWidth;
	}
	/*--
	d=1
	0 1 2 3 4 5 6 7 8 9
	9 0 1 2 3 4 5 6 7 8
	--*/
	for(di=1;di<=dx;di++)//x+1
	{
		for(y=0;y<=ScreenWidth-1;y++)//y同步
		{
			temp=a[0][y];
			a[0][y]=a[ScreenLength-1][y];//a[0]=a[9]
			for(x=ScreenLength-1;x>=2;x--)//a[9]=a[8];...;a[1]=a[0];（a[0]为temp）
			{
				a[x][y]=a[x-1][y];
			}
			a[1][y]=temp;
		}
	}
	for(di=1;di<=dy;di++)//y+1
	{
		for(x=0;x<=ScreenLength-1;x++)//x同步
		{
			temp=a[x][0];
			a[x][0]=a[x][ScreenWidth-1];
			for(y=ScreenWidth-1;y>=2;y--)
			{
				a[x][y]=a[x][y-1];
			}
			a[x][1]=temp;
		}
	}
}
void ReverseDrawing(char direction)
{
	int x, y, temp;
	/*--
	S93:0~92:0~45 47~92
	S43:0~42:0~20 22~42
	S(2n+1):0~2n:0~n-1 n+1~2n
	S(2n):0~2n-1:0~n-1 n~2n-1
	--*/
	if(direction=='x'||direction=='z')
	{
		for(x=0;x<=ScreenLength/2-1;x++)//翻转x
		{
			for(y=0;y<=ScreenWidth-1;y++)//y同步
			{
				temp=a[x][y];
				a[x][y]=a[ScreenLength-1-x][y];
				a[ScreenLength-1-x][y]=temp;
			}
		}
	}
	if(direction=='y'||direction=='z')
	{
		for(y=0;y<=ScreenWidth/2-1;y++)//翻转y
		{
			for(x=0;x<=ScreenLength-1;x++)//x同步
			{
				temp=a[x][y];
				a[x][y]=a[x][ScreenWidth-1-y];
				a[x][ScreenWidth-1-y]=temp;
			}
		}
	}
}
void NumberFromC(int begin)
{
	int i, j, temp, sign;
	for(i=0;i<=7;i++)
	{
		n[i]=0;
	}
	for(i=0;i<=7;i++)
	{
		temp=0;
		sign=1;
		for(j=begin;;j++)
		{
			if(c[j]==' '||c[j]=='\n') break;
			if(c[j]=='-')
			{
				sign=-1;
			}
			else
			{
				temp=temp*10+c[j]-48;
			}
		}
		n[i]=temp*sign;
		begin=j+1;
		if(c[j]=='\n') break;
	}
}
void DrawLine(int x1,int y1,int x2,int y2)
{
	float k, b, e;
	int x, y, temp;
	// y=k(x-x1)+y1
	k=(float)(y2-y1)/(x2-x1);
	b=(float)-k*x1+y1;
	//printf("k=%f,b=%f", k, b);//显示inf,-inf为无穷
	// y=kx+b
	if(x1>x2)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	if(y1>y2)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}//使x1<=x2,y1<=y2
	if(fabs(k)<=1)//优化调整
	{
		e=1;
	}
	else
	{
		//e=fabs(k)+0.5;
		e=1;
	}
	for(y=y1;y<=y2;y++)
	{
		for(x=x1;x<=x2;x++)
		{
			if(x1==x2)//k为无穷
			{
				a[x1][y]=1;
			}
			if(y>k*x+b-e/2.0 && y<k*x+b+e/2.0)//非整点给予误差
			{
				a[x][y]=1;
			}
		}
	}
}
/*void DrawLineA(int x0,int y0,int r,int angle)//需要DrawLine()
{
	float rad;
	int x1, y1;
	rad=angle*PI/180;
	x1=x0+r*cos(rad);
	y1=y0+r*sin(rad);
	DrawLine(x0,y0,x1,y1);
}*/
void DrawRectangle(int x1,int y1,int x3,int y3)//需要DrawLine()
{
	DrawLine(x1,y1,x1,y3);
	DrawLine(x1,y1,x3,y1);
	DrawLine(x1,y3,x3,y3);
	DrawLine(x3,y1,x3,y3);
}
void DrawCircle(int x0,int y0,int r)
{
	int x, y, dx, dy;
	float distance, e;
	e=1;
	for(y=0;y<=ScreenWidth-1;y++)
	{
		for(x=0;x<=ScreenLength-1;x++)
		{
			dx=abs(x-x0);
			dy=abs(y-y0);
			distance=sqrt(dx*dx+dy*dy);
			if(distance>r-e/2.0 && distance<r+e/2.0)
			{
				a[x][y]=1;
			}
		}
	}
}
void Error()//不会使图画消失(doge)
{
	int i;
	printf(":(\n"
		"你的设备遇到问题，需要重启。\n"
		"我们只收集某些错误信息，然后你可以重新启动。\n\n");
	for(i=0;i<=4;i++)
	{
		printf("\r%3d%% 完成", i*25);
		sleep(1);
	}
	printf("\n");
	system("cls");
	main();
}
/*-------------------------------------------
更新日志：
Mix Painter Beta
——新增 擦除图画
——新增 翻转图画
//——新增 以角度绘制线段
——优化 删除代码中无效部分
——优化 屏幕长宽为偶数时显示最大坐标
-------------------------------------------*/
