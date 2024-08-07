#pragma once

#include "incl.hpp"

namespace gl {
	uint32_t CRC_table[256];
	_iobuf* logfile;
	std::vector<std::pair<std::any, int_fast64_t>> objects;
}
