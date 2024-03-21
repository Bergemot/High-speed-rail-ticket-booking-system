#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

//ͣ����վ�ṹ��
typedef struct station
{
	char StaName[10]; //��վ��
	int stacode;//��վ���
	char StopTime[10]; //ͣ��ʱ��
	char DriveTime[10]; //����ʱ��
	float StaMileage; //���
	struct station* next;  //ָ��
}StationData;

//�г��ṹ��
typedef struct train
{
	char TrainNaber[10]; //����
	char StartStation[10]; //ʼ��վ
	char ArriveStation[10]; //�յ�վ
	float Mileage; //���
	char Mod[5]; //�������
	char StartTime[10]; //����ʱ��
	char ArriveTime[10]; //��վʱ��
	int StationNum; //ͣ��վ��
	int ProSet; //�ص�������
	int FirSet; //һ��������
	int SecSet; // ����������
	StationData* TStation; //ͣ����վ
	struct train* next; //ָ��
}TrainData;

//�˿ͽṹ��
typedef struct passenger
{
	char IDNumber[20]; //֤����
	char PaName[10]; //����
	char IDType[10]; //֤������
	char PaTel[20]; //�˿͵绰
	char UrName[10]; //������ϵ��
	char UrTel[20]; //�����绰
	struct passenger* next;//ָ��
}PassengerData;

//��Ʊ�ṹ��
typedef struct ticket
{
	char TicketNum[50]; //������
	char Date[10]; // �˳�����
	char Train[10]; //����
	char StartStation[10]; //ʼ��վ
	char ArriveStation[10]; //�յ�վ
	char IDType[10]; //֤�����
	char IDNumber[20]; //֤����
	char Name[10]; //�˿�����
	char StartTime[10]; //����ʱ��
	char ArriveTime[10]; //����ʱ��
	char SetLevel[10]; //��λ�ȼ�
	int SetNum; // ��λ��
	float price; //Ʊ��
	struct ticket* next;
}TicketData;

//��λ��վ�ṹ��
typedef struct SeatStation
{
    int startcode;//����λ�˿͵���ʼվint����
    int arrivecode;//����λ�˿͵ĵ���վint����
    char date[10];//����λ�˿͵ĳ˳�����
    struct SeatStation* next;//ָ��

}SeatStation;

//��λ�ṹ��
typedef struct Seat
{
    int num;//��λ��
    SeatStation* satation;//����λ�˿͵���ʼ����վ����
    struct Seat* next;//ָ��
}Seat;

//�г���λ�ṹ��
typedef struct TrainSeat
{
    char train[20];//�г�����
    Seat* seat;//�г���λ������
    struct TrainSeat* next;//ָ��
}TrainSeat;

//��Ʊ�ṹ��
typedef struct booking
{
    char trainnum[20];//���Զ��ĳ���
    int startcode;//���г��µ���ʼվ����
    int arrivecode;//���г��µ��յ�վ����
    int seatnum[100];//�ó��ο��Զ�����λ��
    int seat;//�ó��ο��Զ�����λ��
    char trainname[20];//���г��ĳ�������
    char startname[20];//��ʼվ
    char arrivename[20];//�յ�վ
    char date[20];//�˳�����
    struct booking* next;//ָ��
}Booking;

//�������ڽṹ��
typedef struct date
{
    int year;
    int month;
    int day;
    int hour;
    int minit;
}nowtime;

#endif // STRUCT_H_INCLUDED
