#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

/*************************UI**************************/
//��ҳ��
int system_UI(void);
//train����ҳ��
void train_UI(TrainData* head);
//train��ѯ����ѡ��ҳ��
void Seek_Train_UI(TrainData* head);
//passenger����ҳ��
void passenger_UI(PassengerData* head);
//pasenger��ѯ����ѡ��ҳ��
void Seek_Passenger_UI(PassengerData* head);
//booking����ҳ��
void booking_UI(TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4);
//ticket��ѯ����ѡ��ҳ��
void Seek_ticket_UI(TicketData* head);

/************************TRAIN************************/
//��train.txt���ȡ�г���Ϣ
TrainData* read_train_File();
//��train��������train.txt��
void save_train_File(TrainData* L);
//��ӡtrain�����������ݣ�����station��
void print_train_File(TrainData* head);
//��ӡtrain�������ݣ�������station��
void print_train(TrainData* head);
//train��switch case
void train_choose(int choose,TrainData* head);
//����һ��train
TrainData* Insert_Train(TrainData* head);
//ͣ��һ��train
TrainData* Stop_Train(TrainData* head);
//��������ѯtrain
TrainData* Seek_Train(int choose,TrainData* head);
//�޸�train��Ϣ
TrainData* Revise_Train(TrainData* head);

/**********************PASSENGER**********************/
//��passenger.txt��ȡ�˿���Ϣ
PassengerData* read_passengeer_File(void);
//��passenger��������passenger.txt��
void save_passenger_File(PassengerData* L);
//��ӡpassenger�����������
void print_passenger(PassengerData* head);
//passenger��switch case
void passenger_choose(int choose,PassengerData* head);
//�����˿�
PassengerData* Insert_Passenger(PassengerData* head);
//ɾ���ο�
PassengerData* Delete_Passenger(PassengerData* L);
//��������ѯ�ο�
PassengerData* Seek_Passenger(int choose,PassengerData* head);
//�޸��ο���Ϣ
PassengerData* Revise_passenger(PassengerData* head);

/**********************BOOKING************************/
//����seat����
TrainSeat* crate_seat(TrainData* train,TicketData* head3);
//��seat���������λ״̬
TrainSeat* set_seat(TrainSeat* head1,TrainData* head2,TicketData* head3);
//��station������
int set_code(char station[],StationData* head);
//��ӡseat����
void print_seat_list(TrainSeat* head);
//��booking.txt���ȡ��Ʊ��Ϣ
TicketData* read_ticket_File(void);
//��booking��������booking.txt��
void save_ticket_File(TicketData* L);
//��ӡbooking���������������
void print_all_ticket(TicketData* head);
//booking��switch case
void booking_choose(int choose,TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4);
//��������ѯ���ж�Ʊ
void Seek_ticket(int choose,TicketData* head);
//��ѯ��Ʊ
Booking* seek_remain_ticket(TrainSeat* head,TrainData* train);
//�ж��Ƿ���Ʊ
Booking* judge_ticket(char date[10],Booking* bhead,TrainSeat* thead);
//�����Ʊ
void print_bhead(Booking* head);
//��ӡһ�ų�Ʊ
void print_one_ticket(TicketData* head2);
//��ӡ��Ʊ
void print_ticket(TicketData* head);
//ɾ������
void refund_ticket(TicketData* head2);
//��Ʊ
void book_ticket(TrainData* head1,TicketData* head2,TrainSeat* head3,PassengerData* head4);

/************************OTHER************************/
//bye
void goodbye();
//���ص�ǰϵͳʱ��
nowtime Get_Sys_Time();

#endif // FUNCTION_H_INCLUDED
