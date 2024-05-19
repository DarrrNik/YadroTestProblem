#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

struct WorkingTime {
    short hours, minutes;
};

std::istream& operator>>(std::istream& in, WorkingTime& time);
std::ostream& operator<<(std::ostream& out, const WorkingTime& time);
WorkingTime operator+(const WorkingTime& lhs, const WorkingTime& rhs);
bool operator<=(const WorkingTime& lhs, const WorkingTime& rhs);
bool operator==(const WorkingTime& lhs, const WorkingTime& rhs);

std::vector<std::string> split(const std::string s, char delim);
bool IsCorrectTime(std::string& time);
bool IsInt(std::string& s);
bool IsName(std::string& s);
bool IsFileCorrect(char* fileName);

#endif