#include <Arduino.h>
#include "Task.h"

#define MAX_TASKS 10

class Scheduler
{
    Task* _tasks[MAX_TASKS];
    int _taskCount;

public:
    Scheduler();
    void addTask(Task* task);
    void removeTask(Task* task);
    void run();
    String toString();
};
