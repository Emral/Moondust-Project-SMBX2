/*****************************************************************
     Automatically generated by _common/res_generator utility
     Suggested to DONT EDIT THIS
     Edit the _common/res_generator/res_generator.cpp instead
 *****************************************************************/

#include <stdio.h>
#include <string>
#include "resource_data.h"
#include "resource.h"

void RES_getMem(const char* file, char* &mem, size_t &size)
{
   std::unordered_map<std::string, FileEntry>::iterator f = filesMap.find(file);
   if(f == filesMap.end())
       throw("Resource doesn't exists!");

   FileEntry& e = f->second;
   mem = const_cast<char*>(reinterpret_cast<const char*>(e.array));
   size = e.size;
}

