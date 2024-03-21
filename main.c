#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include<time.h>
#include "STRUCT.h"
#include "FUNCTION.h"


int main()
{
    TrainData* head1,* head3;
    PassengerData* head2;
    TicketData* head4;
    TrainSeat* head5;
    int choose;
    while(1)
    {
        head1=read_train_File();
        head2=read_passengeer_File();
        head4=read_ticket_File();
        head5=crate_seat(head1,head4);
        choose=system_UI();
        switch(choose)
        {
            case 1:train_UI(head1);break;
            case 2:passenger_UI(head2);break;
            case 3:booking_UI(head1,head4,head5,head2);break;
            case 4:goodbye();break;
            default : printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                error");break;
        }
        save_train_File(head1);
        save_passenger_File(head2);
        save_ticket_File(head4);
        printf("\n\n                                                                                                               是否继续使用系统？（Y:1 N:0) ");
        scanf("%d",&choose);
        system("cls");
        if(choose==0){goodbye();break;}
        else continue;
    }
}


void goodbye()
{
    system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                               欢迎下次使用~");
	exit(0);
}

nowtime Get_Sys_Time() //返回当前系统时间
{
    struct tm today; //存放时间的结构体
    time_t one; //存放时间的类型
    nowtime now;
    one=time(&one); //获得系统时间
    today=*(gmtime(&one)); //将 time_t 格式系统时间转为 struct tm 格式
    now.year=today.tm_year-100+2000; //2011 年返回 111
    now.month=today.tm_mon+1; //9 月返回 8;
    now.day=today.tm_mday;
    now.hour= today.tm_hour;
    now.minit= today.tm_min;
    return now;
}

//高铁车次信息管理***********************************************************************************************************************************************************************

TrainData* read_train_File()
{
	FILE* fp;
	TrainData* head, * p, * q;
	StationData* m,*n;
	int temp=0,code;
	p = q = (TrainData*)malloc(sizeof(TrainData));//开辟空间赋指针
	if ((fp = fopen("train.txt", "r")) == NULL)//文件指针赋值为NULL
	{
		printf("                                                                                                                                                                        can't open file\n");
		exit(0);
	}
	head = p;//头指针赋值并读入

	while (!feof(fp))
	{
		q = (TrainData*)malloc(sizeof(TrainData));
        fscanf(fp, "%s %s %s %f %s %s %s %d %d %d %d",
        q->TrainNaber, q->StartStation, q->ArriveStation, &q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,&q->StationNum,&q->ProSet,&q->FirSet,&q->SecSet);
        temp=q->StationNum;
        m = (StationData*)malloc(sizeof(StationData));
        q->TStation=m;
        code=0;
        while(temp--)
        {
            code++;
            n = (StationData*)malloc(sizeof(StationData));
            fscanf(fp," %s %s %s %f",n->StaName,n->StopTime,n->DriveTime,&n->StaMileage);
            n->stacode=code;
            m->next=n;
            m=n;
        }
        fscanf(fp,"\n");
        m->next=NULL;
        p->next = q;
		p = q;
	}
	p->next = NULL;
	fclose(fp);
	return head;
}

