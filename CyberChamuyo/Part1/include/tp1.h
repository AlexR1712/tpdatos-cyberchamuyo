#ifndef TP1_H_
#define TP1_H_

#ifndef USER_COMMAND_SEPARATOR
#define USER_COMMAND_SEPARATOR ' '
#endif /*USER_COMMAND_SEPARATOR*/

#ifndef USER_COMMAND_EXIT
#define USER_COMMAND_EXIT "salir"
#endif /*USER_COMMAND_EXIT*/

#include <string>
#include <vector>

std::string parseCommand(std::string& userInput, std::vector<std::string>& commandParams);

#endif /* TP1_H_ */
