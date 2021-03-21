#include "Server.h"
#include <iostream>
using namespace std;
Server::Server(string mode,int core,int memsize,int hwcost,int daycost)
{
	this->mode = mode;
	this->core = core;
	this->memsize = memsize;
	this->hwcost = hwcost;
	this->daycost = daycost;
	
	this->power_on = false;
	
	
	this->a[0] = this->b[0] = core/2;
	this->a[1] = this->b[1] = memsize/2;
	
	//used for purchased_servers
	this->id = 0;
	this->id2 = -1;
	this->usetime = 0;
	this->power_on = true;
	this->day_id = 0xfffffff;	
}

Server::Server()
{
	
}

bool Server::isfull(Vm &add_vm)
{
	bool isfull = false; 
	if(add_vm.istwonode == 1)
	{
		//double node	
		if(add_vm.core/2 > this->a[0] || add_vm.memsize/2 > this->a[1] || add_vm.core/2 > this->b[0] || add_vm.memsize/2 > this->b[1])
		{
			isfull = true;
		} 
	}
	else 
	{
		//single node
		if(add_vm.core > this->a[0] || add_vm.memsize > this->a[1] || add_vm.core > this->b[0] || add_vm.memsize > this->b[1])
		{
			isfull = true;	
		}		
	}
	return isfull;	
} 

bool Server::isempty()
{
	bool isempty = false;
	if(this->core/2 == this->a[0] == this->b[0])
	{
		isempty = true;	
	} 
	return isempty;
} 

void Server::toString()
{
	cout<<mode<<" "<<id<<endl;
}
