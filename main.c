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
        printf("\n\n                                                                                                               �Ƿ����ʹ��ϵͳ����Y:1 N:0) ");
        scanf("%d",&choose);
        system("cls");
        if(choose==0){goodbye();break;}
        else continue;
    }
}


void goodbye()
{
    system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                               ��ӭ�´�ʹ��~");
	exit(0);
}

nowtime Get_Sys_Time() //���ص�ǰϵͳʱ��
{
    struct tm today; //���ʱ��Ľṹ��
    time_t one; //���ʱ�������
    nowtime now;
    one=time(&one); //���ϵͳʱ��
    today=*(gmtime(&one)); //�� time_t ��ʽϵͳʱ��תΪ struct tm ��ʽ
    now.year=today.tm_year-100+2000; //2011 �귵�� 111
    now.month=today.tm_mon+1; //9 �·��� 8;
    now.day=today.tm_mday;
    now.hour= today.tm_hour;
    now.minit= today.tm_min;
    return now;
}

//����������Ϣ����***********************************************************************************************************************************************************************

TrainData* read_train_File()
{
	FILE* fp;
	TrainData* head, * p, * q;
	StationData* m,*n;
	int temp=0,code;
	p = q = (TrainData*)malloc(sizeof(TrainData));//���ٿռ丳ָ��
	if ((fp = fopen("train.txt", "r")) == NULL)//�ļ�ָ�븳ֵΪNULL
	{
		printf("                                                                                                                                                                        can't open file\n");
		exit(0);
	}
	head = p;//ͷָ�븳ֵ������

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
	if (L == NULL)//ͷָ���
	{
		printf("\n                                                                                                                can't save file\n");
		return;
	}
	FILE* fp = fopen("train.txt", "wb");
	if (fp == NULL)//�ļ�ָ���
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
	//��β����
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
    printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
        printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
        printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
        m=q->TStation;
        m=m->next;
        printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
        printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
        printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
    printf("\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                                -------��ӭʹ�ø�������ϵͳ-------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |       1. ����������Ϣ����      |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |       2. �˿���Ϣ����          |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |       3. ������Ʊ��Ϣ����      |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |       4. �˳�ϵͳ              |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
    system("cls");
    return choose;
}

void train_UI(TrainData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ----------����������Ϣ����-------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |          1. �����г�           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          2. ͣ���г�           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          3. �������β�ѯ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          4. �޸��г���Ϣ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          5. �鿴���г���       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          6. �˳�ϵͳ           |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
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
	printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                               �����������г������Ϣ\n");
	printf("                                                                                                               ����: ");
	scanf("%s",train.TrainNaber);
	printf("                                                                                                               ʼ��վ: ");
	scanf("%s",train.StartStation);
	printf("                                                                                                               �յ�վ: ");
	scanf("%s",train.ArriveStation);
	printf("                                                                                                               ���о���: ");
	scanf("%f",&train.Mileage);
	printf("                                                                                                               ͣ����Ϣ: ");
	scanf("%s",train.Mod);
	printf("                                                                                                               ����ʱ��: ");
	scanf("%s",train.StartTime);
	printf("                                                                                                               ����ʱ��: ");
	scanf("%s",train.ArriveTime);
	printf("                                                                                                               ͣ����վ��: ");
	scanf("%d",&train.StationNum);
	printf("                                                                                                               �ص�������: ");
	scanf("%d",&train.ProSet);
	printf("                                                                                                               һ��������: ");
	scanf("%d",&train.FirSet);
	printf("                                                                                                               ����������: ");
	scanf("%d",&train.SecSet);
	temp=train.StationNum;
	m = (StationData*)malloc(sizeof(StationData));
    train.TStation=m;
	while(temp--)
    {
        n = (StationData*)malloc(sizeof(StationData));
        printf("                                                                                                               ͣ��վ: ");
        scanf("%s",n->StaName);
        printf("                                                                                                               ����ʱ��: ");
        scanf("%s",n->StopTime);
        printf("                                                                                                               ����ʱ��: ");
        scanf("%s",n->DriveTime);
        printf("                                                                                                               ���: ");
        scanf("%f",&n->StaMileage);
        m->next=n;
        m=n;
    }
    m->next=NULL;
	TrainData *s=(TrainData *)malloc(sizeof(TrainData));//���½ڵ㣬����
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
    printf("                                                                                                               ��ѡ��ͣ���г�����:");
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
        printf("                                                                                                                   ���ҵ����޸���Ϣ");
        printf("\n                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
        printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
        strcpy(q->Mod,"ͣ��");
        printf("\n\n                                                                                                                   ���ĺ����ϢΪ");
        printf("\n                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
        printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
        printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
        q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
        q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
    }
    else if(q->next==NULL)printf("                                                                                                               δ�ҵ����޸���Ϣ\n");
    save_train_File(head);

}

void Seek_Train_UI(TrainData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ----------����������Ϣ��ѯ-------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |          1. ���β�ѯ           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          2. ʼ��վ��ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          3. �յ�վ��ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          4. ����ʱ���ѯ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          5. ͣ��վ��ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
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
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ���Σ�");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->TrainNaber,input)==0)//ƥ�䵽��ѯĿ��
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ������г�\n");
        }break;

        case 2:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯʼ��վ��");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->StartStation,input)==0)//ƥ�䵽��ѯĿ��
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ������г�\n");
        }break;

        case 3:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ�յ�վ��");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->ArriveStation,input)==0)//ƥ�䵽��ѯĿ��
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                ������г�\n");
        }break;

        case 4:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ����ʱ�䣨XX:XX����");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            if(strcmp(q->StartTime,input)==0)//ƥ�䵽��ѯĿ��
            {
                count++;
                printf("\n\n\n\n");
                printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                m=q->TStation;
                m=m->next;
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
                printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                ������г�\n");
        }break;

        case 5:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ��վ��");
            scanf("%s",input);
            system("cls");
        while(q!=NULL)
        {
            n=q->TStation;
            n=n->next;
            while(n!=NULL)
            {
                if(strcmp(n->StaName,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
                    q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
                    q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
                    m=q->TStation;
                    m=m->next;
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
        printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                ������г�\n");
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
    printf("                                                                                                                  ��������Ҫ�޸ĵĳ��Σ� ");
    scanf("%s",trainname);
    system("cls");
    p=p->next;
    while(p!=NULL)
    {
        q=p->next;
        if(strcmp(q->TrainNaber,trainname)==0)
        {
            printf("\n\n\n\n                                                                                                                 �ҵ����޸��г���");
            printf("\n\n");
            printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
            printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
            printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
            q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
            q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
            m=q->TStation;
            m=m->next;
            printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
            printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
            printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
	printf("\n\n                                                                                                               �������޸ĺ���г������Ϣ\n");
    strcpy(train.TrainNaber,trainname);
	printf("\n                                                                                                               ʼ��վ: ");
	scanf("%s",train.StartStation);
	printf("\n                                                                                                               �յ�վ: ");
	scanf("%s",train.ArriveStation);
	printf("\n                                                                                                               ���о���: ");
	scanf("%f",&train.Mileage);
	printf("\n                                                                                                               ͣ����Ϣ: ");
	scanf("%s",train.Mod);
	printf("\n                                                                                                               ����ʱ��: ");
	scanf("%s",train.StartTime);
	printf("\n                                                                                                               ����ʱ��: ");
	scanf("%s",train.ArriveTime);
	printf("\n                                                                                                               ͣ����վ��: ");
	scanf("%d",&train.StationNum);
	printf("\n                                                                                                               �ص�������: ");
	scanf("%d",&train.ProSet);
	printf("\n                                                                                                               һ��������: ");
	scanf("%d",&train.FirSet);
	printf("\n                                                                                                               ����������: ");
	scanf("%d",&train.SecSet);
	temp=train.StationNum;
	m = (StationData*)malloc(sizeof(StationData));
    train.TStation=m;
	while(temp--)
    {
        n = (StationData*)malloc(sizeof(StationData));
        printf("\n                                                                                                               ͣ��վ: ");
        scanf("%s",n->StaName);
        printf("\n                                                                                                               ����ʱ��: ");
        scanf("%s",n->StopTime);
        printf("\n                                                                                                               ����ʱ��: ");
        scanf("%s",n->DriveTime);
        printf("\n                                                                                                               ���: ");
        scanf("%f",&n->StaMileage);
        m->next=n;
        m=n;
    }
    m->next=NULL;
    TrainData *s=(TrainData *)malloc(sizeof(TrainData));//���½ڵ㣬����
	*s=train;
	s->next=q->next;
	p->next=s;
	free(q);
    system ("cls");
    q=s;
    i=1;
    printf("\n\n\n\n\n\n\n\n                                                                                                        ���ĺ����ϢΪ");
    printf("\n\n");
            printf("                                                                 | ���� || ʼ��վ || �յ�վ || ���о��� || ͣ����Ϣ || ����ʱ�� || ����ʱ�� || ͣ����վ�� || �ص������� || һ�������� || ���������� |\n");
            printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
            printf("                                                                 |%6s%9s %9s   %8.1f  %9s%12s  %10s%12d  %12d  %12d  %12d     |\n",
            q->TrainNaber, q->StartStation, q->ArriveStation, q->Mileage, q->Mod,
            q->StartTime,q->ArriveTime,q->StationNum,q->ProSet,q->FirSet,q->SecSet);
            m=q->TStation;
            m=m->next;
            printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
            printf("                                                                 |             ͣ��վ             ||            ����ʱ��            ||            ����ʱ��            ||            ���            |\n");
            printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
            while(m!=NULL)
            {
                printf("                                                                 |%3d%16s             %20s              %20s            %20.1f            |\n",i,m->StaName,m->StopTime,m->DriveTime,m->StaMileage);
                m=m->next;
                i++;
            }
	save_train_File(head);

}

//�˿���Ϣ����***********************************************************************************************************************************************************************

PassengerData* read_passengeer_File(void)
{
	FILE* fp;
	PassengerData* head, * p, * q;
	p = q = (PassengerData*)malloc(sizeof(PassengerData));//���ٿռ丳ָ��
	if ((fp = fopen("passenger.txt", "r")) == NULL)//�ļ�ָ�븳ֵΪNULL
	{
		printf("                                                                                                                                                                        can't open file\n");
		exit(0);
	}
	head = p;//ͷָ�븳ֵ������

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
	if (L == NULL)//ͷָ���
	{
		printf("\n                                                                                                                can't save file\n");
		return;
	}
	FILE* fp = fopen("passenger.txt", "wb");
	if (fp == NULL)//�ļ�ָ���
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
	//��β����
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
    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
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
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ------------�˿���Ϣ����----------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |         1. ���ӳ˿�            |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         2. ɾ���˿�            |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         3. �˿���Ϣ��ѯ        |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         4. �޸ĳ˿���Ϣ        |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         5. �鿴���г˿�        |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |         6. �˳�ϵͳ            |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
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
	printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                               �����������˿������Ϣ\n");
	printf("                                                                                                               ֤����: ");
	scanf("%s",pass.IDNumber);
	printf("                                                                                                               �˿�����: ");
	scanf("%s",pass.PaName);
	printf("                                                                                                               ֤������: ");
	scanf("%s",pass.IDType);
	printf("                                                                                                               ��ϵ�绰: ");
	scanf("%s",pass.PaTel);
	printf("                                                                                                               ������ϵ��: ");
	scanf("%s",pass.UrName);
	printf("                                                                                                               ��ϵ�˵绰: ");
	scanf("%s",pass.UrTel);
	PassengerData *s=(PassengerData *)malloc(sizeof(PassengerData));//���½ڵ㣬����
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
    printf("                                                                                                      ������Ҫɾ���ĳ˿�֤���ţ�");
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
        printf("                                                                                                      ���ҵ���ɾ����Ϣ��\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",p->IDNumber,p->PaName,p->IDType,p->PaTel,p->UrName,p->UrTel);
        printf("                                                                                                      ȷ���Ƿ�ɾ������Y:1 N:0��");
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
    if(p->next==NULL&&flag==0) printf("\n                                                                            ɾ����Ϣ������");
	return L;
}

void Seek_Passenger_UI(PassengerData* head)
{
    int n=3,choose;
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                -------------�˿���Ϣ��ѯ---------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |        1. �˿�������ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        2. �˿�֤���Ų�ѯ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        3. �˿͵绰��ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        4. ������ϵ�˲�ѯ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        5. �˳�ϵͳ             |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
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
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ������");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->PaName,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����س˿�\n");
        }break;

        case 2:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ֤���ţ�");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->IDNumber,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����س˿�\n");
        }break;

        case 3:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ�绰���룺");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->PaTel,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����س˿�\n");
        }break;

        case 4:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ������ϵ�ˣ�");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->UrName,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����س˿�\n");
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
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                                  ��������Ҫ�޸ĵĳ˿͵�֤���ţ� ");
    scanf("%s",name);
    system("cls");
    p=p->next;
    while(p!=NULL)
    {
        q=p->next;
        if(strcmp(q->IDNumber,name)==0)
        {
            printf("\n\n\n\n\n\n\n\n\n                                                                                                                       �ҵ����޸��г���");
            printf("\n\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
            break;
        }
        i=1;
        p=p->next;
    }
	PassengerData pass;
	printf("\n\n                                                                                                               �������޸ĺ�ĳ˿������Ϣ\n");
	printf("\n                                                                                                               ֤����: ");
	scanf("%s",pass.IDNumber);
	printf("\n                                                                                                               ����: ");
	scanf("%s",pass.PaName);
	printf("\n                                                                                                               ֤������: ");
	scanf("%s",pass.IDType);
	printf("\n                                                                                                               ��ϵ�绰: ");
	scanf("%s",pass.PaTel);
	printf("\n                                                                                                               ������ϵ��: ");
	scanf("%s",pass.UrName);
	printf("\n                                                                                                               ��ϵ�˵绰: ");
	scanf("%s",pass.UrTel);
    PassengerData *s=(PassengerData *)malloc(sizeof(PassengerData));//���½ڵ㣬����
	*s=pass;
	s->next=q->next;
	p->next=s;
	free(q);
    system ("cls");
    q=s;
    i=1;
    printf("\n\n\n\n\n\n\n\n                                                                                                                     ���ĺ����ϢΪ");
    printf("\n\n");
                    printf("                                                                 |            ֤����            ||     ����     ||    ֤������    ||      ��ϵ�绰      ||    ������ϵ��    ||      ��ϵ�˵绰      |\n");
                    printf("                                                                 |����������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("                                                                 | %23s  %15s   %15s  %20s   %15s    %20s       |\n",q->IDNumber,q->PaName,q->IDType,q->PaTel,q->UrName,q->UrTel);
	save_passenger_File(head);
	printf("\n                                                                                                                     ");
	system ("pause");
    system ("cls");
}

//������Ʊ��Ϣ����***********************************************************************************************************************************************************************
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
        //printf("��ѭ����\n");
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
    TrainSeat* s=head1;//�г���λ�����ͷ
    TrainData* t=head2;//�г������ͷ
    TicketData* k=head3;//��Ʊ�����ͷ
    StationData* h;
    SeatStation* p,* q;
    Seat* m,*n;
    int start,arrive;
    s=s->next;
    t=t->next;
    k=k->next;
    while(k!=NULL)//������Ʊ
    {
        //printf("��ѭ����\n");
        t=head2;
        t=t->next;
        while(t!=NULL)//�����г�
        {
            //printf("��ѭ����\n");
            if(strcmp(k->Train,t->TrainNaber)==0)//�ҵ����ų�Ʊ��Ӧ���г�
            {
                //printf("��if��\n");
                h=t->TStation;//ָ��ָ����������ͣ��վ����
                start=set_code(k->StartStation,h);//��ʼվת��
                arrive=set_code(k->ArriveStation,h);//�յ�վת��
                s=head1;
                s=s->next;
                //printf("%s",s->train);
                while(s!=NULL)//�����г���λ����
                {
                    //printf("��ѭ����\n");
                    if(strcmp(k->Train,s->train)==0)//�ҵ����ų�Ʊ��Ӧ���г���λ����
                    {
                        m=s->seat;//mָ���г���λ�������λ����
                        m=m->next;
                        while(k->SetNum!=m->num)
                            m=m->next;
                        if(k->SetNum==m->num)//�ҵ����ų�Ʊ��Ӧ��λ
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
	p = q = (TicketData*)malloc(sizeof(TicketData));//���ٿռ丳ָ��
	if ((fp = fopen("booking.txt", "r")) == NULL)//�ļ�ָ�븳ֵΪNULL
	{
		printf("                                                                                                                                                                        can't open file\n");
		exit(0);
	}
	head = p;//ͷָ�븳ֵ������

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
	if (L == NULL)//ͷָ���
	{
		printf("\n                                                                                                                can't save file\n");
		return;
	}
	FILE* fp = fopen("booking.txt", "wb");
	if (fp == NULL)//�ļ�ָ���
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
	//��β����
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
    printf("               |            ������            ||     �˳�����     ||  ����  ||    ʼ��վ    ||    �յ�վ    ||  ֤�����  ||            ֤����            ||    �˿�����    ||  ����ʱ��  ||  ����ʱ��  || ��λ�ȼ� || ��λ�� ||  Ʊ��  |\n");
    printf("               |������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������|\n");
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
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                ------------��Ʊ��Ϣ����----------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |          1. ��Ʊ               |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          2. ��Ʊ               |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          3. ��Ʊ��Ϣ��ѯ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          4. ��Ʊ��ѯ           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          5. �鿴���г�Ʊ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          6. ��ӡ��Ʊ           |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |          7. �˳�ϵͳ           |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
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
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                               ������Ҫɾ���Ķ����ţ�");
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
        printf("                                                                                                               ���ҵ���ɾ����Ϣ��\n\n");
        printf("               |            ������            ||     �˳�����     ||  ����  ||    ʼ��վ    ||    �յ�վ    ||  ֤�����  ||            ֤����            ||    �˿�����    ||  ����ʱ��  ||  ����ʱ��  || ��λ�ȼ� || ��λ�� ||  Ʊ��  |\n");
        printf("               |������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������|\n");
        printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
        year=(q->Date[0]-'0')*(1000)+(q->Date[1]-'0')*(100)+(q->Date[2]-'0')*(10)+(q->Date[3]-'0');
        month=(q->Date[4]-'0')*(10)+(q->Date[5]-'0');
        day=(q->Date[6]-'0')*(10)+(q->Date[7]-'0');
        hour=(q->StartTime[0]-'0')*(10)+(q->StartTime[2]-'0');
        miniti=(q->StartTime[4]-'0')*(10)+(q->StartTime[5]-'0');
        if(year==ntime.year&&month==ntime.month&&day==ntime.day&&hour>=ntime.hour+2)
            printf("\n\n\n                                                                                                     ��ʾ���࿪��������Сʱ����Ʊ���۳�%.2f�����ѣ�",(0.05)*q->price);
        printf("\n\n                                                                                                               ȷ���Ƿ�ɾ������Y:1 N:0��");
        scanf("%d",&n);
        if(n==1)
        {
            if(p==head2->next)
                head2=q->next;
            else
                p->next=q->next;
                printf("\n\n                                                                                                                     ��Ʊ�ɹ���");
        }
        save_ticket_File(head2);
        flag=1;
    }
    if(q->next==NULL&&flag==0) printf("\n                                                                                                               ɾ����Ϣ������\n");
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
        printf("\n                                                                    ����Ʊ\n");
        return 0;
    }
    printf("\n                                                                                                                ��ѡ�񳵴Σ� ");
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
    printf("                                                                                                                ������˿�֤���ţ� ");
    scanf("%s",np.IDNumber);
    system("cls");
    while(pd!=NULL)
    {
        if(strcmp(pd->IDNumber,np.IDNumber)==0)
        {
            strcpy(np.IDType,pd->IDType);
            strcpy(np.Name,pd->PaName);
            strcpy(np.SetLevel,"������");
            //printf("��ѭ����");
            break;
        }
        pd=pd->next;
    }
    if(pd==NULL)
    {
        printf("����³˿ͣ�");
        Insert_Passenger(head4);
        pd=head4;
        pd=pd->next;
        while(pd!=NULL)
        {
            if(strcmp(pd->IDNumber,np.IDNumber)==0)
            {
                strcpy(np.IDType,pd->IDType);
                strcpy(np.Name,pd->PaName);
                strcpy(np.SetLevel,"������");
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
    printf("\n\n\n\n\n\n\n                                                                                                                �����붩���ţ� ");
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
        printf("����ض���");
}

void print_ticket(TicketData* head)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                ��������������������������������������������������������������������������������������������\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |         %10s վ                     %s                   %10s վ            |\n",head->StartStation,head->Train,head->ArriveStation);
    printf("                                                                                |                                        -------->                                         |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |   %c%c%c%c �� %c%c �� %c%c �� %s ��                                      %2d ����              |\n",head->Date[0],head->Date[1],head->Date[2],head->Date[3],head->Date[4],head->Date[5],head->Date[6],head->Date[7],head->StartTime,head->SetNum);
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |         %7.2f Ԫ                                                   ������              |\n",head->price);
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |     %20s %10s                                                      |\n",head->IDNumber,head->Name);
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                |                                  �й���·ף����;���                                    |\n");
    printf("                                                                                |                                                                                          |\n");
    printf("                                                                                ��������������������������������������������������������������������������������������������\n");
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
    printf("\n\n\n\n\n\n\n                                                                                                                ������˳����ڣ� ");
    scanf("%s",date);
    printf("                                                                                                                ��������ʼվ�� ");
    scanf("%s",start);
    printf("                                                                                                                �������յ�վ�� ");
    scanf("%s",arrive);
    p=train;
    p=p->next;
    Bhead=n=m=(Booking*)malloc(sizeof(Booking));
    year=(date[0]-'0')*(1000)+(date[1]-'0')*(100)+(date[2]-'0')*(10)+(date[3]-'0');
    month=(date[4]-'0')*(10)+(date[5]-'0');
    day=(date[6]-'0')*(10)+(date[7]-'0');
    if(year!=ntime.year)
    {
        printf("\n                                                                                                                ֻ��Ԥ���������ڵĳ�Ʊ");
        return 0;
    }
    else if(month>(ntime.month+2))
    {
        printf("\n                                                                                                                ֻ��Ԥ���������ڵĳ�Ʊ");
        return 0;
    }
    else if(month==(ntime.month+2))
    {
        if(day>ntime.day)
        {
            printf("\n                                                                                                                ֻ��Ԥ���������ڵĳ�Ʊ");
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
            if(strcmp(start,q->StaName)==0)//�ҵ���ͬ����ʼվ
            {
                startcode=q->stacode;
                q=q->next;
                while(q!=NULL)//ԭ�ؼ�������ͣ��վ����
                {
                    //printf("��ѭ����");
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
                    //printf("��if��");
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
            //printf("��ѭ����");
            q=q->next;
        }
        //printf("��ѭ����");
        p=p->next;
    }
    //printf("��ѭ����");
    if(tag==0)
    {
        printf("                                                                                                                �޿ɴ��г�");
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
            //printf("��tsѭ����");
            if(strcmp(p->trainnum,m->train)==0)//�ҵ���������Ӧ����λ״̬��
            {
                //printf("%s\n",p->trainnum);
                n=m->seat;
                n=n->next;
                while(n!=NULL)//������λ
                {
                   // printf("��seatѭ����");
                    t=n->satation;
                    t=t->next;
                    while(t!=NULL)//������λ��״̬
                    {
                       // printf("��ssѭ����");
                        //printf("%s %s %d %d ",date,t->date,t->arrivecode,p->startcode);
                        if(strcmp(date,t->date)==0 && (t->arrivecode > p->startcode)  )break;//�ж����������״̬�ĵ��������ڳ˿͵���ʼ��������ͬһ�죬�����������ж���λ��������
                        t=t->next;
                    }
                    //printf("��ssѭ����");
                    if(t==NULL)//����������״̬
                    {
                        p->seatnum[count++]=n->num;//�������λ�ż���booking����Ŀɶ���λ������
                        //printf("%d\n", p->seatnum[count]);
                    }
                    n=n->next;
                }
                //printf("��seatѭ����");
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
        printf("����Ʊ");
        return 0;
    }
    printf("                                                                                                                |  ����  ||  ʣ��Ʊ��  |\n");
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
    printf("\n\n\n\n\n\n\n\n\n\n                                                                                                                -------------��Ʊ��Ϣ��ѯ---------\n");
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                |        1. �˿�������ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        2. �˿�֤���Ų�ѯ       |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        3. �˳����ڲ�ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        4. ���˳��β�ѯ         |\n");
    printf("                                                                                                                |                                |\n");
    printf("                                                                                                                |        5. �˳�ϵͳ             |\n");
    printf("                                                                                                                |                                |\n");
    n=3;
    while(n)
    {
    printf("                                                                                                                |                                |\n");
    n--;
    }
    printf("                                                                                                                ----------------------------------\n");
    printf("                                                                                                                             ��ѡ��: ");
    scanf("%d",&choose);//�û�ѡ����
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
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ������");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->Name,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            ������            ||     �˳�����     ||  ����  ||    ʼ��վ    ||    �յ�վ    ||  ֤�����  ||            ֤����            ||    �˿�����    ||  ����ʱ��  ||  ����ʱ��  || ��λ�ȼ� || ��λ�� ||  Ʊ��  |\n");
                    printf("               |������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����ض�Ʊ\n");
        }break;

        case 2:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        �������ѯ֤���ţ�");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->IDNumber,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            ������            ||     �˳�����     ||  ����  ||    ʼ��վ    ||    �յ�վ    ||  ֤�����  ||            ֤����            ||    �˿�����    ||  ����ʱ��  ||  ����ʱ��  || ��λ�ȼ� || ��λ�� ||  Ʊ��  |\n");
                    printf("               |������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����ض�Ʊ\n");
        }break;

        case 3:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        ������˳����ڣ�");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->Date,input)==0)//ƥ�䵽��ѯĿ��
                {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            ������            ||     �˳�����     ||  ����  ||    ʼ��վ    ||    �յ�վ    ||  ֤�����  ||            ֤����            ||    �˿�����    ||  ����ʱ��  ||  ����ʱ��  || ��λ�ȼ� || ��λ�� ||  Ʊ��  |\n");
                    printf("               |������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����ض�Ʊ\n");
        }break;
        case 4:
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                        ���������˳��Σ�");
            scanf("%s",input);
            system("cls");
            while(q!=NULL)
            {
                if(strcmp(q->Train,input)==0)//ƥ�䵽��ѯĿ��
                {
                    count++;
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("               |            ������            ||     �˳�����     ||  ����  ||    ʼ��վ    ||    �յ�վ    ||  ֤�����  ||            ֤����            ||    �˿�����    ||  ����ʱ��  ||  ����ʱ��  || ��λ�ȼ� || ��λ�� ||  Ʊ��  |\n");
                    printf("               |������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������|\n");
                    printf("               %25s         %12s  %10s   %12s    %12s     %10s          %20s       %10s       %10s    %10s   %10s %8d   %9.2f\n",q->TicketNum,q->Date,q->Train,q->StartStation,q->ArriveStation,q->IDType,q->IDNumber,q->Name,q->StartTime,q->ArriveTime,q->SetLevel,q->SetNum,q->price);
                }
                q=q->next;
            }
            if(count==0)
            printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                               ����ض�Ʊ\n");
        }break;
        case 5:goodbye();break;
        default:printf("\n\n\n\n\n\n\n\n\n\n\n                                                                                                                                error");break;
    }

}
