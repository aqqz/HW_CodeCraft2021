#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector> 
#include <iterator>
#include <algorithm>
#include "Server.h"
#include "Vm.h"
#include "Request.h"
#include "Decision.h"
#include "time.h"


using namespace std;
int total_cost = 0;
int number = 0;
//compare server by hwcost
bool compare(Server &s1,Server &s2)
{
	if(s1.hwcost < s2.hwcost)
	{
		return 1;
	}
	else if(s1.hwcost == s2.hwcost&&s1.daycost < s2.daycost)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void read_save_data(istream &in,vector<Server> & vec1,vector<Vm> & vec2,vector<vector<Request> > & vec3)
{
	int N,M,T,R;
	in>>N;
	//in.seekg(1,ios::cur);	
	
	for(int i = 0;i<N;i++)
	{
		//read
		string temp;
		// in.seekg(1,ios::cur);
		in.ignore();
		in>>temp;
		string temp_mode;
		int temp_core,temp_memsize,temp_hwcost,temp_daycost;
		temp_mode = temp.substr(1,temp.size()-2);		
		// in.seekg(1,ios::cur);
		in>>temp_core;
		// in.seekg(2,ios::cur);
		in.ignore();
		in>>temp_memsize;
		// in.seekg(2,ios::cur);
		in.ignore();
		in>>temp_hwcost;
		// in.seekg(2,ios::cur);
		in.ignore();
		in>>temp_daycost;
		// in.seekg(2,ios::cur);
		in.ignore();
		//save
		Server temp_server(temp_mode,temp_core,temp_memsize,temp_hwcost,temp_daycost);
		vec1.push_back(temp_server);
	}
	in>>M;
	// in.seekg(1,ios::cur);
	for(int i = 0;i<M;i++)
	{
		//read
		string temp;
		// in.seekg(1,ios::cur);
		in.ignore();
		in>>temp;	
		string temp_mode;
		int temp_core,temp_memsize,temp_twonode;
		temp_mode = temp.substr(1,temp.size()-2);
		// in.seekg(1,ios::cur);
		in>>temp_core;
		// in.seekg(2,ios::cur);
		in.ignore();
		in>>temp_memsize;
		// in.seekg(2,ios::cur);
		in.ignore();
		in>>temp_twonode;
		// in.seekg(2,ios::cur);
		in.ignore();
		//save
		Vm temp_vm(temp_mode,temp_core,temp_memsize,temp_twonode);
		vec2.push_back(temp_vm);	
	}
	in>>T;
	// in.seekg(1,ios::cur);
	for(int i = 0;i<T;i++)
	{
		in>>R;
		// in.seekg(1,ios::cur);
		
		vector<Request> temp_vec;	
		for(int j = 0;j<R;j++)
		{
			//read
			string temp_request,temp_vm_mode;
			int temp_vm_id; 
			// in.seekg(1,ios::cur);
			in.ignore();
			in>>temp_request;
			temp_request = temp_request.substr(1,3);
			if(temp_request == "add")
			{
				// in.seekg(1,ios::cur);
				in>>temp_vm_mode;
				temp_vm_mode = temp_vm_mode.substr(0,temp_vm_mode.size()-1);
				// in.seekg(1,ios::cur);
				in>>temp_vm_id;
				// in.seekg(2,ios::cur);
				in.ignore();
				//save
				Request temp_requests(temp_request,temp_vm_mode,temp_vm_id,j+1);
				temp_vec.push_back(temp_requests);
			}
			if(temp_request == "del")
			{
				// in.seekg(1,ios::cur);
				in>>temp_vm_id;
				// in.seekg(2,ios::cur);
				in.ignore();
				//save
				Request temp_requests(temp_request,temp_vm_id,j+1);
				temp_vec.push_back(temp_requests);
			}
		}
		vec3.push_back(temp_vec);
	}
}

void test_print(vector<Server> & servers,vector<Vm> & vms,vector<vector<Request> > & requests)
{
	for(int i = 0;i<servers.size();i++)
	{
		cout<<servers[i].mode<<" "<<servers[i].core<<" "<<servers[i].memsize<<" "<<servers[i].hwcost<<" "<<servers[i].daycost<<endl; 
	}
	for(int i = 0;i<vms.size();i++)
	{
		cout<<vms[i].mode<<" "<<vms[i].core<<" "<<vms[i].memsize<<" "<<vms[i].istwonode<<endl;
	}
	for(int i = 0;i<requests.size();i++)
	{
		vector<Request> vec_temp = requests[i];
		for(int j = 0;j<vec_temp.size();j++)
		{
			if(vec_temp[j].vm_mode!="")
			{
				cout<<vec_temp[j].request<<" "<<vec_temp[j].vm_mode<<" "<<vec_temp[j].vm_id<<endl;	
			}
			else
			{
				cout<<vec_temp[j].request<<" "<<vec_temp[j].vm_id<<endl;	
			}	
		}
	}
}

//container_all_full
bool servers_full(vector<Server> &ps,Vm &v)
{
	if(ps.size()==0)
	{
		return true;
	}
	for(int i = 0;i<ps.size();i++)
	{
		if(!ps[i].isfull(v))
		{
			return false;			
		}
	}	
	return true;
}

//get_vm_from_request
Vm get_vm_from_request(vector<Vm> &v,Request &r)
{
	Vm newvm;
	if(r.request == "add")
	{
		for(int i = 0;i<v.size();i++)
		{
			if(r.vm_mode == v[i].mode)
			{
				newvm = Vm(v[i]);
				newvm.id = r.vm_id;
			}	
		}		
	}
	else
	{
		for(int i = 0;i<v.size();i++)
		{
			if(r.vm_id == v[i].id)
			{
				newvm = Vm(v[i]);
			}
		}
	}
	return newvm;	
}

//purchase_server
// void purchase_server(vector<Server> &ss,vector<Server> &ps,int day_id)
// {
// 	Server temp_server(ss[0]);
// 	temp_server.day_id = day_id;
// 	temp_server.id = 0;
// 	ps.push_back(temp_server);
// 	// cerr<<"purchase server: " + (ps.end() - 1)->mode<<" number: "<<(ps.end() - 1)->id<<endl; 
// }

//expan_server
void expan_server(vector<Server> &ss,vector<Server> &ps,Vm &v,int day_id)
{
	for(int i = 0;i<ss.size();i++)
	{
		if(!ss[i].isfull(v))
		{
			// ss[i].toString();		 
			Server temp_server(ss[i]);
			temp_server.day_id = day_id;
			temp_server.id = ps.size();
			ps.push_back(temp_server);
			break;
		}
	}	
	// cerr<<"purchase server: " + (ps.end() - 1)->mode<<" number: "<<(ps.end() - 1)->id<<endl; 
}
int add_count = 0;
//add()
bool add(vector<Server> &ps,Vm &v,vector<Vm> &pv)
{
	bool add_success = false;	
	for(int i = 0;i<ps.size();i++)
	{
		if(v.istwonode)
		{	
			if(ps[i].a[0] >= v.core/2 && ps[i].a[1] >= v.memsize/2 && ps[i].b[0] >= v.core/2 && ps[i].b[1] >= v.memsize/2)
			{
				//add	
				ps[i].a[0] -= v.core/2;
				ps[i].a[1] -= v.memsize/2;
				ps[i].b[0] -= v.core/2;
				ps[i].b[1] -= v.memsize/2;
				add_success = true;
			}
		}
		else
		{
			if(ps[i].a[0] >= v.core && ps[i].a[1] >= v.memsize)
			{
				//add_to_A
				ps[i].a[0] -= v.core;
				ps[i].a[1] -= v.memsize;
				v.node = 0;
				add_success = true;
				
			}else if(ps[i].b[0] >= v.core && ps[i].b[1] >= v.memsize)
			{
				//add_to_B
				ps[i].b[0] -= v.core;
				ps[i].b[1] -= v.memsize;
				v.node = 1;
				add_success = true;
			}
		}
		//double bind
		if(add_success)
		{
			v.server_id = ps[i].id;	 
			pv.push_back(v);
			add_count++;
			// cerr<<"add vm success"<<endl;
			// cerr<<add_count<<" vmid: "<<v.id<<" serverid: "<<v.server_id<<endl;
			break;
		}
	}
	return add_success;
}

//del
bool del(vector<Server> &ps,Vm &v,vector<Vm> &pv)
{
	bool del_success;
	for(int i = 0;i<ps.size();i++)
	{
		if(v.server_id == ps[i].id)
		{
			// cerr<<"find it"<<endl;
			del_success = true;
			v.server_id = -1;
			//del
			if(v.node == 2)
			{
				//double node
				ps[i].a[0] += v.core/2;
				ps[i].a[1] += v.memsize/2;
				ps[i].b[0] += v.core/2;
				ps[i].b[1] += v.memsize/2; 
			}
			else if(v.node == 0)
			{
				//in_A
				ps[i].a[0] += v.core;
				ps[i].a[1] += v.memsize;
			}
			else
			{
				//in_B
				ps[i].b[0] += v.core;
				ps[i].b[1] += v.memsize;
			}
			// cerr<<"del: v_id: "<<v.id<<" v_server_id: "<<v.server_id<<endl;
			
			for(vector<Vm>::iterator it = pv.begin();it!=pv.end();it++)
			{
				if(it->id == v.id)
				{
					it = pv.erase(it);
				}
			}
			if(ps[i].isempty())
			{
				ps[i].power_on = false;
			}
			break;	
		}
		else
		{
			del_success = false;
		}
	}
	return del_success;
} 

//sets_update
void decision_update(vector<Server> &ps,vector<Vm> &pv,Decision &d)
{
	for(int i = 0;i<ps.size();i++)
	{
		if(ps[i].day_id == d.day_id)
		{
			d.dec[ps[i].mode]++;
		}
	} 
	Vm temp_vm;
	for(int i = 0;i<pv.size();i++)
	{
		if(pv[i].day_id == d.day_id)
		{
			temp_vm = Vm(pv[i]);
			d.v.push_back(temp_vm);
		}
	}
}

//number_server
void number_server(vector<Server> &ps,Decision &d)
{
	for(map<string,int>::iterator it = d.dec.begin();it!= d.dec.end();it++)
	{
		for(int i = 0;i<ps.size();i++)
		{
			if(ps[i].day_id == d.day_id && ps[i].mode == it->first)
			{
				ps[i].id2 = number++;
			}
		}
	}
}

//show_purchase
void show_purchase(vector<Server> &ps,vector<Vm> &pv)
{
	for(int i = 0;i<ps.size();i++)
	{
		cout<<ps[i].mode<<" "<<ps[i].core<<" "<<ps[i].memsize<<" "<<ps[i].a[0]<<" "<<ps[i].a[1]<<" "<<ps[i].hwcost<<" "<<ps[i].daycost<<" "<<\
		ps[i].id<<" "<<ps[i].id2<<" power_on: "<<ps[i].power_on<<" day_id: "<<ps[i].day_id<<endl; 
	}
	for(int i = 0;i<pv.size();i++)
	{
		cout<<pv[i].mode<<" "<<pv[i].core<<" "<<pv[i].memsize<<" "<<pv[i].id<<" "<<pv[i].server_id<<" day_id: "<<pv[i].day_id<<endl;
	}
}

void compute_cost(vector<Server> &ps)
{
	for (int i = 0; i<ps.size();i++)
	{
		total_cost += (ps[i].usetime * ps[i].daycost + ps[i].hwcost);
	}
}
	
int main()
{
	// clock_t start,end;
	// start = clock();
	// TODO:read standard input
	char path[80] = "/home/taozhi/Desktop/competition/training-data/training-1.txt"; 
	// char path[80] = "/home/taozhi/Desktop/competition/SDK/SDK_C++/CodeCraft-2021/1.txt";

	// freopen(path,"r",stdin);
	// freopen("/home/taozhi/Desktop/data.txt","w+",stdout);
	vector<Server> servers;
	vector<Vm> vms;
	vector<vector<Request> > requests;
	
	read_save_data(cin,servers,vms,requests);
	fclose(stdin);
	 
	sort(servers.begin(),servers.end(),compare);
	// test_print(servers,vms,requests);
	
	vector<Server> purchased_servers;
	vector<Vm> purchased_vms;
	vector<Decision> decs;  
	
	// TODO:process
	for(int i = 0;i<requests.size();i++)
	{
		Decision dec;
		//every_day
		vector<Request> day_req = requests[i];
		for(int j = 0;j<purchased_servers.size();j++)
		{
			if(purchased_servers[i].power_on)
			{
				purchased_servers[i].usetime++;
			}	
		}
		for(int j = 0;j<day_req.size();j++)
		{
			//every_entry
			Vm operator_vm = get_vm_from_request(vms,day_req[j]);
			operator_vm.day_id = i;
			//add
			if(day_req[j].request == "add")
			{
				//get_vm_from_request
				Vm add_vm;
				add_vm = operator_vm;
				// add_vm.toString();
				//container_is_full
				if(servers_full(purchased_servers,add_vm))
				{
					// cerr<<"container is not enough!!!"<<endl;
					expan_server(servers,purchased_servers,add_vm,i);
				}
				add(purchased_servers,add_vm,purchased_vms);
			}
			
			//del
			if(day_req[j].request == "del")
			{
				//get_vm_from_request
				Vm del_vm;
				del_vm = operator_vm;
				del(purchased_servers,del_vm,purchased_vms);
			}
		}
			
		dec.day_id = i;
		decision_update(purchased_servers,purchased_vms,dec);
		number_server(purchased_servers,dec);
		decs.push_back(dec);		
	}
	
	// TODO:write standard output
	for(int i = 0;i<decs.size();i++)
	{
		decs[i].toString(purchased_servers);
	}
	// show_purchase(purchased_servers,purchased_vms);
	// TODO:fflush(stdout);
	// compute_cost(purchased_servers);
	// cout<<total_cost<<endl;
	// end = clock();
	// cout<<(double)(end-start)/CLOCKS_PER_SEC;
	fflush(stdout);
	fclose(stdout);	
	
	return 0;
}
