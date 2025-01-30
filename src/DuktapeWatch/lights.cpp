#include <LilyGoLib.h>
#include <duktape.h>
#include "ui.h"
#include <HTTPClient.h>
static lv_obj_t *list;
static void loadLights();
static void lights() {
    lv_obj_t *appsTile = lv_tileview_get_tile_act(tileview);
    list = lv_obj_create(appsTile);
	lv_obj_set_style_border_side(list, LV_BORDER_SIDE_NONE, LV_PART_MAIN);
	lv_obj_set_style_radius(list, 0, LV_PART_MAIN);
	lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));
	lv_obj_set_flex_flow(list, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_align(list, LV_ALIGN_CENTER, 0, 0);
	loadLights();

}
static duk_ret_t js_lights(duk_context *ctx) {
    lights();
    return 1;
}
static void createLight(const char *name);
static void loadLights()
{
	createLight("on");
    createLight("off");
}

static void createLight(const char *name)
{
    if (name == nullptr) {
        Serial.println("Error: lightName is null!");
        return;
    }
	lv_obj_t *btn = lv_btn_create(list);
	lv_obj_set_size(btn, 100, 100);
	lv_obj_set_style_bg_color(btn, lv_color_hex(0x0000ff), 0);

	lv_obj_t *label = lv_label_create(btn);
	lv_label_set_text(label, name);
	lv_obj_center(label);

	lv_obj_clear_flag(btn, LV_OBJ_FLAG_PRESS_LOCK);
	lv_obj_add_event_cb(
		btn,
		[](lv_event_t *e) {
            watch.setWaveform(0, 14);
	        watch.run();
            HTTPClient http;
            auto name = (String *)lv_event_get_user_data(e);
	        http.begin("https://lights.sawicz.com/api/scenes");
            http.sendRequest("PUT", "{\"id\":\"" + *name + "\",\"action\":\"activate\"}");
            http.end();
            
		},
		LV_EVENT_CLICKED,
		new String(name)
	);
}
void duktape_watch_install_lights(duk_context *ctx) {
	duk_push_c_function(ctx, js_lights, 0);
	duk_put_global_string(ctx, "setupLights");
}