void save_train_File(TrainData* L)
{
	if (L == NULL)//头指针空
	{
		printf("\n                                                                                                                can't save file\n");
		return;
	}
	FILE* fp = fopen("train.txt", "wb");
	if (fp == NULL)//文件指针空
	{
		printf("\n                                                                                                                can't open file\n");
		return;
	}
	TrainData* q ;
	StationData* m;
	q=L;
	q=q->next;

	while (q != NULL)
	{
		fprintf(fp,"%s %s %s %.1f %s %s %s %d %d %d %d",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
        m=q->TStation;
        m=m->next;
        while(m!=NULL)
        {
            if(m->next==NULL)
            {
                fprintf(fp," %s %s %s %.1f\n",m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
            }
            else
            {
                fprintf(fp," %s %s %s %.1f",m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
            }
            m=m->next;
        }
		q = q->next;
	}
	//收尾处理
	fclose(fp);
	fp = NULL;

}

void print_train(TrainData* head)
{
    TrainData* q;
    int i=1;
    q=head;
    q=q->next;
    printf("\n\n\n\n");
    printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
    while(q!=NULL)
    {
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
        printf("                                                                 |                                                                                                                                  |\n");
        q=q->next;
        printf("\n");
    }
}

void print_train_File(TrainData* head)
{
    TrainData* q;
    int i=1;
    StationData* m;
    q=head;
    q=q->next;
    while(q!=NULL)
    {
        printf("\n\n\n\n");
        printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
        printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
        m=q->TStation;
        m=m->next;
        printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
        printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
        printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
        while(m!=NULL)
        {
            printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
            m=m->next;
            i++;
        }
        i=1;
        q=q->next;
        printf("\n\n");
    }
}

int system_UI(void)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                                -------欢迎使用高铁管理系统-------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |       1. 高铁车次信息管理      |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |       2. 乘客信息管理          |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |       3. 高铁订票信息管理      |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |       4. 退出系统              |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    return choose;
}

void train_UI(TrainData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ----------高铁车次信息管理-------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |          1. 增开列车           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          2. 停开列车           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          3. 高铁车次查询       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          4. 修改列车信息       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          5. 查看所有车次       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          6. 退出系统           |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    train_choose(choose,head);
}

void train_choose(int choose,TrainData* head)
{
    switch(choose)
    {
        case 1:Insert_Train(head);break;
        case 2:Stop_Train(head);break;
        case 3:Seek_Train_UI(head);break;
        case 4:Revise_Train(head);break;
        case 5:print_train_File(head);break;
        case 6:goodbye();break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}

TrainData* Insert_Train(TrainData* head)
{
    system("cls");
	TrainData train;
	TrainData* p;
	StationData* m,*n;
	int temp;
	p=head;
	printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                               请输入新增列车相关信息\n");
	printf("                                                                                                               车次: ");
	scanf("%s",train.TrainNaber);
	printf("                                                                                                               始发站: ");
	scanf("%s",train.StartStation);
	printf("                                                                                                               终点站: ");
	scanf("%s",train.ArriveStation);
	printf("                                                                                                               运行距离: ");
	scanf("%f",&train.Mileage);
	printf("                                                                                                               停运信息: ");
	scanf("%s",train.Mod);
	printf("                                                                                                               发车时间: ");
	scanf("%s",train.StartTime);
	printf("                                                                                                               到达时间: ");
	scanf("%s",train.ArriveTime);
	printf("                                                                                                               停靠车站数: ");
	scanf("%d",&train.StationNum);
	printf("                                                                                                               特等座数量: ");
	scanf("%d",&train.ProSet);
	printf("                                                                                                               一等座数量: ");
	scanf("%d",&train.FirSet);
	printf("                                                                                                               二等座数量: ");
	scanf("%d",&train.SecSet);
	temp=train.StationNum;
	m = (StationData*)malloc(sizeof(StationData));
    train.TStation=m;
	while(temp--)
    {
        n = (StationData*)malloc(sizeof(StationData));
        printf("                                                                                                               停靠站: ");
        scanf("%s",n->StaName);
        printf("                                                                                                               到达时间: ");
        scanf("%s",n->StopTime);
        printf("                                                                                                               发车时间: ");
        scanf("%s",n->DriveTime);
        printf("                                                                                                               里程: ");
        scanf("%f",&n->StaMileage);
        m->next=n;
        m=n;
    }
    m->next=NULL;
	TrainData *s=(TrainData *)malloc(sizeof(TrainData));//开新节点，存入
	*s=train;
	s->next=NULL;
	while(p->next!=NULL)
    {
        p=p->next;
    }
        p->next=s;
	system ("cls");
	save_train_File(head);
}

TrainData* Stop_Train(TrainData* head)
{
    char name[10];
    TrainData* q=head;
    print_train(head);
    printf("                                                                                                               请选择停开列车车次:");
    scanf("%s",name);
     while(1)
    {
        if(strcmp(q->TrainNaber,name)==0)break;
        if(q->next==NULL)break;
        q=q->next;
    }
    if(strcmp(q->TrainNaber,name)==0)
    {
        printf("\n\n\n\n\n\n\n");
        printf("                                                                                                                   已找到待修改信息");
        printf("\n                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
        printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
        strcpy(q->Mod,"停运");
        printf("\n\n                                                                                                                   更改后的信息为");
        printf("\n                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
        printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
    }
    else if(q->next==NULL)printf("                                                                                                               未找到待修改信息\n");
    save_train_File(head);

}

void Seek_Train_UI(TrainData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ----------高铁车次信息查询-------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |          1. 车次查询           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          2. 始发站查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          3. 终点站查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          4. 发车时间查询       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          5. 停靠站查询         |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    Seek_Train(choose,head);
}

TrainData* Seek_Train(int choose,TrainData* head)
{
    TrainData* q=head;
    q=q->next;
    StationData* m,*n;
    int count=0,i=1;
    char input[30];
    switch(choose)
    {
        case 1:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询车次：");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->TrainNaber,input)==0)//匹配到查询目标
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                while(m!=NULL)
                {
                    printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                    m=m->next;
                    i++;
                }
                i=1;
            }
            q=q->next;
        }
        if(count==0)
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关列车\n");
        }break;

        case 2:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询始发站：");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->StartStation,input)==0)//匹配到查询目标
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                while(m!=NULL)
                {
                    printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                    m=m->next;
                    i++;
                }
                i=1;
            }
            q=q->next;
        }
        if(count==0)
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关列车\n");
        }break;

        case 3:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询终点站：");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->ArriveStation,input)==0)//匹配到查询目标
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                while(m!=NULL)
                {
                    printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                    m=m->next;
                    i++;
                }
                i=1;
            }
            q=q->next;
        }
        if(count==0)
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                无相关列车\n");
        }break;

        case 4:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询发车时间（XX:XX）：");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->StartTime,input)==0)//匹配到查询目标
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
                printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                while(m!=NULL)
                {
                    printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                    m=m->next;
                    i++;
                }
                i=1;
            }
            q=q->next;
        }
        if(count==0)
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                无相关列车\n");
        }break;

        case 5:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询车站：");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            n=q->TStation;
            n=n->next;
            while(n!=NULL)
            {
                if(strcmp(n->StaName,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                    q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                    q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                    m=q->TStation;
                    m=m->next;
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    while(m!=NULL)
                    {
                        printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                        m=m->next;
                        i++;
                    }
                    i=1;
                }
                n=n->next;
            }

            q=q->next;
        }
        if(count==0)
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                无相关列车\n");
        }break;

        default:printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                error");break;
    }

}

