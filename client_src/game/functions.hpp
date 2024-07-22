#pragma once

#include "incl.hpp"
#include "init.hpp"
#include "nodes/object.hpp"

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

void render(SDL_Renderer* rend, SDL_Texture* txtr, ...) {
	va_list args;
	va_start(args, first_txtr);
	SDL_Texture* txtr = first_txtr;
	while (txtr) {
		SDL_RenderCopy(rend, txtr, NULL, NULL);
		txtr = va_arg(args, SDL_Texture*);
	}
	va_end(args);
}

object* create_object(SDL_Renderer* rend, uint_fast64_t z_order) {
	return new object(rend, z_order);
}

void destroy(object* ptr) {
	if (ptr != nullptr) delete ptr;
}
