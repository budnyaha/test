/*
 * grup.h
 *
 *  Created on: 26 июл. 2024 г.
 *      Author: Budnaha
 */

#ifndef SRS_GRUP_H_
#define SRS_GRUP_H_

struct object
{
	std::string name;
	double coord_x;
	double coord_y;
	std::string type;
	time_t data;

};

std::string grup(std::vector<object> file, int metod);
std::vector<object> parsFile(const char* path);
void save_file(std::string text_File);



#endif /* SRS_GRUP_H_ */
