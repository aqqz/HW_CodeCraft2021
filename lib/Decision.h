#ifndef __DECISION_H
#define __DECISION_H
#include <vector>
#include <string>
#include "Vm.h"
#include "Server.h"
#include <map>
class Decision
{
	public:
		Decision(std::map<std::string ,int> dec,std::vector<Vm> v,int day_id);
		Decision();
		std::map<std::string ,int> dec;
		std::vector<Vm> v;
		int day_id;
		
		void toString(std::vector<Server> &ps);
};
#endif
