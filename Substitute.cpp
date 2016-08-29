#include "Substitute.h"
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

Substitute::Substitute(char* file_name) : filename(file_name), queue(new TrackingDeque<char>())
{
	pos_cur=0;
	pos_put=0;
	pos_check=0;
	substitutions=0;
	f_stream.open(file_name, ios_base::in | ios_base::out);
}

Substitute::~Substitute()
{
	delete queue;
	f_stream.close();
	if(old_str.size() > rep_str.size())
	{
		int return_val;
		return_val = truncate(filename, pos_put);
	}
}

void Substitute :: get(char &push)
{
   f_stream.seekg(pos_cur);
   push = f_stream.get();
   pos_cur++;
}

void Substitute::substitute(string old_s, string new_s)
{
	old_str = old_s;
	rep_str = new_s;
	char cur_char;
	pos_cur = 0;
	pos_check = 0;
	pos_put = 0;

	do
	{		
		if(queue->size() > 0)
		{	
			if(f_stream.eof() && queue->size() == 1)
			{
				break;
			}
			cur_char = queue->at(0);
			queue->pop_front();
			if(!f_stream.eof())
			{
				f_stream.seekg(pos_cur);
				char push = f_stream.get();
				queue->push_back(push);
				pos_cur++;
			}			
		}
		else
		{
			f_stream.seekg(pos_cur);
			f_stream.get(cur_char);
			if(f_stream.eof())
			break;
			pos_cur++;
		}
			
		if(pos_check > 0 && (cur_char != old_s[pos_check]))
		{		
			int add_to_pos_check = 0;
			int index = 0;
			int print_these = pos_check;
			for(int i = 0; i < pos_check; i++)
			{
				if(old_s[i] == old_s[index] && i != 0)
				{
					print_these = i;
					add_to_pos_check++;
					index++;
				}
				else
				{
					add_to_pos_check = 0;
					index = 0;
					print_these = pos_check;
				}						
			}
			for(int j = 0; j < print_these; j++)
			{
				f_stream.seekp(pos_put);				
				f_stream.put(old_s[j]);
				pos_put++;
			}
			pos_check = add_to_pos_check;
		}
		if(cur_char == old_s[pos_check])
		{
			pos_check++;
			
			if(pos_check == old_s.size()) 
			{
				if(old_s.size() == new_s.size())
				{
					for(int i = 0; i < new_s.size(); i++)
					{
						f_stream.seekp(pos_put);
						f_stream.put(new_s[i]);
						pos_put++;	
					}
				}
				else if(old_s.size() > new_s.size())
				{
					for(int i = 0; i < new_s.size(); i++)
					{
						f_stream.seekp(pos_put);
						f_stream.put(new_s[i]);
						pos_put++;	
					}
				}
				else if(old_s.size() < new_s.size())
				{		
					for(int i = 0; i < (new_s.size()-old_s.size()); i++)
					{
						if(!f_stream.eof())
						{
							f_stream.seekg(pos_cur);
							char check = f_stream.get();
							pos_cur++;
							
							queue->push_back(check);
							if(f_stream.eof())
							{
								break;
							}
							
						}
					}
					if(f_stream.eof())
					{
						f_stream.clear(); 
						f_stream.seekp(pos_put);
						for(int i = 0; i < new_s.size(); i++)
						{
							f_stream.put(new_s[i]);
							pos_put++;
						}
						f_stream.setstate(ios::eofbit); 
					}
					else
					{
						f_stream.seekp(pos_put);
						for(int i = 0; i < new_s.size(); i++)
						{
							f_stream.put(new_s[i]);
							pos_put++;
						}
					}
				}
				substitutions++;
				pos_check = 0; 
			}
		}
		else
		{	
			if(cur_char != EOF) 
			{
				if(!f_stream.eof())
				{
					f_stream.seekp(pos_put);
					f_stream.put(cur_char);
					pos_put++;
				}
				else
				{
					f_stream.clear();
					f_stream.seekp(pos_put);
					f_stream.put(cur_char);
					pos_put++;
					f_stream.setstate(ios::eofbit);
				}
			}
		}
		
	}
	while(cur_char != EOF);
}





