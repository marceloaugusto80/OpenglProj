#pragma once

#define VECTOR_REMOVE(VECTOR, ITEM) \
VECTOR.erase(std::remove(VECTOR.begin(), VECTOR.end(), ITEM), VECTOR.end())