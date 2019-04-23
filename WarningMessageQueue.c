#include "WaringMessageQueue.h"

/**��̬��������**/
//���ظ���BSM��Ϣ������PriorityQueue����ȥ��


/****���ȼ�������ز��������ѣ�****/
WaringPriorityQueue WarningPQInitialize(int capacity);					//��ʼ�� ���ȼ����У��ѣ�
int WarningPQDestroy(WaringPriorityQueue WPQ);						//���� ���ȼ����У��ѣ�
int WarningPQMakeEmpty(WaringPriorityQueue WPQ);						//��� ���ȼ����У��ѣ�
int WarningPQInsertBSM(WaringPriorityQueue WPQ, tWaringMessage WM);			//��ӣ����복��BSM��Ϣ
double WarningPQComputeKey(tWaringMessage WM);								//����BSM��Ϣ�����ȼ���keyԽС�����ȼ�Խ�ߣ�
int WarningPQDeleteMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM); 	//���ӣ�ɾ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
int WarningPQQueryMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM);		//��ѯ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
//��������С�ѣ�
int WarningPQReSort(WaringPriorityQueue WPQ);							//����HV��BSM��Ϣ����Ҫ�����ȼ����н���������
int IsWarningPQEmpty(WaringPriorityQueue WPQ); 						//�ж����ȼ������Ƿ�Ϊ��
int IsWarningPQFull(WaringPriorityQueue WPQ);							//�ж����ȼ������Ƿ�����


