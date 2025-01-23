#include "filesystem.h"
#include <SPIFFS.h>
void setupFILESYSTEM() {
    String data = "{\"disablesleep\":false, \"wifi\": {\"network\": {\"ssid\":\"IU PublicNet\", \"password\":\"\"}, \"enabled\":false}}";
    if (SPIFFS.exists("/setting.json")) {
        Serial.println("File exists!");
        File file = SPIFFS.open("/setting.json", FILE_READ);
        if (file) {
            size_t fileSize = file.size(); // Get file size
            Serial.printf("File size: %lu bytes\n", fileSize);
            if (fileSize == 0) {
                Serial.printf("File %s is empty. Writing data...\n", "settings.json");
                file.close();
                File file = SPIFFS.open("/setting.json", FILE_WRITE);
                file.println(data);
                file.close();
            }
        }
    } else {
        Serial.println("File does not exist. Creating file and adding data...");
        
        // Create and write to the file
        File file = SPIFFS.open("/setting.json", FILE_WRITE);
        if (!file) {
        Serial.println("Failed to create file");
        } else {
            file.println(data);
            Serial.println("File created and data written successfully.");
        file.close();
        }
    }
    data = "[{\"ssid\":\"IU PublicNet\",\"password\":\"\"}]";
    if (SPIFFS.exists("/wifi-network.json")) {
        Serial.println("File exists!");
        File file = SPIFFS.open("/wifi-network.json", FILE_READ);
        if (file) {
            size_t fileSize = file.size(); // Get file size
            Serial.printf("File size: %lu bytes\n", fileSize);
            if (fileSize < 5) {
                Serial.printf("File %s is empty. Writing data...\n", "wifi-network.json");
                file.close();
                File file = SPIFFS.open("/wifi-network.json", FILE_WRITE);
                file.println(data);
                file.close();
            }
        }
    } else {
        Serial.println("File does not exist. Creating file and adding data...");
        
        // Create and write to the file
        File file = SPIFFS.open("/wifi-network.json", FILE_WRITE);
        if (!file) {
        Serial.println("Failed to create file");
        } else {
            file.println(data);
            Serial.println("File created and data written successfully.");
        file.close();
        }
    }
    /*data = "const label = lv_label_create(appTile);"
    "lv_obj_set_align(label, LV_ALIGN_CENTER);"
    "lv_label_set_text(label, \"Hello from JavaScript!\");"
    "const btn = lv_btn_create(appTile);"
    "lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);";*/
    data = "const btn = lv_btn_create(appTile);\n"
    "lv_obj_set_align(btn, LV_ALIGN_CENTER);\n"
    "btnLabel = lv_label_create(btn);\n"
    "lv_label_set_text(btnLabel, \"gooooooo\");\n"
    "var i, n, e,res,content,s;\n"
    "lv_obj_add_event_cb(btn,\n"
    "   function (e) {\n"
    "       res = http(\"GET\",\"http://10.20.75.198:8080/all\");\n"
    "       print(res.body + \"\\n\");\n"
    "       s = res.body.split(\",\")\n"
    "       i=0;\n"
    "       for (i, n = s.length; i < n; i++) {\n"
    "           e = s[i];\n"
    "           print(\"load \"+e);\n"
    "           content = http(\"GET\",\"http://10.20.75.198:8080/s/\"+e);\n"
    "           fs.writeFile(\"/app/\"+e,content);\n"
    "       }\n"
    "       loadapps();\n"
    "       vibrate();\n"
    "   },\n"
    "   LV_EVENT_CLICKED,\n"
    "   null\n"
    ");\n";


    if (SPIFFS.exists("/app/load.js")) {
        Serial.println("File exists!");
        File file = SPIFFS.open("/app/load.js", FILE_READ);
        if (file) {
            size_t fileSize = file.size(); // Get file size
            Serial.printf("File size: %lu bytes\n", fileSize);
            if (fileSize < 50000) {
                Serial.printf("File %s is empty. Writing data...\n", "/app/load.js");
                file.close();
                File file = SPIFFS.open("/app/load.js", FILE_WRITE);
                file.println(data);
                file.close();
            }
        }
    } else {
        Serial.println("File does not exist. Creating file and adding data...");
        
        // Create and write to the file
        File file = SPIFFS.open("/app/load.js", FILE_WRITE);
        if (!file) {
        Serial.println("Failed to create file");
        } else {
            file.println(data);
            Serial.println("File created and data written successfully.");
        file.close();
        }
    }
}