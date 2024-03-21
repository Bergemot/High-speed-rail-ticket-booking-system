#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

/*************************UI**************************/
//主页面
int system_UI(void);
//train功能页面
void train_UI(TrainData* head);
//train查询条件选择页面
void Seek_Train_UI(TrainData* head);
//passenger功能页面
void passenger_UI(PassengerData* head);
//pasenger查询条件选择页面
void Seek_Passenger_UI(PassengerData* head);
//booking功能页面
void booking_UI(TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4);
//ticket查询条件选择页面
void Seek_ticket_UI(TicketData* head);

/************************TRAIN************************/
//从train.txt里读取列车信息
TrainData* read_train_File();
//将train链表保存在train.txt里
void save_train_File(TrainData* L);
//打印train链表所有内容（包含station）
void print_train_File(TrainData* head);
//打印train链表内容（不包含station）
void print_train(TrainData* head);
//train的switch case
void train_choose(int choose,TrainData* head);
//插入一辆train
TrainData* Insert_Train(TrainData* head);
//停开一辆train
TrainData* Stop_Train(TrainData* head);
//按条件查询train
TrainData* Seek_Train(int choose,TrainData* head);
//修改train信息
TrainData* Revise_Train(TrainData* head);

/**********************PASSENGER**********************/
//从passenger.txt读取乘客信息
PassengerData* read_passengeer_File(void);
//将passenger链表保存在passenger.txt里
void save_passenger_File(PassengerData* L);
//打印passenger链表里的内容
void print_passenger(PassengerData* head);
//passenger的switch case
void passenger_choose(int choose,PassengerData* head);
//新增乘客
PassengerData* Insert_Passenger(PassengerData* head);
//删除游客
PassengerData* Delete_Passenger(PassengerData* L);
//按条件查询游客
PassengerData* Seek_Passenger(int choose,PassengerData* head);
//修改游客信息
PassengerData* Revise_passenger(PassengerData* head);

/**********************BOOKING************************/
//创建seat链表
TrainSeat* crate_seat(TrainData* train,TicketData* head3);
//向seat链表添加座位状态
TrainSeat* set_seat(TrainSeat* head1,TrainData* head2,TicketData* head3);
//给station赋编码
int set_code(char station[],StationData* head);
//打印seat链表
void print_seat_list(TrainSeat* head);
//从booking.txt里读取订票信息
TicketData* read_ticket_File(void);
//将booking链表保存在booking.txt里
void save_ticket_File(TicketData* L);
//打印booking链表里的所有内容
void print_all_ticket(TicketData* head);
//booking的switch case
void booking_choose(int choose,TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4);
//按条件查询已有订票
void Seek_ticket(int choose,TicketData* head);
//查询余票
Booking* seek_remain_ticket(TrainSeat* head,TrainData* train);
//判断是否有票
Booking* judge_ticket(char date[10],Booking* bhead,TrainSeat* thead);
//输出余票
void print_bhead(Booking* head);
//打印一张车票
void print_one_ticket(TicketData* head2);
//打印车票
void print_ticket(TicketData* head);
//删除订单
void refund_ticket(TicketData* head2);
//订票
void book_ticket(TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4);

/************************OTHER************************/
//bye
void goodbye();
//返回当前系统时间
nowtime Get_Sys_Time();

#endif // FUNCTION_H_INCLUDED
