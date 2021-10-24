#pragma once

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void dfs(Graph *G, uint32_t v, Path *curr, char *cities[], Path *shortest, int *counter,
    FILE *outfile, bool verbose);
