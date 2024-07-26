#include <fstream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <bits/stdc++.h>
#include "grup.h"



bool compareDistanse(object i1, object i2)
{
	double distans1 = sqrt((i1.coord_x*i1.coord_x)+(i1.coord_y*i1.coord_y));
	double distans2 = sqrt((i2.coord_x*i2.coord_x)+(i2.coord_y*i2.coord_y));
	return (distans1 < distans2);
}

bool compareName(object i1, object i2)
{
	return (std::strcmp(i1.name.data(), i2.name.data()) < 0);
}

bool compareData(object i1, object i2)
{
	return (i1.data > i2.data);
}

bool compareType(object i1, object i2)
{
	return (std::strcmp(i1.type.data(), i2.type.data()) < 0);
}

std::vector<object> parsFile(const char* path)
{
	 std::string s;

	    std::vector<object> file;
		std::vector<std::string> words;
		object line;
		const char* const delimeters = " ";
		char* token;
	    std::ifstream doc(path);

	    while(getline(doc, s))
	    {
	    	if (s == "")
	    		continue;
	    	token = strtok(s.data(), delimeters);
	    	while (token != nullptr)
	    	{
	    		words.push_back(token);
	    		token = strtok(nullptr, delimeters);

	    	}

	    	line.name = words[0];
	    	words.erase(words.begin());
	    	line.coord_x =std::stod(words[0]);
	    	words.erase(words.begin());
	    	line.coord_y = std::stod(words[0]);
	    	words.erase(words.begin());
	    	line.type = words[0];
	    	words.erase(words.begin());
	    	line.data = std::stod(words[0]);
	    	words.clear();

	    	file.push_back(line);
	    }

	    doc.close();

	    return file;
}

void save_file(std::string text_File)
{
	std::ofstream out;
	    out.open("out.txt");
	    if (out.is_open())
	    {
	        out << text_File << std::endl;
	    }
	    out.close();
}

std::string struct_to_string(object line)
{
	std::string text_Line;
	text_Line += line.name + " ";
	text_Line += std::to_string(line.coord_x) + " ";
	text_Line += std::to_string(line.coord_y) + " ";
	text_Line += line.type + " ";
	text_Line += std::asctime(std::localtime(&line.data));
	text_Line += '\n';

	return text_Line;
}

std::string grup_distanse(std::vector<object> file)
{
	std::string text_File;
	bool check100{true}, check1000{true}, check10000{true}, check_other{true};
	double distanse;
	sort(file.begin(), file.end(), compareDistanse);
	for (long unsigned int i = 0; i < file.size(); i++)
	{
		distanse =sqrt((file[i].coord_x*file[i].coord_x)+(file[i].coord_y*file[i].coord_y));
	    if (distanse <= 100)
	    {
	    	if(check100)
	    	{
	    		text_File += "Группа до 100:\n\n";
	    		check100 = false;
	    	}
	    	text_File += struct_to_string(file[i]);
	    }
	    else if(distanse <=1000)
	    {
	    	if(check1000)
	    	{
	    		text_File += "Группа до 1000:\n\n";
	    		check1000 = false;
	    	}
	    	text_File += struct_to_string(file[i]);
	    }
	    else if(distanse <=10000)
	    {
	    	if(check10000)
	    	{
	    		text_File += "Группа до 10000:\n\n";
	    		check10000 = false;
	    	}
	    	text_File += struct_to_string(file[i]);
	    }
	    else
	    {
	    	if(check_other)
	    	{
	    		text_File += "Группа слишком далеко:\n\n";
	    		check_other = false;
	    	}
	    	text_File += struct_to_string(file[i]);
	    }
	}

	return text_File;
}

std::string grup_name(std::vector<object> file)
{
	std::string text_File;
	sort(file.begin(), file.end(), compareName);
	for (long unsigned int i = 0; i < file.size(); i++)
	{

			text_File += struct_to_string(file[i]);

	}

	return text_File;
}

std::string grup_data(std::vector<object> file)
{
	bool check_Week{true}, check_Month{true}, check_Year{true}, check_Other{true};
	std::string text_File;
	time_t seconds = time(NULL);
	sort(file.begin(), file.end(), compareData);
	for (long unsigned int i = 0; i < file.size(); i++)
	{
		if ((seconds - file[i].data) <= 604800)
		{
			if(check_Week)
			{
				text_File += "Групппа на этой неделе:\n\n";
				check_Week = false;
			}
			text_File += struct_to_string(file[i]);
		}
		else if((seconds - file[i].data) <= 2592000)
		{
			if(check_Month)
			{
			 	text_File += "Группа в этом месяце:\n\n";
				check_Month = false;
			}
			text_File += struct_to_string(file[i]);
		}else if((seconds - file[i].data) <= 31536000)
		{
			if(check_Year)
			{
				text_File += "Группа в этом году:\n\n";
				check_Year = false;
			}
			text_File += struct_to_string(file[i]);
		}else
		{
			if(check_Other)
			{
				text_File += "Группа в ранее:\n\n";
				check_Other = false;
			}
			text_File += struct_to_string(file[i]);
		}
	}

	return text_File;
}

std::string grup_type(std::vector<object> file)
{
	std::string text_File, text_Temp, text_Type;
	std::string grup_Other = "Группа разное:\n\n";
	int сounter = 0;
	sort(file.begin(), file.end(), compareType);
	text_Type = file[0].type;
	for (long unsigned int i = 0; i < file.size(); i++)
	{
		if(text_Type == file[i].type && i+1 < file.size())
		{
			text_Temp += struct_to_string(file[i]);
			сounter++;
		}else if (сounter <= 5)
		{
			if(i+1 == file.size())
				text_Temp += struct_to_string(file[i]);
			grup_Other += text_Temp;
			сounter = 0;
			text_Temp = "";
			text_Type = file[i].type;
		}else
		{
			if(i+1 == file.size())
				text_Temp += struct_to_string(file[i]);
			text_File += "Группа " + text_Type + ":\n\n";
			text_File += text_Temp;
			сounter = 0;
			text_Temp = "";
			text_Type = file[i].type;
			text_Temp += struct_to_string(file[i]);
		}
	}
	text_File += grup_Other;

	return text_File;
}

std::string grup(std::vector<object> file, int metod)
{
	object test;
	if (test.name != "")
		file.push_back(test);
	std::string text_File;
	switch(metod)
	{
		case 0:
			text_File = grup_distanse(file);
			break;
		case 1:
			text_File = grup_name(file);
			break;
		case 2:
			text_File = grup_data(file);
			break;
		case 3:
			text_File = grup_type(file);
			break;
		default:
			std::cout << "Error\n";
	}
	return text_File;
}
