#ifndef OUTPUTEVENTS_HPP
#define OUTPUTEVENTS_HPP

#include <sstream>
#include <string>
#include "Tools.hpp"

extern std::stringstream sout;

enum class OutputEvent {
    CLIENT_LEFT,
    CLIENT_SAT,
    ERROR,
    OK
};

enum class ErrorMessages {
    ALREADY_INSIDE,
    NOT_OPEN_YET,
    PLACE_IS_BUSY,
    CLIENT_UNKNOWN,
    CANT_WAIT,
    DEFAULT
};

void WriteError(WorkingTime& time, ErrorMessages er);
void WriteOutput(WorkingTime& time, OutputEvent oev, const std::string& name, int tableNum, ErrorMessages er);

#endif