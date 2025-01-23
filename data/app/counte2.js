counter = 0;

label = lv_label_create(appTile);
lv_obj_set_align(label, LV_ALIGN_CENTER);
lv_label_set_text(label, "ITS 2: 0");

btn = lv_btn_create(appTile);
lv_obj_set_align(btn, LV_ALIGN_BOTTOM_MID);

btnLabel = lv_label_create(btn);
lv_label_set_text(btnLabel, "Increment");
lv_obj_add_event_cb(btn,
    function (e) {
        counter++;
        lv_label_set_text(label, "Counter: " + counter);
    },
    LV_EVENT_CLICKED,
    null
);