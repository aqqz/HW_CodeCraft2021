#ifndef __VM_H
#define __VM_H
#include <string>
class Vm
{
public:
	Vm(std::string mode,int core,int memsize,int istwonode);
	Vm(std::string mode,int id);
	Vm();
	void toString();
	
	std::string mode;
	int core;
	int memsize;
	int istwonode;
	
	//used for purchased_vms
	int id;
	int server_id;
	int node;//0:A 1:B 2:doublenode
	int day_id;
};
#endif
