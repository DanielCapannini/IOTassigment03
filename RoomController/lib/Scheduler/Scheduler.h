#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 10

class Scheduler {
  unsigned long period;
  int _taskCount;
  Task* _tasks[MAX_TASKS];
  unsigned long tempo;

public:
  void init(unsigned long period);
  virtual bool addTask(Task* task);
  virtual void run();
};

#endif