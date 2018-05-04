#ifndef PARSING_H
#define PARSING_H

#include "defs.h"
#include "types.h"
#include "createcmd.h"
#include "utils.h"

struct cmd* parse_line(char* b, int s);

#endif // PARSING_H
