#include "Scheduler.h"
#include <Arduino.h>

#define MAX_TASKS 10

void Scheduler::init(unsigned long period) {
  this->period = period;
  _taskCount = 0;
  tempo = millis();  
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
  
void Scheduler::run() {   
  while (millis() - tempo < period) {}
    for (int i = 0; i < _taskCount; i++) {
      if (_tasks[i]->updateTime(period)) {
        _tasks[i]->tick();
      }
    }
  tempo = millis();
}