#ifndef STDLIB_H
#include <stdlib.h>
#endif
#define SIZE 1000

enum state {
  RUNNING,
  RUNNABLE,
  TERMINATED,
  IO,
  EMBRYO
};


struct proc {
  int pid;
  int arrTime;
  int burstTime;
  int IO1;
  int IO2;
  enum state currState;
  int initStartTime;
  int finalEndTime;
};

struct proc* Rqueue = NULL;
int *tempStoreBT = NULL;
int *tempStoreIO1 = NULL;
int *tempStoreIO2 = NULL;

struct readyQueue {
  int frontIdx;
  int rearIdx;
  int arr[SIZE];
};

struct readyQueue RQ;

void initRQ() {
  RQ.frontIdx = RQ.rearIdx = -1;
}

int isEmptyRQ() {
  if (RQ.frontIdx == -1 && RQ.rearIdx == -1)
    return 1;
  return 0;
}

/**
 * @return status if 1 successful otherwise failure
 */
int pushRQ(int pid) {
  if (isEmptyRQ()) {
    RQ.frontIdx = 0;
    RQ.arr[(RQ.rearIdx + 1) % SIZE] = pid;
    RQ.rearIdx = (RQ.rearIdx + 1) % SIZE;
    return 1;
  }
  if ((RQ.rearIdx + 1)%SIZE == RQ.frontIdx)
    return 0;
  else {
    RQ.arr[(RQ.rearIdx + 1) % SIZE] = pid;
    RQ.rearIdx = (RQ.rearIdx + 1) % SIZE;
    return 1;
  }
}

/**
 * @return will return process PID to be worked on
 */
int popRQ() {
  if (isEmptyRQ()) {
    return -999;
  }
  int pid = RQ.arr[RQ.frontIdx];
  if (RQ.frontIdx == RQ.rearIdx) {
    // only one element
    RQ.frontIdx = RQ.rearIdx = -1;
  } else {
    RQ.frontIdx = (RQ.frontIdx + 1) % SIZE;
  }
  return pid;
}


//------------------------------
struct readyQueue WQ;

void initWQ() {
  WQ.frontIdx = WQ.rearIdx = -1;
}

int isEmptyWQ() {
  if (WQ.frontIdx == -1 && WQ.rearIdx == -1)
    return 1;
  return 0;
}

/**
 * @return status if 1 successful otherwise failure
 */
int pushWQ(int pid) {
  if (Rqueue[pid].IO1 == tempStoreIO1[pid]) {
    Rqueue[pid].initStartTime = CLK_CYCLE;
  }
  if (isEmptyWQ())
  {
    WQ.frontIdx = 0;
    WQ.arr[(WQ.rearIdx + 1) % SIZE] = pid;
    WQ.rearIdx = (WQ.rearIdx + 1) % SIZE;
    return 1;
  }
  if ((WQ.rearIdx + 1)%SIZE == WQ.frontIdx)
    return 0;
  else {
    WQ.arr[(WQ.rearIdx + 1) % SIZE] = pid;
    WQ.rearIdx = (WQ.rearIdx + 1) % SIZE;
    return 1;
  }
}

/**
 * @return will return process PID to be worked on
 */
int popWQ() {
  if (isEmptyWQ()) {
    return -999;
  }
  int pid = WQ.arr[WQ.frontIdx];
  if (WQ.frontIdx == WQ.rearIdx) {
    // only one element
    WQ.frontIdx = WQ.rearIdx = -1;
  } else {
    WQ.frontIdx = (WQ.frontIdx + 1) % SIZE;
  }
  return pid;
}

int isDone(int i) {
  return (Rqueue[i].IO1 == 0 || Rqueue[i].IO2 == 0) ? 1 : 0;
}

void removeTheDoneProc(int idx) {

  if (idx == WQ.frontIdx) {
    // remvoe front
    popWQ();
    return;
  }
  // shifting
  int prevI = 0;
  for (int i = idx; i != WQ.rearIdx; i = (i + 1) % SIZE)
  {
    WQ.arr[i] = WQ.arr[(i+1) % SIZE];
    prevI = i;
  }
  WQ.rearIdx = prevI;
}

void refreshWQ() {
  if (isEmptyWQ())
    return;
  int i = WQ.frontIdx;
  while (i != (WQ.rearIdx + 1) % SIZE) {
    if (Rqueue[WQ.arr[i]].IO2 != 0 && Rqueue[WQ.arr[i]].IO1 == 0 && Rqueue[WQ.arr[i]].burstTime == 0) {
      Rqueue[WQ.arr[i]].IO2-- ;
      if (Rqueue[WQ.arr[i]].IO2 == 0) {
        Rqueue[WQ.arr[i]].currState = TERMINATED;
        Rqueue[WQ.arr[i]].finalEndTime = CLK_CYCLE;
        Rqueue[WQ.arr[i]].currState = TERMINATED;
        printf("COMPLETED!!\tpid: %d\tCLK: %ld\n", Rqueue[WQ.arr[i]].pid, CLK_CYCLE);
        removeTheDoneProc(i);
        continue;
      }
    }
    else if (Rqueue[WQ.arr[i]].IO1 != 0) {
      Rqueue[WQ.arr[i]].IO1--;
      if (Rqueue[WQ.arr[i]].IO1 == 0) {
        Rqueue[WQ.arr[i]].currState = RUNNABLE;
        // push
        pushRQ(WQ.arr[i]);
        removeTheDoneProc(i);
        continue;
      }
    }


    i = (i + 1) % SIZE;
  }
}