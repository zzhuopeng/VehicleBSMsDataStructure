#ifndef WarningMessageQueue_H_
#define WarningMessageQueue_H_

/**
 * 说明：预警消息优先级队列（Waring Message Priority Queue）存储结构体
 		通过最大堆进行存储，WarningMessages[0]不包含数据。
 		排序规则：预警场景+预警等级
 * 注意：①PriorityQueue的容量尽量不能经常被填满，否则需要经常PQDeleteMaxBSM()， 比较耗时
   待考虑：
 		 ②重复的BSM消息，会在PriorityQueue里面去除（这部分需要考虑一下）
 */


/****宏定义****/
#define WarningPQ_MIN_CAPACITY 	8	//预警消息优先级队列（堆容量）最小保留个数
#define WarningPQ_MAX_CAPACITY 	64	//预警消息优先级队列（堆容量）最大保留个数
#define WarningPQ_EXPENDFACTOR	0.5 //扩容因子，扩展的大小=原大小*扩容因子


/****结构体定义****/
typedef struct MaxHeapStruct* WaringPriorityQueue;

//堆结构体（基于数组）
typedef struct MaxHeapStruct {
	int Capacity; 	                //堆容量(自定义)
	int Size; 		                //当前堆大小
	tWaringMessage* WarningMessages;//预警消息数组
} tMaxHeapStruct;

//预警消息结构体
typedef struct WaringMessage {
	int Scene; 	        //预警场景
	int Level; 		    //预警等级
	double RVLatitude;  //RV纬度
	double RVLongitude; //RV经度
} tWaringMessage;


/****优先级队列相关操作（最大堆）****/
WaringPriorityQueue WarningPQInitialize(int capacity);					    //初始化 优先级队列（堆）
int WarningPQDestroy(WaringPriorityQueue WPQ);						        //销毁 优先级队列（堆）
int WarningPQMakeEmpty(WaringPriorityQueue WPQ);						    //清空 优先级队列（堆）
int WarningPQInsertBSM(WaringPriorityQueue WPQ, tWaringMessage WM);			//入队：插入车辆BSM消息
double WarningPQComputeKey(tWaringMessage WM);								//计算BSM消息的优先级（key越小，优先级越高）
int WarningPQDeleteMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM); 	//出队：删除优先级最高（关键字最小）BSM消息
int WarningPQQueryMinBSM(WaringPriorityQueue WPQ, tWaringMessage* topWM);   //查询：优先级最高（关键字最小）BSM消息
//重排序（最小堆）
int WarningPQReSort(WaringPriorityQueue WPQ);							    //更新HV的BSM消息后，需要对优先级队列进行重排序
int IsWarningPQEmpty(WaringPriorityQueue WPQ); 						        //判断优先级队列是否为空
int IsWarningPQFull(WaringPriorityQueue WPQ);							    //判断优先级队列是否已满



#endif
