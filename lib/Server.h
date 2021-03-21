#ifndef __SERVER_H
#define __SERVER_H
#include <string>
#include <vector>
#include "Vm.h"
class Server
{
public:
	Server(std::string mode,int core,int memsize,int hwcost,int daycost);
	Server();
	void toString();
	std::string mode;
	int core;
	int memsize;
	int hwcost;
	int daycost;
	
	 
	int a[2]; //a[0]:a_core,a[1]:a_mem 
	int b[2];//b[0]:b_core,b[1]:b_mem
	
	//used for purchased_severs
	bool power_on;
	int id;
	int id2;
	int usetime;
	int day_id;
//	std::vector<Vm> sub_vms;
	
	
	bool isfull(Vm &add_vm); //check current server can or not contain a vm
	bool isempty();

};
#endif
