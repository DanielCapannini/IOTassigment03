#ifndef __TASK__
#define __TASK__

class Task {
  int currentPeriod;
  int timeElapsed;
  bool run;

  
public:
  virtual void init(int period){
    currentPeriod = period;  
    timeElapsed = 0;
    run = true;
  }

  virtual void run() = 0;

  bool updateTime(int period){
    timeElapsed += period;
    if (timeElapsed >= currentPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  bool isRunning(){
    return run;
  }

  void setRunning(bool run){
    this->run = run;
  }
  
};

#endif