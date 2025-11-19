#ifndef DETACHED_PROCESS_H
#define DETACHED_PROCESS_H

#include <string>

class DetachedProcess {
public:
	DetachedProcess(std::string cmd);
	~DetachedProcess();
private:
};

#endif