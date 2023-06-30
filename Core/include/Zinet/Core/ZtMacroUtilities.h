#pragma once

#include "Zinet/Core/ZtCore.h"

#define ZINET_CONCAT2(A, B) A ## B
#define ZINET_CONCAT3(A, B, C) ZINET_CONCAT2(A, B) ## C
#define ZINET_CONCAT4(A, B, C, D) ZINET_CONCAT3(A, B, C) ## D