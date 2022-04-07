enum state {
  RUNNING,
  RUNNABLE,
  // WAITING,
  TERMINATED,
  EMBRYO
};


struct proc {
  int pid;
  int arrTime;
  int burstTime;
  enum state currState;
};

struct proc* Rqueue;