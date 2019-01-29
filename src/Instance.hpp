#pragma once

#include "Command.hpp"

namespace MPIScheduler {

class SVGDrawer;

class Instance {
public:
  Instance(CommandPtr command, int startingRank, int ranksNumber, const string &outputDir); 
  virtual bool execute(shared_ptr<Instance> self) = 0;
  virtual void writeSVGStatistics(SVGDrawer &drawer, const Time &initialTime); 
  const string &getId() const {return _command->getId();}
  virtual void onFinished();
  virtual void onFailure(int errorCode = 0);
  int getStartingRank() const {return _startingRank;} 
  int getRanksNumber() const {return _ranksNumber;} 
  void setElapsedMs(int elapsed) {_elapsed = elapsed;}
  virtual int getElapsedMs() const {return _elapsed;}
  void setStartingElapsedMS(int starting) {_startingElapsedMS = starting;}

  static bool _jobFailureFatal;
protected:
  const string &getOutputDir() {return _outputDir;}
  
  int _startingElapsedMS;
  string _outputDir;
  CommandPtr _command;
  int _startingRank;
  int _ranksNumber;
  Time _endTime;
  int _elapsed;
};
using InstancePtr = shared_ptr<Instance>;
using InstancesHistoric = vector<InstancePtr>;

}
