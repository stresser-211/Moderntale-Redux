#pragma once

#include "incl.hpp"
#include "functions.hpp"

void stacktrace(const char* module, const char* msg, ...) {
	time_t get_time = time(NULL);
	struct tm* timeinfo;
	char current_time[80];
	timeinfo = localtime(&get_time);
	strftime(current_time, sizeof(current_time), "%Y-%m-%d // %H:%M:%S", timeinfo);
	fprintf(gl::logfile, "[%s] [%s] ", current_time, module);
	va_list args;
	va_start(args, msg);
	vfprintf(gl::logfile, msg, args);
	va_end(args);
	fprintf(gl::logfile, "\n");
}
int verify_integrity(void) {
	_iobuf* check;
	uint32_t CRC_check;
	using namespace path;
	for (auto& iter : engine) {
		check = fopen(iter.first, "r");
		if (!check) {
			stacktrace(module::error, "\"%s\" not found.", iter.first);
			throw MISSING_ENGINE_FILE;
		}
		CRC_check = get_CRC(check);
		if (CRC_check != iter.second) {
			stacktrace(module::error, "\"%s\" is corrupted. (CRC: %X, expected %X)", iter.first, CRC_check, iter.second);
			throw INTEGRITY_VIOLATED;
		};
		stacktrace(module::ios, "Reading \"%s\": the file is fine.", iter.first);
		fclose(check);
	}
	return SUCCESS;
}
