#pragma once

#include <cstddef>
#include "gen/enums.h"

#define YYLTYPE_IS_DECLARED
typedef struct yyltype {
  int first_line;
  size_t offset;
  size_t first_column;
  int last_line;
  size_t last_column;
} YYLTYPE;

struct Condition
{

};