TrainData* Revise_Train(TrainData* head)
{
    TrainData* p=head,* q;
    StationData* m,* n;
    int i=1,temp;
    char trainname[20];
    print_train(head);
    printf("                                                                                                                  请输入需要修改的车次： ");
    scanf("%s",trainname);
    system("cls");
    p=p->next;
    while(p!=NULL)
    {
        q=p->next;
        if(strcmp(q->TrainNaber,trainname)==0)
        {
            printf("\n\n\n\n                                                                                                                 找到待修改列车：");
            printf("\n\n");
            printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
            printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
            printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
            q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
            q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
            m=q->TStation;
            m=m->next;
            printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
            printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
            printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
            while(m!=NULL)
            {
                printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                m=m->next;
                i++;
            }
            break;
        }
        i=1;
        p=p->next;
        printf("\n\n");
    }
	TrainData train;
	printf("\n\n                                                                                                               请输入修改后的列车相关信息\n");
    strcpy(train.TrainNaber,trainname);
	printf("\n                                                                                                               始发站: ");
	scanf("%s",train.StartStation);
	printf("\n                                                                                                               终点站: ");
	scanf("%s",train.ArriveStation);
	printf("\n                                                                                                               运行距离: ");
	scanf("%f",&train.Mileage);
	printf("\n                                                                                                               停运信息: ");
	scanf("%s",train.Mod);
	printf("\n                                                                                                               发车时间: ");
	scanf("%s",train.StartTime);
	printf("\n                                                                                                               到达时间: ");
	scanf("%s",train.ArriveTime);
	printf("\n                                                                                                               停靠车站数: ");
	scanf("%d",&train.StationNum);
	printf("\n                                                                                                               特等座数量: ");
	scanf("%d",&train.ProSet);
	printf("\n                                                                                                               一等座数量: ");
	scanf("%d",&train.FirSet);
	printf("\n                                                                                                               二等座数量: ");
	scanf("%d",&train.SecSet);
	temp=train.StationNum;
	m = (StationData*)malloc(sizeof(StationData));
    train.TStation=m;
	while(temp--)
    {
        n = (StationData*)malloc(sizeof(StationData));
        printf("\n                                                                                                               停靠站: ");
        scanf("%s",n->StaName);
        printf("\n                                                                                                               到达时间: ");
        scanf("%s",n->StopTime);
        printf("\n                                                                                                               发车时间: ");
        scanf("%s",n->DriveTime);
        printf("\n                                                                                                               里程: ");
        scanf("%f",&n->StaMileage);
        m->next=n;
        m=n;
    }
    m->next=NULL;
    TrainData *s=(TrainData *)malloc(sizeof(TrainData));//开新节点，存入
	*s=train;
	s->next=q->next;
	p->next=s;
	free(q);
    system ("cls");
    q=s;
    i=1;
    printf("\n\n\n\n\n\n\n\n                                                                                                        更改后的信息为");
    printf("\n\n");
            printf("                                                                 | 车次 || 始发站 || 终点站 || 运行距离 || 停运信息 || 发车时间 || 到达时间 || 停靠车站数 || 特等座数量 || 一等座数量 || 二等座数量 |\n");
            printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
            printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
            q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
            q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
            m=q->TStation;
            m=m->next;
            printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
            printf("                                                                 |             停靠站             ||            到达时间            ||            发车时间            ||            里程            |\n");
            printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
            while(m!=NULL)
            {
                printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                m=m->next;
                i++;
            }
	save_train_File(head);

}

//乘客信息管理***********************************************************************************************************************************************************************

