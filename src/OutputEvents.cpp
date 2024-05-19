#include "OutputEvents.hpp"

void WriteError(WorkingTime& time, ErrorMessages er) {
    sout << time << " 13 ";
    switch (er) {
        case ErrorMessages::ALREADY_INSIDE:
            sout << "YouShallNotPass\n";
        break;
        case ErrorMessages::NOT_OPEN_YET:
            sout << "NotOpenYet\n";
        break;
        case ErrorMessages::PLACE_IS_BUSY:
            sout << "PlaceIsBusy\n";
        break;
        case ErrorMessages::CLIENT_UNKNOWN:
            sout << "ClientUnknown\n";
        break;
        case ErrorMessages::CANT_WAIT:
            sout << "ICanWaitNoLonger!\n";
        break;
    };
}

void WriteOutput(WorkingTime& time, OutputEvent oev, const std::string& name, int tableNum, ErrorMessages er) {
    switch (oev) {
        case OutputEvent::CLIENT_LEFT:
            sout << time << " 11 " << name << std::endl;
        break;
        case OutputEvent::CLIENT_SAT:
            sout << time << " 12 " << name << ' ' << tableNum << std::endl;
        break;
        case OutputEvent::ERROR:
            WriteError(time, er);
        break;
        default:
        break;
    };
}