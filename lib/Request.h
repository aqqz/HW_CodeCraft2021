#ifndef __REQUEST_H
#define __REQUEST_H 
#include <string>
class Request{
	public:
		Request(std::string request,std::string vm_mode,int vm_id,int day_id);
		Request(std::string request,int vm_id,int day_id);
		std::string request;
		std::string vm_mode;
		int vm_id;
		int day_id;
};
#endif