PassengerData* read_passengeer_File(void)
{
	FILE* fp;
	PassengerData* head, * p, * q;
	p = q = (PassengerData*)malloc(sizeof(PassengerData));//开辟空间赋指针
	if ((fp = fopen("passenger.txt", "r")) == NULL)//文件指针赋值为NULL
	{
		printf("                                                                                                                                                                        can't open file\n");
		exit(0);
	}
	head = p;//头指针赋值并读入

	while (!feof(fp))
	{
		q = (PassengerData*)malloc(sizeof(PassengerData));
        fscanf(fp, "%s %s %s %s %s %s\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
        p->next = q;
		p = q;
	}
	p->next = NULL;
	fclose(fp);
	return head;
}

void save_passenger_File(PassengerData* L)
{
	if (L == NULL)//头指针空
	{
		printf("\n                                                                                                                can't save file\n");
		return;
	}
	FILE* fp = fopen("passenger.txt", "wb");
	if (fp == NULL)//文件指针空
	{
		printf("\n                                                                                                                can't open file\n");
		return;
	}
	PassengerData* q ;
	q=L;
	q=q->next;
	while (q != NULL)
	{
		fprintf(fp,"%s %s %s %s %s %s\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
		q = q->next;
	}
	//收尾处理
	fclose(fp);
	fp = NULL;

}

void print_passenger(PassengerData* head)
{
    PassengerData* q;
    int i=1;
    q=head;
    q=q->next;
    printf("\n\n\n\n");
    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
    while(q!=NULL)
    {
        printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
        printf("                                                                 |                                                                                                                                  |\n");
        q=q->next;
    }
}

void passenger_UI(PassengerData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ------------乘客信息管理----------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |         1. 增加乘客            |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         2. 删除乘客            |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         3. 乘客信息查询        |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         4. 修改乘客信息        |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         5. 查看所有乘客        |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         6. 退出系统            |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    passenger_choose(choose,head);
}

void passenger_choose(int choose,PassengerData* head)
{
    switch(choose)
    {
        case 1:Insert_Passenger(head);break;
        case 2:Delete_Passenger(head);break;
        case 3:Seek_Passenger_UI(head);break;
        case 4:Revise_passenger(head);break;
        case 5:print_passenger(head);break;
        case 6:goodbye();break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}

PassengerData* Insert_Passenger(PassengerData* head)
{
    system("cls");
    PassengerData pass;
    PassengerData* p;
	p=head;
	printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                               请输入新增乘客相关信息\n");
	printf("                                                                                                               证件号: ");
	scanf("%s",pass.IDNumber);
	printf("                                                                                                               乘客姓名: ");
	scanf("%s",pass.PaName);
	printf("                                                                                                               证件类型: ");
	scanf("%s",pass.IDType);
	printf("                                                                                                               联系电话: ");
	scanf("%s",pass.PaTel);
	printf("                                                                                                               紧急联系人: ");
	scanf("%s",pass.UrName);
	printf("                                                                                                               联系人电话: ");
	scanf("%s",pass.UrTel);
	PassengerData *s=(PassengerData *)malloc(sizeof(PassengerData));//开新节点，存入
	*s=pass;
	s->next=NULL;
	while(p->next!=NULL)
    {
        p=p->next;
    }
        p->next=s;
	system ("cls");
	save_passenger_File(head);
}

PassengerData* Delete_Passenger(PassengerData* L)
{

    PassengerData* p=L;
    PassengerData* q;
    int i;
    char id[20];
    int n,flag=0;
    printf("                                                                                                      请输入要删除的乘客证件号：");
    scanf("%s",id);
	while(1)
    {
        if(strcmp(p->IDNumber,id)==0)break;
        if(p->next==NULL)break;
        q=p;
        p=p->next;

    }
    if(strcmp(p->IDNumber,id)==0)
    {
        printf("                                                                                                      已找到待删除信息：\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",p->IDNumber,p->PaName,p->IDType,p->PaTel,p->UrName,p->UrTel);
        printf("                                                                                                      确认是否删除？（Y:1 N:0）");
        scanf("%d",&n);
        if(n==1)
        {
            if(p==L)
                L=p->next;
            else
                q->next=p->next;
        }
        save_passenger_File(L);
        flag=1;
    }
    if(p->next==NULL&&flag==0) printf("\n                                                                            删除信息不存在");
	return L;
}

void Seek_Passenger_UI(PassengerData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                -------------乘客信息查询---------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |        1. 乘客姓名查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        2. 乘客证件号查询       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        3. 乘客电话查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        4. 紧急联系人查询       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        5. 退出系统             |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    Seek_Passenger(choose,head);
}

PassengerData* Seek_Passenger(int choose,PassengerData* head)
{
    PassengerData* q=head;
    q=q->next;
    int count=0;
    char input[30];
    int tel;
    switch(choose)
    {
        case 1:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询姓名：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->PaName,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关乘客\n");
        }break;

        case 2:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询证件号：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->IDNumber,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关乘客\n");
        }break;

        case 3:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询电话号码：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->PaTel,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关乘客\n");
        }break;

        case 4:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询紧急联系人：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->UrName,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关乘客\n");
        }break;
        case 5:goodbye();break;
        default:printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                error");break;
    }

}

