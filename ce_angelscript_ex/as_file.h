#ifndef AS_FILE_H
#define AS_FILE_H

#include <string>

class as_file {
public:
   static bool file_exists(const std::string& path);
   static bool dir_exists(const std::string& path);
};

#endif // AS_FILE_H
