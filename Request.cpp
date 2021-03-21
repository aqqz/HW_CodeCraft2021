#include "Request.h" 
#include <string>
using namespace std;
Request::Request(string request,string vm_mode,int vm_id,int day_id)
{
	this->request = request;
	this->vm_mode = vm_mode;
	this->vm_id = vm_id;
	this->day_id = day_id;
}

Request::Request(string request,int vm_id,int day_id)
{
	this->request = request;
	this->vm_id = vm_id;
	this->day_id = day_id;
}