PassengerData* Revise_passenger(PassengerData* head)
{
    PassengerData* p=head,* q;
    int i=1,temp;
    char name[20];
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                                  请输入需要修改的乘客的证件号： ");
    scanf("%s",name);
    system("cls");
    p=p->next;
    while(p!=NULL)
    {
        q=p->next;
        if(strcmp(q->IDNumber,name)==0)
        {
            printf("\n\n\n\n\n\n\n\n\n                                                                                                                       找到待修改列车：");
            printf("\n\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
            break;
        }
        i=1;
        p=p->next;
    }
	PassengerData pass;
	printf("\n\n                                                                                                               请输入修改后的乘客相关信息\n");
	printf("\n                                                                                                               证件号: ");
	scanf("%s",pass.IDNumber);
	printf("\n                                                                                                               姓名: ");
	scanf("%s",pass.PaName);
	printf("\n                                                                                                               证件类型: ");
	scanf("%s",pass.IDType);
	printf("\n                                                                                                               联系电话: ");
	scanf("%s",pass.PaTel);
	printf("\n                                                                                                               紧急联系人: ");
	scanf("%s",pass.UrName);
	printf("\n                                                                                                               联系人电话: ");
	scanf("%s",pass.UrTel);
    PassengerData *s=(PassengerData *)malloc(sizeof(PassengerData));//开新节点，存入
	*s=pass;
	s->next=q->next;
	p->next=s;
	free(q);
    system ("cls");
    q=s;
    i=1;
    printf("\n\n\n\n\n\n\n\n                                                                                                                     更改后的信息为");
    printf("\n\n");
                    printf("                                                                 |            证件号            ||     姓名     ||    证件类型    ||      联系电话      ||    紧急联系人    ||      联系人电话      |\n");
                    printf("                                                                 |—————————————————————————————————————————————————————————————————|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
	save_passenger_File(head);
	printf("\n                                                                                                                     ");
	system ("pause");
    system ("cls");
}

//高铁订票信息管理***********************************************************************************************************************************************************************
TrainSeat* crate_seat(TrainData* train,TicketData* head3)
{
    TrainSeat* head,* p,* q;
    TrainData* t;
    Seat* m,* n;
    SeatStation* z;
    int code,temp;
    head = p = q =(TrainSeat*)malloc(sizeof(TrainSeat));
    t = train;
    t=t->next;
    while(t!=NULL)
    {
        //printf("进循环了\n");
        code=0;
        q = (TrainSeat*)malloc(sizeof(TrainSeat));
        strcpy(q->train,t->TrainNaber);
        q->seat = m = n = (Seat*)malloc(sizeof(Seat));
        temp=t->SecSet;
        while(temp--)
        {
            code++;
            n = (Seat*)malloc(sizeof(Seat));
            n->num=code;
            n->satation = z = (SeatStation*)malloc(sizeof(SeatStation));
            z->next=NULL;
            m->next=n;
            m=n;
        }
        m->next=NULL;
        p->next = q;
		p = q;
		t=t->next;
    }
    p->next=NULL;
    head=set_seat(head,train,head3);
    //print_seat_list(head);
    return head;

}

TrainSeat* set_seat(TrainSeat* head1,TrainData* head2,TicketData* head3)
{
    TrainSeat* s=head1;//列车座位链表的头
    TrainData* t=head2;//列车链表的头
    TicketData* k=head3;//车票链表的头
    StationData* h;
    SeatStation* p,* q;
    Seat* m,*n;
    int start,arrive;
    s=s->next;
    t=t->next;
    k=k->next;
    while(k!=NULL)//遍历车票
    {
        //printf("进循环了\n");
        t=head2;
        t=t->next;
        while(t!=NULL)//遍历列车
        {
            //printf("进循环了\n");
            if(strcmp(k->Train,t->TrainNaber)==0)//找到这张车票对应的列车
            {
                //printf("进if了\n");
                h=t->TStation;//指针指到这辆车的停靠站链表
                start=set_code(k->StartStation,h);//起始站转码
                arrive=set_code(k->ArriveStation,h);//终点站转码
                s=head1;
                s=s->next;
                //printf("%s",s->train);
                while(s!=NULL)//遍历列车座位链表
                {
                    //printf("进循环了\n");
                    if(strcmp(k->Train,s->train)==0)//找到这张车票对应的列车座位链表
                    {
                        m=s->seat;//m指向列车座位链表的座位链表
                        m=m->next;
                        while(k->SetNum!=m->num)
                            m=m->next;
                        if(k->SetNum==m->num)//找到这张车票对应座位
                        {
                            p = m->satation;
                            while(p->next!=NULL) p=p->next;
                            q=(SeatStation*)malloc(sizeof(SeatStation));
                            q->arrivecode=arrive;
                            q->startcode=start;
                            strcpy(q->date,k->Date);
                            p->next=q;
                            p=q;
                            p->next=NULL;
                        }
                    }
                    s=s->next;
                }
            }
            t=t->next;
        }
        k=k->next;
    }
    //print_seat_list(head1);
    return head1;

}

int set_code(char station[],StationData* head)
{
    int code;
    StationData* p=head;
    p=p->next;
    while(p!=NULL)
    {
        if(strcmp(station,p->StaName)==0)
        {
            return p->stacode;
        }

        p=p->next;
    }
}

void print_seat_list(TrainSeat* head)
{
    TrainSeat* p=head;
    Seat* q;
    SeatStation* r;
    p=p->next;
    while(p!=NULL)
    {
        printf("%s",p->train);
        q=p->seat;
        q=q->next;
        while(q!=NULL)
        {
            printf("\n %d",q->num);
            r=q->satation;
            r=r->next;
            while(r!=NULL)
            {
                printf(" || %d %d %s || ",r->startcode,r->arrivecode,r->date);
                r=r->next;
            }
            q=q->next;
        }
        printf(" \n");
        p=p->next;
    }
    system("pause");
}

TicketData* read_ticket_File(void)
{
	FILE* fp;
	TicketData* head, * p, * q;
	p = q = (TicketData*)malloc(sizeof(TicketData));//开辟空间赋指针
	if ((fp = fopen("booking.txt", "r")) == NULL)//文件指针赋值为NULL
	{
		printf("                                                                                                                                                                        can't open file\n");
		exit(0);
	}
	head = p;//头指针赋值并读入

	while (!feof(fp))
	{
		q = (TicketData*)malloc(sizeof(TicketData));
        fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %d %f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,&q->SetNum,&q->price);
        p->next = q;
		p = q;
	}
	p->next = NULL;
	fclose(fp);
	return head;
}

void save_ticket_File(TicketData* L)
{
	if (L == NULL)//头指针空
	{
		printf("\n                                                                                                                can't save file\n");
		return;
	}
	FILE* fp = fopen("booking.txt", "wb");
	if (fp == NULL)//文件指针空
	{
		printf("\n                                                                                                                can't open file\n");
		return;
	}
	TicketData* q ;
	q=L;
	q=q->next;
	while (q != NULL)
	{
        fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s %d %.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
        q = q->next;
	}
	//收尾处理
	fclose(fp);
	fp = NULL;

}

void print_all_ticket(TicketData* head)
{
    TicketData* q;
    int i=1;
    q=head;
    q=q->next;
    printf("\n\n\n\n");
    printf("               |            订单号            ||     乘车日期     ||  车次  ||    始发站    ||    终点站    ||  证件类别  ||            证件号            ||    乘客姓名    ||  开车时间  ||  到达时间  || 座位等级 || 座位号 ||  票价  |\n");
    printf("               |————————————————————————————————————————————————————————————————————————————————————————————————————————————|\n");
    while(q!=NULL)
    {
        printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
    printf("               |                                                                                                                                                                                                                        |\n");
        q=q->next;
    }
}

void booking_UI(TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ------------订票信息管理----------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |          1. 订票               |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          2. 退票               |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          3. 车票信息查询       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          4. 余票查询           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          5. 查看所有车票       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          6. 打印车票           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          7. 退出系统           |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    booking_choose(choose,head1,head2,head3,head4);
}

void booking_choose(int choose,TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4)
{
    switch(choose)
    {
        case 1:book_ticket(head1,head2,head3,head4);break;
        case 2:refund_ticket(head2);break;
        case 3:Seek_ticket_UI(head2);break;
        case 4:seek_remain_ticket(head3,head1);break;
        case 5:print_all_ticket(head2);break;
        case 6:print_one_ticket(head2);break;
        case 7:goodbye();break;
        default:printf("\n\n\n\n\n\n\n\n\n                            error");break;
    }
}

void refund_ticket(TicketData* head2)
{
    TicketData* q=head2;
    TicketData* p;
    int i;
    int year,month,day,hour,miniti;
    char id[20];
    int n,flag=0;
    nowtime ntime=Get_Sys_Time();
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                               请输入要删除的订单号：");
    scanf("%s",id);
	while(1)
    {
        if(strcmp(q->TicketNum,id)==0)break;
        if(q->next==NULL)break;
        p=q;
        q=q->next;

    }
    if(strcmp(q->TicketNum,id)==0)
    {
        printf("\n\n");
        printf("                                                                                                               已找到待删除信息：\n\n");
        printf("               |            订单号            ||     乘车日期     ||  车次  ||    始发站    ||    终点站    ||  证件类别  ||            证件号            ||    乘客姓名    ||  开车时间  ||  到达时间  || 座位等级 || 座位号 ||  票价  |\n");
        printf("               |————————————————————————————————————————————————————————————————————————————————————————————————————————————|\n");
        printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
        year=(q->Date[0]-'0')*(1000)+(q->Date[1]-'0')*(100)+(q->Date[2]-'0')*(10)+(q->Date[3]-'0');
        month=(q->Date[4]-'0')*(10)+(q->Date[5]-'0');
        day=(q->Date[6]-'0')*(10)+(q->Date[7]-'0');
        hour=(q->StartTime[0]-'0')*(10)+(q->StartTime[2]-'0');
        miniti=(q->StartTime[4]-'0')*(10)+(q->StartTime[5]-'0');
        if(year==ntime.year&&month==ntime.month&&day==ntime.day&&hour>=ntime.hour+2)
            printf("\n\n\n                                                                                                     提示：距开车不足两小时，退票将扣除%.2f手续费！",(0.05)*q->price);
        printf("\n\n                                                                                                               确认是否删除？（Y:1 N:0）");
        scanf("%d",&n);
        if(n==1)
        {
            if(p==head2->next)
                head2=q->next;
            else
                p->next=q->next;
                printf("\n\n                                                                                                                     退票成功！");
        }
        save_ticket_File(head2);
        flag=1;
    }
    if(q->next==NULL&&flag==0) printf("\n                                                                                                               删除信息不存在\n");
	return head2;
}

void book_ticket(TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4)
{
    char num;
    char trainname[20];
    PassengerData npd;
    TicketData np;
    TicketData* td,* k;
    int seatnum,tag=0;
    TrainData* t;
    Booking* b;
    StationData* s;
    Booking* head=seek_remain_ticket(head3,head1);
    PassengerData* pd,*z;
    if(head==NULL)
    {
        printf("\n                                                                    无余票\n");
        return 0;
    }
    printf("\n                                                                                                                请选择车次： ");
    scanf("%s",trainname);
    b=head;
    b=b->next;
    t=head1;
    t=t->next;
    pd=head4;
    pd=pd->next;
    td=head2;
    td=td->next;
    while(b!=NULL)
    {
        if(strcmp(b->trainnum,trainname)==0)
        {
            np.SetNum = b->seatnum[0];
            num = b->seatnum[0]+'0';
            strcpy(np.StartStation,b->startname);
            strcpy(np.ArriveStation,b->arrivename);
            strcpy(np.Date,b->date);
            strcpy(np.Train,trainname);
            break;
        }

        b=b->next;
    }
    while(t!=NULL)
    {
        if(strcmp(t->TrainNaber,trainname)==0)
        {
            s=t->TStation;
            s=s->next;
            while(s!=NULL)
            {
                if(strcmp(s->StaName,np.StartStation)==0)
                {
                    np.price=((-1)*s->StaMileage);
                    strcpy(np.StartTime,s->DriveTime);
                    s=s->next;
                    while(s!=NULL)
                    {
                        if(strcmp(s->StaName,np.ArriveStation)==0)
                        {
                            np.price=(0.46)*(np.price+s->StaMileage);
                            strcpy(np.ArriveTime,s->StopTime);
                            tag=1;
                            break;
                        }
                        s=s->next;
                    }
                }
                s=s->next;
                if(tag==1)break;
            }
        }
        if(tag==1)break;
        t=t->next;
    }
    printf("                                                                                                                请输入乘客证件号： ");
    scanf("%s",np.IDNumber);
    system("cls");
    while(pd!=NULL)
    {
        if(strcmp(pd->IDNumber,np.IDNumber)==0)
        {
            strcpy(np.IDType,pd->IDType);
            strcpy(np.Name,pd->PaName);
            strcpy(np.SetLevel,"二等座");
            //printf("进循环了");
            break;
        }
        pd=pd->next;
    }
    if(pd==NULL)
    {
        printf("添加新乘客？");
        Insert_Passenger(head4);
        pd=head4;
        pd=pd->next;
        while(pd!=NULL)
        {
            if(strcmp(pd->IDNumber,np.IDNumber)==0)
            {
                strcpy(np.IDType,pd->IDType);
                strcpy(np.Name,pd->PaName);
                strcpy(np.SetLevel,"二等座");
                break;
            }
            pd=pd->next;
        }
    }
    strcpy(np.TicketNum,np.Date);
    np.TicketNum[8]= '-' ;
    np.TicketNum[13]='-' ;
    if(strlen(np.Train)==4)
    {
        np.TicketNum[9]='0';
        np.TicketNum[10]=np.Train[1];
        np.TicketNum[11]=np.Train[2];
        np.TicketNum[12]=np.Train[3];
    }
    else if(strlen(np.Train)==3)
    {
        np.TicketNum[9]='0';
        np.TicketNum[10]='0';
        np.TicketNum[11]=np.Train[1];
        np.TicketNum[12]=np.Train[2];
    }
    else if(strlen(np.Train)==2)
    {
        np.TicketNum[9]='0';
        np.TicketNum[10]='0';
        np.TicketNum[11]='0';
        np.TicketNum[12]=np.Train[1];
    }
    if(np.SetNum<10)
    {
        np.TicketNum[14]='0';
        np.TicketNum[15]='0';
        np.TicketNum[16]= num;
        //printf("%c  ",num);
    }
    else if(np.SetNum>=10)
    {
        np.TicketNum[14]='0';
        np.TicketNum[15]= (np.SetNum/10)+'0';
        np.TicketNum[16]= (np.SetNum%10)+'0';
    }
    np.TicketNum[17] = '\0';
    np.next=NULL;
    k=(TicketData *)malloc(sizeof(TicketData));
    *k=np;
    while(td->next!=NULL)td=td->next;
    td->next=k;
    print_ticket(k);
    save_ticket_File(head2);
    //system("pause");
}

void print_one_ticket(TicketData* head2)
{
    TicketData* p;
    char order[20];
    printf("\n\n\n\n\n\n\n                                                                                                                请输入订单号： ");
    scanf("%s",order);
    p=head2;
    p=p->next;
    while(p!=NULL)
    {
        if(strcmp(p->TicketNum,order)==0)
        {
            print_ticket(p);
            return 0;
        }
        p=p->next;
    }
    if(p==NULL)
        printf("无相关订单");
}

void print_ticket(TicketData* head)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                ——————————————————————————————————————————————\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |         %10s 站                     %s                   %10s 站            |\n",head->StartStation,head->Train,head->ArriveStation);
    printf("                                                                                |                                        -------->                                         |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |   %c%c%c%c 年 %c%c 月 %c%c 日 %s 开                                      %2d 号座              |\n",head->Date[0],head->Date[1],head->Date[2],head->Date[3],head->Date[4],head->Date[5],head->Date[6],head->Date[7],head->StartTime,head->SetNum);
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |         %7.2f 元                                                   二等座              |\n",head->price);
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |     %20s %10s                                                      |\n",head->IDNumber,head->Name);
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |                                  中国铁路祝您旅途愉快                                    |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                ——————————————————————————————————————————————\n");
    system("pause");
}

