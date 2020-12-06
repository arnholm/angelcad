#include "recursive_file_search.h"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

// https://stackoverflow.com/questions/18620348/iterating-files-with-boostfilesystem-3-0
// https://stackoverflow.com/questions/3300419/file-name-matching-with-wildcard#3301284

namespace fs = boost::filesystem;

void EscapeRegex(std::string &regex)
{
    boost::replace_all(regex, "\\", "\\\\");
    boost::replace_all(regex, "^", "\\^");
    boost::replace_all(regex, ".", "\\.");
    boost::replace_all(regex, "$", "\\$");
    boost::replace_all(regex, "|", "\\|");
    boost::replace_all(regex, "(", "\\(");
    boost::replace_all(regex, ")", "\\)");
    boost::replace_all(regex, "{", "\\{");
    boost::replace_all(regex, "{", "\\}");
    boost::replace_all(regex, "[", "\\[");
    boost::replace_all(regex, "]", "\\]");
    boost::replace_all(regex, "*", "\\*");
    boost::replace_all(regex, "+", "\\+");
    boost::replace_all(regex, "?", "\\?");
    boost::replace_all(regex, "/", "\\/");
}

size_t path_levels(const fs::path& f)
{
   size_t levels = 0;
   for (fs::path::iterator it(f.begin()), it_end(f.end()); it != it_end; ++it) levels++;
   return levels;
}

std::vector<std::string> recursive_file_search(const std::string& root_path, const std::string& file_mask, int max_recurse)
{
   // create a regex_mask from the file mask
   std::string regex_mask(file_mask);
   EscapeRegex(regex_mask);
   // Convert chars '*?' back to their regex equivalents
   boost::replace_all(regex_mask, "\\?", ".");
   boost::replace_all(regex_mask, "\\*", ".*");
   const boost::regex pattern(regex_mask);

   // establish the number of directory levels in the root path
   fs::path f(root_path);
   if (fs::is_directory(f)) {
      char c = root_path[root_path.length()-1];
      if(!(c=='/' || c=='\\')) f = fs::path(root_path+'/');
   }
   size_t lp = path_levels(f);

   std::vector<std::string> result;
   if (fs::is_directory(f)) {

      for (fs::recursive_directory_iterator it(f), eit; it != eit; ++it) {

         if (!fs::is_directory(it->path())) {

            // check recursion level of this file relative to root_path
            bool process_file = true;
            if(max_recurse >= 0) {
               size_t level = path_levels(it->path()) - lp;
               if(level > max_recurse) process_file = false;
            }

            // Skip file if too low level or no name match
            boost::smatch what;
            if(process_file && boost::regex_match( it->path().filename().string(), what, pattern ) ) {
               std::string path = it->path().string();
               std::replace(path.begin(),path.end(), '\\', '/');
               result.push_back(path);
            }
         }
      }
   }
   else {
      // Skip if no name match
      boost::smatch what;
      if(boost::regex_match(f.filename().string(), what, pattern ) ) {
         result.push_back(f.string());
      }
   }
   return std::move(result);
}
