#include "BSM.h"
#include "VehicleHistoryDatas.h"
#include "MultiVehicleHistoryDatas.h"
#include "VehiclePendingDatas.h"

/**全局变量**/
PriorityQueue pV2XRxPQ;            //待处理V2X消息


/****函数声明****/


int main(void)
{
    int i, j, ret;

    //初始化优先级队列
    pV2XRxPQ = PQInitialize(PQ_MAX_CAPACITY);
    if(NULL == pV2XRxPQ) {
        printf("[Debug]:PQInitialize() failed\n");
        goto Error;
    }

    //初始化Msg
    tBSM *Msg = (tBSM *)calloc(1,sizeof(tBSM));
    if(NULL == Msg) {
        printf("[Debug]: calloc for Msg failed\n");
        goto Error;
    }

    while(1) {
        //插入
        for(i=1; i<=10; i++) {
            Msg->id = i;
            Msg->vehicleID = i;
            Msg->latitude = 29.5385722917+(double)i;
            Msg->longitude = 106.6032197583+(double)i;
            Msg->elevation = rand()%100/10;
            Msg->speed = rand()%100/10;
            Msg->heading = (float) 340+i;
            Msg->vehicleClass = (long) i;

            ret = PQInsertBSM(pV2XRxPQ, *Msg);
            if(0 == ret) {
                printf("[Debug]: PQInsertBSM() failed\n");
            } else {
                printf("[Debug]: PQInsertBSM() success\n");
            }

            for(j=0; j<100000000; j++) {
                ;
            }
        }
        //取出
        for(i=1; i<10; i++) {
            ret = PQDeleteMinBSM(pV2XRxPQ, Msg);
            if(0 == ret) {
                printf("[Debug]: PQInsertBSM() failed\n");
            } else {
                printf("[Debug]: PQInsertBSM() success\n");
                printf("id=%d vehicleID=%d latitude=%f longitude=%f elevation=%f speed=%f heading=%f vehicleClass=%ld. \n",
                        Msg->id, Msg->vehicleID, Msg->latitude, Msg->longitude, Msg->elevation, Msg->speed, Msg->heading, Msg->vehicleClass);
            }

            for(j=0; j<1000000000; j++) {
                ;
            }
        }
    }
Error:
    //销毁V2X消息 优先级队列
    PQDestroy(pV2XRxPQ);
    free(Msg);
}
