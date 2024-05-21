#include "Tools.hpp"

std::istream& operator>>(std::istream& fin, WorkingTime& time) {
    std::string input;
    fin >> input;
    input[2] = '\0';
    time.hours = atoi(input.data());
    time.minutes = atoi(input.data() + 3);
    return fin;
}

std::ostream& operator<< (std::ostream& out, const WorkingTime& time) {
    out.width(2);
    out.fill('0');
    out << time.hours << ':';
    out.width(2);
    out.fill('0');
    out << time.minutes;
    return out;
}

WorkingTime operator+(const WorkingTime& lhs, const WorkingTime& rhs) {
    return WorkingTime{(short)(lhs.hours + rhs.hours + (lhs.minutes + rhs.minutes) / 60), (short)((lhs.minutes + rhs.minutes) % 60)};
}

bool operator<=(const WorkingTime& lhs, const WorkingTime& rhs) {
    if (lhs.hours < rhs.hours)
        return true;
    if (lhs.hours > rhs.hours)
        return false;
    return lhs.minutes <= rhs.minutes;
}

bool operator==(const WorkingTime& lhs, const WorkingTime& rhs) {
    return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

std::vector<std::string> split(const std::string s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool IsCorrectTime(std::string& time) {
    if (time[0] < '0' || time[0] > '2' || (time[0] == '2' && (time[1] < '0' || time[1] > '3')) || time[1] < '0' || time[1] > '9') //check hours in time
        return false;
    if (time[2] != ':')
        return false;
    if (time[3] < '0' || time[3] > '5' || time[4] < '0' || time[4] > '9') //check minutes in time
        return false;
    return true;
}

bool IsInt(std::string& s) {
    for (char c : s) 
        if (c < '0' || c > '9')
            return false;
    return true;
}

bool IsName(std::string& s) {
    for (char c : s) 
        if (!(c >= 'a' && c <= 'z' || c >= '1' && c <= '9'))
            return false;
    return true;
}

bool IsFileCorrect(char* fileName) {
    std::ifstream fin(fileName);
    if (!fin) {
        std::cout << "File is not found.\n";
        fin.close();
        return false;
    }
    const int LINE_SIZE = 1024;
    char line[LINE_SIZE];    
    bool isThereEmpty = false;

    try {
        if (fin.eof())
            throw std::exception();        
        fin.getline(line, LINE_SIZE);                           //check tables number
        std::vector<std::string> elems = split(line, ' ');
        if (elems.size() != 1)
            throw std::exception();
        if (!IsInt(elems[0]))
            throw std::exception();
        int tablesNum = atoi(elems[0].data());
        
        if (fin.eof())
            throw std::exception();
        fin.getline(line, LINE_SIZE);                           //check start and end times
        elems = split(line, ' ');
        if (elems.size() != 2 || !IsCorrectTime(elems[0]) || !IsCorrectTime(elems[1]))
            throw std::exception();
        WorkingTime s, e;
        std::stringstream(elems[0]) >> s;
        std::stringstream(elems[1]) >> e;
        if (!(s <= e))
            throw std::exception();

        if (fin.eof())
            throw std::exception();
        fin.getline(line, LINE_SIZE);                           //check hour cost
        elems = split(line, ' ');
        if (elems.size() != 1 || !IsInt(elems[0]))
            throw std::exception();
        int hourCost = atoi(elems[0].data());

        WorkingTime prevT = {-1, -1}, curT = {-1, -1};
        while (!fin.eof()) {                                    //check event lines
            fin.getline(line, LINE_SIZE);
            if (strlen(line) == 0 && fin.eof())                 //check for '\n' in the end of file
                break;
            elems = split(line, ' ');
            if (elems.size() != 3 && elems.size() != 4)
                throw std::exception();
            if (!IsCorrectTime(elems[0]) || !IsInt(elems[1]) || !IsName(elems[2]) || (elems.size() == 4 && !IsInt(elems[3])))
                throw std::exception();

            std::stringstream(elems[0]) >> curT;                //check previous event time is lesser than or equals to current one
            if (!(prevT == WorkingTime{-1, -1}) && !(prevT <= curT)) 
                throw std::exception();
            prevT = curT;

            int inEvent = atoi(elems[1].data());
            if (inEvent < 1 || inEvent > 4)                     //check correct event number
                throw std::exception();
            if (!(inEvent == 2 && elems.size() == 4 || inEvent != 2 && elems.size() == 3))          //check that there is table number if event is 2
                throw std::exception();
            if (inEvent != 2)
                continue;
            int table = atoi(elems[3].data());
            if (!(table > 0 && table <= tablesNum))                              //check correct table number
                throw std::exception();
        }
    }
    catch (std::exception e) {
        std::cout << line << std::endl;
        fin.close();
        return false;
    }
    
    fin.close();
    return true;
}