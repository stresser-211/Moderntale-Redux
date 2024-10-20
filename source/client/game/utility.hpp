﻿#pragma once

#include "incl.hpp"

template <typename T> concept is_number = std::is_arithmetic_v<T> && !std::is_same_v<bool, T>;
template <typename T> concept is_positive = is_number<T> && requires(T a) {
	std::cmp_greater(a, 0u);
};

constexpr inline int_fast64_t operator""Z(unsigned long long i) {
	return static_cast<int_fast64_t>(i);
}
inline void ERROR_CRIT(const char* msg) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "(see stacktrace.log for details)", msg, NULL);
};
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
	fputc('\n', gl::logfile);
}
int init(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		stacktrace(module::core, "SDL initialisation failed: %s.", SDL_GetError());
		throw INITIALISATION;
	}
	if (IMG_Init(IMG_INIT_PNG) == -1) {
		stacktrace(module::core, "SDL_image initialisation failed: %s.", IMG_GetError());
		throw INITIALISATION;
	}
	if (Mix_Init(MIX_INIT_OGG) == -1) {
		stacktrace(module::core, "SDL_mixer initialisation failed: %s.", Mix_GetError());
		throw INITIALISATION;
	}
	if (TTF_Init() == -1) {
		stacktrace(module::core, "SDL_ttf initialisation failed: %s.", TTF_GetError());
		throw INITIALISATION;
	}
	return SUCCESS;
}
uint32_t get_CRC(_iobuf* file) {
	uint32_t CRC = 0xFFFFFFFF;
	unsigned char buffer[4096];
	size_t bytes_read;
	while ((bytes_read = fread(buffer, 1, 4096, file)) > 0) {
		for (size_t i = 0; i < bytes_read; i++) {
			uint8_t byte = buffer[i];
			CRC = (CRC >> 8) ^ gl::CRC_table[(CRC ^ byte) & 0xFF];
		}
	}
	fclose(file);
	return CRC ^ 0xFFFFFFFF;
}
int verify_integrity(void) {
	_iobuf* check;
	uint32_t CRC_check;
	using namespace path;
	for (auto& iter : engine) {
		check = fopen(iter.first, "r");
		if (!check) {
			stacktrace(module::core, "\"%s\" not found.", iter.first);
			throw MISSING_ENGINE_FILE;
		}
		CRC_check = get_CRC(check);
		if (CRC_check != iter.second) {
			stacktrace(module::core, "\"%s\" is corrupted. (CRC: \"%X\", \"%X\" expected)", iter.first, CRC_check, iter.second);
			throw INTEGRITY_VIOLATED;
		};
		stacktrace(module::ios, "Reading \"%s\": the file is fine.", iter.first);
		fclose(check);
	}
	return SUCCESS;
}
namespace random {
	[[nodiscard]] int32_t int32(void) {
		std::random_device rd;
		std::mt19937_64 mt(rd());
		return mt();
	}
};