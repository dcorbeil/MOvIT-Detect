#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <string>

using std::string;

#define DEBUG_SERIAL //Debug trace

bool program_loop();
string& getCmd();
void sendData(string& request, bool state, bool e);
void getData();
void formatDateTimeString();

#endif /* _PROGRAM_H_ */