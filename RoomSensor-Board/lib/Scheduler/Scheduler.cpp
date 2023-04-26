#include "Scheduler.h"

Scheduler::Scheduler()
{
    _taskCount = 0;
}

void Scheduler::init()
{
}

void Scheduler::addTask(Task* task)
{
    if (_taskCount < MAX_TASKS)
    {
        _tasks[_taskCount] = task;
        _taskCount++;
    }
}

void Scheduler::removeTask(Task* task)
{
    for (int i = 0; i < _taskCount; i++)
    {
        if (_tasks[i] == task)
        {
            _tasks[i] = _tasks[_taskCount - 1];
            _taskCount--;
        }
    }
}

void Scheduler::run()
{
    for (int i = 0; i < _taskCount; i++)
    {
        _tasks[i]->run();
    }
}

String Scheduler::toString()
{
    String result = "Scheduler: ";
    for (int i = 0; i < _taskCount; i++)
    {
        result += _tasks[i]->toString();
    }
    return result;
}

// Path: RoomController\lib\Scheduler\Scheduler.cpp