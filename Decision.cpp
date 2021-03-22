#include "Decision.h"
#include <iterator>
#include <iostream>
using namespace std;

Decision::Decision(map<string,int> dec,vector<Vm> v,int day_id)
{
	this->dec = dec;
	this->v = v;
	this->day_id = day_id;
}

Decision::Decision()
{
	
} 

void Decision::toString(vector<Server> &ps)
{
	//purchase info
	cout<<"(purchase, "<<this->dec.size()<<")"<<endl;
	for(map<string,int>::iterator it = dec.begin();it!= dec.end();it++)
	{
		cout<<"("<<it->first<<", "<<it->second<<")"<<endl;
	}
	//migration info
	cout<<"(migration, 0)"<<endl;
	//allocate info
	for(int i = 0;i<v.size();i++)
	{
		for(int j = 0;j<ps.size();j++)
		{
			if(v[i].server_id == ps[j].id && v[i].server_id!= -1)
			{
				//cerr<<"find it"<<endl;
				if(v[i].node == 0)
				{
					cout<<"("<<ps[j].id2<<", A)"<<endl;
					break;
				}
				else if(v[i].node == 1)
				{
					cout<<"("<<ps[j].id2<<", B)"<<endl;
					break;
				}
				else
				{
					cout<<"("<<ps[j].id2<<")"<<endl;
					break;
				}
			}
		}
	}
}
