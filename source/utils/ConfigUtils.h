#pragma once

#include <gx2/enum.h>

struct StoredBuffer {
    void *buffer;
    uint32_t buffer_size;
    uint32_t mode;
    GX2SurfaceFormat surface_format;
    GX2BufferingMode buffering_mode;
};

class ConfigUtils {
public:
    static void openConfigMenu();

private:
    static void displayMenu();
};