#include "Table.hpp"

unsigned int Table::hourCost = 0;

Table::Table(int n, int in, WorkingTime wt, WorkingTime sat, bool b) 
    : num(n), income(in), workTime(wt), satAtTime(sat), busy(b) { }

bool Table::isBusy() const {
    return busy;
}

void Table::clientLeftAt(const WorkingTime& t) {
    busy = false;
    WorkingTime diff = {(short)(t.hours - satAtTime.hours - (int)(t.minutes < satAtTime.minutes)), (short)((t.minutes - satAtTime.minutes + 60) % 60)};
    workTime = workTime + diff;
    income += hourCost + hourCost * diff.hours;
}

void Table::clientSatAt(const WorkingTime& t) {
    busy = true;
    satAtTime = t;
}

void Table::setNum(int n) {
    num = n;
}

int Table::getNum() const {
    return num;
}

std::ostream& operator<<(std::ostream& sout, const Table& table) {
    sout << table.num << ' ' << table.income << ' ' << table.workTime;
    return sout;
}

bool IsThereFreeTable(const std::vector<Table>& tables) {
    for (const Table& t : tables)
        if (!t.isBusy())
            return true;
    return false;
}
