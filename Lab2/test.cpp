#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

#ifndef WIN32
  #define popen _popen
  #define pclose _pclose
#endif

using namespace std;

/**
 * @brief Выполнить программу в 
 * 
 * @param command команда с параметрами
 * @return string вывод программы
 */
string exec(string command) {
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

int main() {
   string ls = exec("ls");
   cout << ls;
}