Booking* seek_remain_ticket(TrainSeat* head,TrainData* train)
{
    char date[20];
    char start[20],arrive[20];
    int startcode,arrivecode,flag=0,tag=0;
    int year,month,day;
    char trainnum[100][20];
    nowtime ntime=Get_Sys_Time();
    TrainData* p;
    StationData* q;
    Booking* m,*n,*Bhead;
    printf("\n\n\n\n\n\n\n                                                                                                                请输入乘车日期： ");
    scanf("%s",date);
    printf("                                                                                                                请输入起始站： ");
    scanf("%s",start);
    printf("                                                                                                                请输入终点站： ");
    scanf("%s",arrive);
    p=train;
    p=p->next;
    Bhead=n=m=(Booking*)malloc(sizeof(Booking));
    year=(date[0]-'0')*(1000)+(date[1]-'0')*(100)+(date[2]-'0')*(10)+(date[3]-'0');
    month=(date[4]-'0')*(10)+(date[5]-'0');
    day=(date[6]-'0')*(10)+(date[7]-'0');
    if(year!=ntime.year)
    {
        printf("\n                                                                                                                只能预定两个月内的车票");
        return 0;
    }
    else if(month>(ntime.month+2))
    {
        printf("\n                                                                                                                只能预定两个月内的车票");
        return 0;
    }
    else if(month==(ntime.month+2))
    {
        if(day>ntime.day)
        {
            printf("\n                                                                                                                只能预定两个月内的车票");
            return 0;
        }

    }
    while(p!=NULL)
    {
        q=p->TStation;
        q=q->next;
        while(q!=NULL)
        {
            flag=0;
            if(strcmp(start,q->StaName)==0)//找到相同的起始站
            {
                startcode=q->stacode;
                q=q->next;
                while(q!=NULL)//原地继续遍历停靠站链表
                {
                    //printf("进循环了");
                    if(strcmp(arrive,q->StaName)==0)
                    {
                        flag=1;
                        tag=1;
                        arrivecode=q->stacode;
                        break;
                    }
                    q = q->next;
                }
                if(flag==1)
                {
                    //printf("进if了");
                    n=(Booking*)malloc(sizeof(Booking));
                    strcpy(n->trainnum,p->TrainNaber);
                    n->startcode=startcode;
                    n->arrivecode=arrivecode;
                    strcpy(n->startname,start);
                    strcpy(n->arrivename,arrive);
                    strcpy(n->date,date);
                    m->next=n;
                    m=n;
                    m->next=NULL;
                    break;
                }
                else break;
            }
            //printf("出循环了");
            q=q->next;
        }
        //printf("出循环了");
        p=p->next;
    }
    //printf("出循环了");
    if(tag==0)
    {
        printf("                                                                                                                无可达列车");
        return 0;
    }
    Bhead=judge_ticket(date,Bhead,head);
    print_bhead(Bhead);
    return Bhead;

}

