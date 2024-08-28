#ifndef JSON_H
#define JSON_H

#include "j/parson.h"

enum JSONFILE {
	PROPS,
	WL,
	BL,
	PSW
};

struct properties {
	JSON_Value* json = json_parse_file(".. /properties.json");
	JSON_Object* root = json_value_get_object(json);

	JSON_Value* name = json_object_get_string(root, "name");
	JSON_Object* players = json_object_get_object(root, "players");
		JSON_Value* p_total = json_object_get_number(players, "total");
		JSON_Value* p_per_world = json_object_get_number(players, "per_world");
	JSON_Object* rn_enx = json_object_get_object(root, "random_encounters");
		JSON_Value* re_enable = json_object_get_boolean(players, "enable");
		JSON_Value* re_chance = json_object_get_number(players, "chance");
		JSON_Value* re_delay = json_object_get_number(players, "delay_ts");
	JSON_Value* tps = json_object_get_number(root, "ticks_per_second");
	JSON_Value* user_skins = json_object_get_boolean(root, "user_skins");
	JSON_Value* psw = json_object_get_boolean(root, "require_password");
	JSON_Value* filter = json_object_get_boolean(root, "word_filter");
	JSON_Value* b_list = json_object_get_boolean(root, "blacklist");
	JSON_Value* w_list = json_object_get_boolean(root, "whitelist");
};

void parse_json(JSONFILE file) {
	char* error = NULL;
	switch (file) {
	case PROPS:
	case WL:
	case BL:
	case PSW:
	default:
		break;
	}

CLEANUP:
	if (error != NULL) {
		printf("[Error] %s\n", error);
	}
	json_value_free(root_value);
	json_value_free()
}
void json_write(const char* json, const char* value) {
	return;
}

#endif // JSON_H