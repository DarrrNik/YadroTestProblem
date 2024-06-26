#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <queue>
#include <string>
#include <functional>
#include "Tools.hpp"
#include "Help.hpp"
#include "Table.hpp"
#include "InputEvents.hpp"

std::queue<std::string> clientsQu;
std::stringstream sout;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << helpText;
        return 1;
    }

    if (!IsFileCorrect(argv[1]))
        return 2;
    
    std::ifstream fin(argv[1]);

    int tablesNumber = 0;
    fin >> tablesNumber;
    std::vector<Table> tables(tablesNumber);
    for (int i = 0; i < tablesNumber; ++i)
        tables[i].setNum(i + 1);

    WorkingTime begin, end;
    fin >> begin >> end;
    sout << begin << std::endl;  

    fin >> Table::hourCost;  

    std::map<std::string, int> clients;
    std::vector<std::function<void(WorkingTime&, std::map<std::string, int>&, const std::string&, int, std::vector<Table>&)>> EventProcessings= {
        InputClientCome, InputClientSat, InputClientWaiting, InputClientLeft
    };


    while (!fin.eof()) {
        WorkingTime eventTime;
        InputEvent inEvent;
        std::string name;
        fin >> eventTime >> inEvent >> name;
        int tableNum = -1;
        if (inEvent == InputEvent::CLIENT_SAT)
            fin >> tableNum;
        WriteInput(eventTime, name, tableNum, inEvent);
        if (!(begin <= eventTime)) {
            WriteOutput(eventTime, OutputEvent::ERROR, name, tableNum, ErrorMessages::NOT_OPEN_YET);
            continue;
        }
        EventProcessings[(int)inEvent - 1](eventTime, clients, name, tableNum, tables);
    }

    for (auto itcl = clients.begin(); itcl != clients.end();) {
        WriteOutput(end, OutputEvent::CLIENT_LEFT, itcl->first, itcl->second, ErrorMessages::DEFAULT);
        if (itcl->second) 
            tables[itcl->second - 1].clientLeftAt(end);
        itcl = clients.erase(itcl);
    }

    sout << end << std::endl;
    for (const Table& t : tables) {
        sout << t << std::endl;
    }
    
    std::cout << sout.str();

    return 0;
}