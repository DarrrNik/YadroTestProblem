#ifndef INPUTEVENTS_HPP
#define INPUTEVENTS_HPP

#include <string>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include "Tools.hpp"
#include "Table.hpp"
#include "OutputEvents.hpp"

enum class InputEvent {
    CLIENT_COME = 1,
    CLIENT_SAT,
    CLIENT_WAITING,
    CLIENT_LEFT
};

void InputClientCome(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables);
void InputClientSat(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables);
void InputClientWaiting(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables);
void InputClientLeft(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables);

void WriteInput(WorkingTime& evTime, const std::string& name, int tableNum, InputEvent& ev);

std::istream& operator>>(std::istream& in, InputEvent& ev);
std::ostream& operator<<(std::ostream& out, InputEvent& ev);

#endif