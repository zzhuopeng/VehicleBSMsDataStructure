#ifndef WarningMessageQueue_H_
#define WarningMessageQueue_H_

/**
 * ˵����Ԥ����Ϣ���ȼ����У�Waring Message Priority Queue���洢�ṹ��
 		ͨ�����ѽ��д洢��WarningMessages[0]���������ݡ�
 		�������Ԥ������+Ԥ���ȼ�
 * ע�⣺��PriorityQueue�������������ܾ�����������������Ҫ����PQDeleteMaxBSM()�� �ȽϺ�ʱ
   �����ǣ�
 		 ���ظ���BSM��Ϣ������PriorityQueue����ȥ�����ⲿ����Ҫ����һ�£�
 */


/****�궨��****/
#define WarningPQ_MIN_CAPACITY 	8	//Ԥ����Ϣ���ȼ����У�����������С��������
#define WarningPQ_MAX_CAPACITY 	64	//Ԥ����Ϣ���ȼ����У������������������
#define WarningPQ_EXPENDFACTOR	0.5 //�������ӣ���չ�Ĵ�С=ԭ��С*��������


/****�ṹ�嶨��****/
typedef struct MaxHeapStruct* WaringPriorityQueue;

//�ѽṹ�壨�������飩
typedef struct MaxHeapStruct {
	int Capacity; 	                //������(�Զ���)
	int Size; 		                //��ǰ�Ѵ�С
	tWaringMessage* WarningMessages;//Ԥ����Ϣ����
} tMaxHeapStruct;

//Ԥ����Ϣ�ṹ��
typedef struct WaringMessage {
	int Scene; 	        //Ԥ������
	int Level; 		    //Ԥ���ȼ�
	double RVLatitude;  //RVγ��
	double RVLongitude; //RV����
} tWaringMessage;


/****���ȼ�������ز��������ѣ�****/
WaringPriorityQueue WarningPQInitialize(int capacity);					    //��ʼ�� ���ȼ����У��ѣ�
int WarningPQDestroy(WaringPriorityQueue WPQ);						        //���� ���ȼ����У��ѣ�
int WarningPQMakeEmpty(WaringPriorityQueue WPQ);						    //��� ���ȼ����У��ѣ�
int WarningPQInsertBSM(WaringPriorityQueue WPQ, tWaringMessage WM);			//��ӣ����복��BSM��Ϣ
double WarningPQComputeKey(tWaringMessage WM);								//����BSM��Ϣ�����ȼ���keyԽС�����ȼ�Խ�ߣ�
int WarningPQDeleteMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM); 	//���ӣ�ɾ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
int WarningPQQueryMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM);   //��ѯ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
//��������С�ѣ�
int WarningPQReSort(WaringPriorityQueue WPQ);							    //����HV��BSM��Ϣ����Ҫ�����ȼ����н���������
int IsWarningPQEmpty(WaringPriorityQueue WPQ); 						        //�ж����ȼ������Ƿ�Ϊ��
int IsWarningPQFull(WaringPriorityQueue WPQ);							    //�ж����ȼ������Ƿ�����



#endif
