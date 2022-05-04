#include <stdbool.h>

#ifndef STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#endif

#include "timer.h"
#include "procRR.h"
static int Qt = 5; // 3 Qt

int NoOfProcesses;

void enterData() {
  printf("Enter the PID, BurstTime for each proc\n");
  int id, bt;
  for (int i = 0; i < NoOfProcesses; i++)
  {
    scanf("%d %d", &id, &bt);
    Rqueue[i].arrTime = 0;
    Rqueue[i].currState = EMBRYO;
    Rqueue[i].IO1 = 0.2 * bt;
    Rqueue[i].burstTime = bt * 0.6;
    Rqueue[i].IO2 = bt * 0.2;
    Rqueue[i].pid = id;
    Rqueue[i].initStartTime = Rqueue[i].finalEndTime = 0;
    tempStoreBT[i] = bt * 0.6;
    tempStoreIO1[i] = 0.2 * bt;
    tempStoreIO2[i] = bt * 0.2;
  }
}

void __PS() {
  printf("PID\tArr\tIO1\tBurst\tIO2\n");
  for (int i = 0; i < NoOfProcesses; i++)
    printf("%d\t%d\t%d\t%d\t%d\n", Rqueue[i].pid, Rqueue[i].arrTime, Rqueue[i].IO1, Rqueue[i].burstTime, Rqueue[i].IO2);
}

void sched() {
  for (int i = 0; i < NoOfProcesses; i++) {
    if (CLK_CYCLE >= Rqueue[i].arrTime 
        && Rqueue[i].currState == EMBRYO) {

      int ret;
      if (Rqueue[i].IO1 != 0)
      {
        Rqueue[i].currState = IO;
        ret = pushWQ(i);
      }
      if (!ret) {
        system("echo \"$(tput setaf 2)$(tput bold)UNKNOWN: $(tput init)Resource leak or INF loop\"");
        while (1);
      }
    }
  }
}


int isAllDone() {
  for (int i = 0; i < NoOfProcesses; i++) {
    if (Rqueue[i].currState != TERMINATED)
      return 0;
  }
  return 1;
}

void __CPU_SCHED(int idx) {
  Rqueue[idx].currState = RUNNING;

  int currJobBT = Qt;
  while (Rqueue[idx].burstTime > 0 && currJobBT > 0) {
    CLK_CYCLE++;
    refreshWQ();
    Rqueue[idx].burstTime--;// adde before
    currJobBT--;
  }

  if (Rqueue[idx].burstTime == 0) {
    Rqueue[idx].currState = IO;
    pushWQ(idx);
    return;
  }
  Rqueue[idx].currState = RUNNABLE;
  // record the Complition time for a process
}

// returns the index for that process to run
void proc() {
  while (1) {
    // check if all have done
    if (isAllDone() == 1)
      return;

    int i;
    i = popRQ();
    if (i == -999) {
      // no process was found
      CLK_CYCLE++;
      refreshWQ();
    } else {
      __CPU_SCHED(i);
    }

    // when a process gets completed the scheduler is called
    sched();
    // do here
    // reinsertion
    if (i != -999 && Rqueue[i].currState == RUNNABLE) {
      // reinsert else dont reinsert
      pushRQ(i);
    }
  }
}

void ReportDis() {
  int Swt = 0;
  for (int i = 0; i < NoOfProcesses; i++)
  {
    int TT = Rqueue[i].finalEndTime - Rqueue[i].arrTime;
    int RT = Rqueue[i].initStartTime - Rqueue[i].arrTime;
    int WT = TT - tempStoreBT[i] - tempStoreIO1[i] - tempStoreIO2[i];
    Swt += WT;
    printf("Process\tPID: %d\tAT: %d\tIO1: %d\tBT: %d\tIO2: %d\tTT: %d\tWT: %d\tRT: %d\n",
           Rqueue[i].pid, Rqueue[i].arrTime, tempStoreIO1[i], tempStoreBT[i], tempStoreIO2[i], TT, WT, RT);
  }
  printf("Avg WT: %f\n", (float)(Swt)/NoOfProcesses);
}

int main() {
  CLK_CYCLE = 0;
  printf("Enter number of processes");
  scanf("%d", &NoOfProcesses);
  if (NoOfProcesses > SIZE) {
    system("echo \"$(tput setaf 1)$(tput bold)ERR: $(tput init)No of processes greater than Ready Queue CAPACITY\"");
    return 1;
  }
  Rqueue = (struct proc *)malloc(sizeof(struct proc) * NoOfProcesses);
  tempStoreBT = (int *)malloc(sizeof(int) * NoOfProcesses);
  tempStoreIO1 = (int *)malloc(sizeof(int) * NoOfProcesses);
  tempStoreIO2 = (int *)malloc(sizeof(int) * NoOfProcesses);
  initRQ();
  initWQ();
  enterData();
  __PS();
  // initial scheduler is called so as to make the process as runnable
  sched();
  proc();

  // all have done display Report
  ReportDis();

  free(Rqueue);
  free(tempStoreBT);
  free(tempStoreIO1);
  free(tempStoreIO2);
  return 0;
}
