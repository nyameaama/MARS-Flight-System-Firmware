#pragma once

#include <lvgl/lvgl.h>
#include <screen.h>
#include <tock.h>
#include <touch.h>

int lvgl_driver_init(int buffer_size);
void lvgl_driver_event(int mills);
