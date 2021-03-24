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
	
	
	//used for purchased_servers
	this->a[0] = this->b[0] = core/2;
	this->a[1] = this->b[1] = memsize/2;
	this->power_on = false;
	this->id = 0;
	this->id2 = -1;
	this->usetime = 0;
	this->day_id = 0;
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
	if(this->core/2 == this->a[0] && this->core/2 == this->b[0] && this->memsize/2 == this->a[1] && this->memsize/2 == this->b[1])
	{
		isempty = true;	
	} 
	return isempty;
} 

void Server::toString()
{
	cout<<mode<<" "<<id<<endl;
}

void Server::clean()
{
	this->a[0] = this->core/2;
	this->b[0] = this->core/2;
	this->a[1] = this->memsize/2;
	this->b[1] = this->memsize/2;
	this->sub_vms.clear();
}

bool Server::add(Vm &v)
{
	bool add_success = false;
	if(v.istwonode)
	{	
		if(this->a[0] >= v.core/2 && this->a[1] >= v.memsize/2 && this->b[0] >= v.core/2 && this->b[1] >= v.memsize/2)
		{
			//add	
			this->a[0] -= v.core/2;
			this->a[1] -= v.memsize/2;
			this->b[0] -= v.core/2;
			this->b[1] -= v.memsize/2;
			add_success = true;
		}
	}
	else
	{
		if(this->a[0] >= v.core && this->a[1] >= v.memsize)
		{
			//add_to_A
			this->a[0] -= v.core;
			this->a[1] -= v.memsize;
			v.node = 0;
			add_success = true;
			
		}else if(this->b[0] >= v.core && this->b[1] >= v.memsize)
		{
			//add_to_B
			this->b[0] -= v.core;
			this->b[1] -= v.memsize;
			v.node = 1;
			add_success = true;
		}
	}
	if(add_success)
	{
		v.server_id = this->id;	 
		this->sub_vms.push_back(v);
	}
	return add_success;
}

bool Server::del(Vm &v)
{
	bool del_success = false;
	if(v.server_id == this->id)
	{
		del_success = true;
		v.server_id = -1;
		//del
		if(v.node == 2)
		{
			//double node
			this->a[0] += v.core/2;
			this->a[1] += v.memsize/2;
			this->b[0] += v.core/2;
			this->b[1] += v.memsize/2; 
		}
		else if(v.node == 0)
		{
			//in_A
			this->a[0] += v.core;
			this->a[1] += v.memsize;
		}
		else
		{
			//in_B
			this->b[0] += v.core;
			this->b[1] += v.memsize;
		}
		// cerr<<"del: v_id: "<<v.id<<" v_server_id: "<<v.server_id<<endl;
		if(this->isempty())
		{
			this->power_on = false;
		}
	}

	return del_success;
}

bool Server::miguration(Vm &v,Server &des)
{
	bool migurate_success = false;

	bool del = this->del(v);
	bool add = des.add(v);
	if(del && add)
		migurate_success = true;
	return migurate_success;
}
