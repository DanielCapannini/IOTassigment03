#include "Scheduler.h"
#include <Arduino.h>

#define MAX_TASKS 10

void Scheduler::init(unsigned long period) {
  this->period = period;
  _taskCount = 0;
  time = millis();  
}

void Scheduler::run() {   
  while (millis() - time < period) {}
    for (int i = 0; i < _taskCount; i++) {
      if (_tasks[i]->updateTime(period)) {
        _tasks[i]->run();
      }
    }
  time = millis();
}

bool Scheduler::addTask(Task* task) {
  if (_taskCount < MAX_TASKS-1) {
    _tasks[_taskCount] = task;
    _taskCount++;
    return true;
  } else {
    return false; 
  }
}
  