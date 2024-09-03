#ifndef UTILITY_H
#define UTILITY_H

#include "incl.h"
#include <parson.c>

const char* cmd[] = {
	"~quit",
	"~restart",
	"~kick",
	"~ban",
	"~plist",
	"~tp",
	"~~silent",
	"~~reason"
};
void THROW(void) {
}
void CATCH(void) {
}
void stacktrace(const char* module, const char* msg, ...) {
	time_t get_time = time(NULL);
	struct tm* timeinfo;
	char current_time[80];
	timeinfo = localtime(&get_time);
	strftime(current_time, sizeof(current_time), "%Y-%m-%d // %H:%M:%S", timeinfo);
	fprintf(logfile, "[%s] [%s] ", current_time, module);
	va_list args;
	va_start(args, msg);
	vfprintf(logfile, msg, args);
	va_end(args);
	fputc('\n', logfile);
}
void get_properties(void) {
	JSON_Value* json = json_parse_file(".. /properties.json");
	JSON_Object* root = json_value_get_object(json);

	JSON_Value* name = json_object_get_string(root, "name");
	JSON_Object* players = json_object_get_object(root, "players");
		int p_total = json_object_get_number(players, "total");
		int p_per_world = json_object_get_number(players, "per_world");
	JSON_Object* rn_enx = json_object_get_object(root, "random_encounters");
		bool re_enable = json_object_get_boolean(players, "enable");
		double re_chance = json_object_get_number(players, "chance");
		int re_delay = json_object_get_number(players, "delay_ts");
	int tps = json_object_get_number(root, "ticks_per_second");
	bool user_skins = json_object_get_boolean(root, "user_skins");
	bool psw = json_object_get_boolean(root, "require_password");
	bool filter = json_object_get_boolean(root, "word_filter");
	bool b_list = json_object_get_boolean(root, "blacklist");
	bool w_list = json_object_get_boolean(root, "whitelist");
	int afk = json_object_get_number(root, "timeout");
	bool logs = json_object_get_boolean(root, "logs");
}
void json_write(const char* json, const char* value) {
	return;
}
enum unicodes {
	latin,
	cyrillic,
	cjk
};

// Function to determine the Unicode block
int get_font(uint32_t codepoint) {
	if (codepoint >= 0x0000 && codepoint <= 0x007F) {
		return latin;
	}
	else if (codepoint >= 0x0400 && codepoint <= 0x04FF) {
		return cyrillic;
	}
	else if (codepoint >= 0x4E00 && codepoint <= 0x9FFF) {
		return cjk;
	}
	return latin;
}

#endif // UTILITY_H