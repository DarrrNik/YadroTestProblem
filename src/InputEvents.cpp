#include "InputEvents.hpp"

extern std::queue<std::string> clientsQu;

void InputClientCome(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables) {
    if (clients.find(name) != clients.end()) {
        WriteOutput(time, OutputEvent::ERROR, name, tableNum, ErrorMessages::ALREADY_INSIDE);
        return;
    }
    clients.insert(std::make_pair(name, 0));
}

void InputClientSat(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables) {
    if (clients.find(name) == clients.end()) {
        WriteOutput(time, OutputEvent::ERROR, name, tableNum, ErrorMessages::CLIENT_UNKNOWN);
        return;
    }
    if (tables[tableNum - 1].isBusy()) {
        WriteOutput(time, OutputEvent::ERROR, name, tableNum, ErrorMessages::PLACE_IS_BUSY);
        return;
    }
    if (clients[name]) 
        tables[clients[name] - 1].clientLeftAt(time);
    clients[name] = tableNum;
    tables[tableNum - 1].clientSatAt(time);
}

void InputClientWaiting(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables) {
    if (clients.find(name) == clients.end()){
        WriteOutput(time, OutputEvent::ERROR, name, tableNum, ErrorMessages::CLIENT_UNKNOWN);
        return;
    }
    if (IsThereFreeTable(tables)) {
        WriteOutput(time, OutputEvent::ERROR, name, tableNum, ErrorMessages::CANT_WAIT);
        return;
    }
    if (clientsQu.size() > tables.size()) {
        WriteOutput(time, OutputEvent::CLIENT_LEFT, name, tableNum, ErrorMessages::DEFAULT);
        clients.erase(name);
        return;
    }
    clientsQu.push(name);
}   

void InputClientLeft(WorkingTime& time, std::map<std::string, int>& clients, const std::string& name, int tableNum, std::vector<Table>& tables) {
    if (clients.find(name) == clients.end()){
        WriteOutput(time, OutputEvent::ERROR, name, tableNum, ErrorMessages::CLIENT_UNKNOWN);
        return;
    }
    tableNum = clients[name];
    clients.erase(name);
    tables[tableNum - 1].clientLeftAt(time);
    if (clientsQu.empty())
        return;
    tables[tableNum - 1].clientSatAt(time);
    clients[clientsQu.front()] = tableNum;
    WriteOutput(time, OutputEvent::CLIENT_SAT, clientsQu.front(), tableNum, ErrorMessages::DEFAULT);
    clientsQu.pop();
}

void WriteInput(WorkingTime& evTime, const std::string& name, int tableNum, InputEvent& ev) {
    sout << evTime << ' ' << ev << ' ' << name << ' ';
    if (ev == InputEvent::CLIENT_SAT)
        sout << tableNum;
    sout << std::endl;
}

std::istream& operator>>(std::istream& in, InputEvent& ev) {
    int num;
    in >> num;
    ev = (InputEvent)num;
    return in;
}

std::ostream& operator<<(std::ostream& out, InputEvent& ev) {
    out << (int)ev;
    return out;
}