Booking* judge_ticket(char date[10],Booking* bhead,TrainSeat* thead)
{
    Booking* p,* q;
    TrainSeat* m;
    Seat* n;
    SeatStation* t;
    TrainData* v;
    int falg=0,count=0;
    p=bhead;
    p=p->next;

    while(p!=NULL)
    {
        m=thead;
        m=m->next;
        count=0;
        while(m!=NULL)
        {
            //printf("进ts循环了");
            if(strcmp(p->trainnum,m->train)==0)//找到这辆车对应的座位状态表
            {
                //printf("%s\n",p->trainnum);
                n=m->seat;
                n=n->next;
                while(n!=NULL)//遍历座位
                {
                   // printf("进seat循环了");
                    t=n->satation;
                    t=t->next;
                    while(t!=NULL)//遍历座位的状态
                    {
                       // printf("进ss循环了");
                        //printf("%s %s %d %d ",date,t->date,t->arrivecode,p->startcode);
                        if(strcmp(date,t->date)==0 && (t->arrivecode > p->startcode)  )break;//判断条件：这个状态的到达编码大于乘客的起始编码且在同一天，满足条件就判定座位不可以坐
                        t=t->next;
                    }
                    //printf("出ss循环了");
                    if(t==NULL)//遍历完所有状态
                    {
                        p->seatnum[count++]=n->num;//把这个座位号加在booking链表的可定座位数组里
                        //printf("%d\n", p->seatnum[count]);
                    }
                    n=n->next;
                }
                //printf("出seat循环了");
            }

            m=m->next;
        }
        p->seat=count;
        p=p->next;
    }

    return bhead;
}

