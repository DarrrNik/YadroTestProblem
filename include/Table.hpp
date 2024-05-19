#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include "Tools.hpp"

class Table {
public:
    Table(int n = 0, int in = 0, WorkingTime wt = {0, 0}, WorkingTime sat = {0, 0}, bool b = false);

    bool isBusy() const;
    void clientLeftAt(const WorkingTime& t);
    void clientSatAt(const WorkingTime& t);

    void setNum(int n);
    int getNum() const;

    friend std::ostream& operator<<(std::ostream& sout, const Table& table);
    static unsigned int hourCost;
private:
    int num, income;
    WorkingTime workTime, satAtTime;
    bool busy;
};

std::ostream& operator<<(std::ostream& out, const Table& table);
bool IsThereFreeTable(const std::vector<Table>& tabels);

#endif