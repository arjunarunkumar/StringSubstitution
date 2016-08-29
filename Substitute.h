#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H
#include <fstream>
#include "Deque.h"

class Substitute
{
	public:
		Substitute(char* file_name);
		~Substitute();
		void substitute(string old_s, string rep_s);
	private:
		fstream f_stream;
		void get(char &push);
		int pos_cur;
		int pos_put;
		int pos_check;
		TrackingDeque<char> *queue;
		char *filename;
		string old_str;
		string rep_str;
		int substitutions;

};


#endif