void print_bhead(Booking* head)
{
    Booking* q;
    q=head;
    q=q->next;
    if(q==NULL)
    {
        printf("无余票");
        return 0;
    }
    printf("                                                                                                                |  车次  ||  剩余票数  |\n");
    while(q!=NULL)
    {
        printf("                                                                                                                    %s         %d\n",q->trainnum,q->seat);
//        for(int i=0;i<q->seat;i++)
//        {
//            printf(" %d",q->seatnum[i]);
//        }
        q=q->next;
    }
}

void Seek_ticket_UI(TicketData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                -------------车票信息查询---------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |        1. 乘客姓名查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        2. 乘客证件号查询       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        3. 乘车日期查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        4. 所乘车次查询         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        5. 退出系统             |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             请选择: ");
    scanf("%d",&choose);//用户选择功能
    system("cls");
    Seek_ticket(choose,head);
}

void Seek_ticket(int choose,TicketData* head)
{
    TicketData* q=head;
    q=q->next;
    int count=0;
    char input[30];
    int tel;
    switch(choose)
    {
        case 1:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询姓名：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->Name,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            订单号            ||     乘车日期     ||  车次  ||    始发站    ||    终点站    ||  证件类别  ||            证件号            ||    乘客姓名    ||  开车时间  ||  到达时间  || 座位等级 || 座位号 ||  票价  |\n");
                    printf("               |————————————————————————————————————————————————————————————————————————————————————————————————————————————|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关订票\n");
        }break;

        case 2:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入查询证件号：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->IDNumber,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            订单号            ||     乘车日期     ||  车次  ||    始发站    ||    终点站    ||  证件类别  ||            证件号            ||    乘客姓名    ||  开车时间  ||  到达时间  || 座位等级 || 座位号 ||  票价  |\n");
                    printf("               |————————————————————————————————————————————————————————————————————————————————————————————————————————————|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关订票\n");
        }break;

        case 3:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入乘车日期：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->Date,input)==0)//匹配到查询目标
                {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            订单号            ||     乘车日期     ||  车次  ||    始发站    ||    终点站    ||  证件类别  ||            证件号            ||    乘客姓名    ||  开车时间  ||  到达时间  || 座位等级 || 座位号 ||  票价  |\n");
                    printf("               |————————————————————————————————————————————————————————————————————————————————————————————————————————————|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关订票\n");
        }break;
        case 4:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        请输入所乘车次：");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->Train,input)==0)//匹配到查询目标
                {
                    count++;
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            订单号            ||     乘车日期     ||  车次  ||    始发站    ||    终点站    ||  证件类别  ||            证件号            ||    乘客姓名    ||  开车时间  ||  到达时间  || 座位等级 || 座位号 ||  票价  |\n");
                    printf("               |————————————————————————————————————————————————————————————————————————————————————————————————————————————|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               无相关订票\n");
        }break;
        case 5:goodbye();break;
        default:printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                error");break;
    }

}
