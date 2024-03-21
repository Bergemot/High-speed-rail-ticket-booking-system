#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

//停靠车站结构体
typedef struct station
{
	char StaName[10]; //车站名
	int stacode;//车站编号
	char StopTime[10]; //停车时间
	char DriveTime[10]; //开车时间
	float StaMileage; //里程
	struct station* next;  //指针
}StationData;

//列车结构体
typedef struct train
{
	char TrainNaber[10]; //车次
	char StartStation[10]; //始发站
	char ArriveStation[10]; //终点站
	float Mileage; //里程
	char Mod[5]; //运行情况
	char StartTime[10]; //发车时间
	char ArriveTime[10]; //到站时间
	int StationNum; //停靠站数
	int ProSet; //特等座个数
	int FirSet; //一等座个数
	int SecSet; // 二等座个数
	StationData* TStation; //停靠车站
	struct train* next; //指针
}TrainData;

//乘客结构体
typedef struct passenger
{
	char IDNumber[20]; //证件号
	char PaName[10]; //姓名
	char IDType[10]; //证件类型
	char PaTel[20]; //乘客电话
	char UrName[10]; //紧急联系人
	char UrTel[20]; //紧急电话
	struct passenger* next;//指针
}PassengerData;

//车票结构体
typedef struct ticket
{
	char TicketNum[50]; //订单号
	char Date[10]; // 乘车日期
	char Train[10]; //车次
	char StartStation[10]; //始发站
	char ArriveStation[10]; //终到站
	char IDType[10]; //证件类别
	char IDNumber[20]; //证件号
	char Name[10]; //乘客姓名
	char StartTime[10]; //开车时间
	char ArriveTime[10]; //到达时间
	char SetLevel[10]; //座位等级
	int SetNum; // 座位号
	float price; //票价
	struct ticket* next;
}TicketData;

//座位车站结构体
typedef struct SeatStation
{
    int startcode;//该座位乘客的起始站int编码
    int arrivecode;//该座位乘客的到达站int编码
    char date[10];//该座位乘客的乘车日期
    struct SeatStation* next;//指针

}SeatStation;

//座位结构体
typedef struct Seat
{
    int num;//座位号
    SeatStation* satation;//该座位乘客的起始到达站链表
    struct Seat* next;//指针
}Seat;

//列车座位结构体
typedef struct TrainSeat
{
    char train[20];//列车车次
    Seat* seat;//列车座位的链表
    struct TrainSeat* next;//指针
}TrainSeat;

//订票结构体
typedef struct booking
{
    char trainnum[20];//可以定的车次
    int startcode;//该列车下的起始站编码
    int arrivecode;//该列车下的终点站编码
    int seatnum[100];//该车次可以定的座位号
    int seat;//该车次可以定的座位数
    char trainname[20];//该列车的车次名称
    char startname[20];//起始站
    char arrivename[20];//终点站
    char date[20];//乘车日期
    struct booking* next;//指针
}Booking;

//定义日期结构体
typedef struct date
{
    int year;
    int month;
    int day;
    int hour;
    int minit;
}nowtime;

#endif // STRUCT_H_INCLUDED
