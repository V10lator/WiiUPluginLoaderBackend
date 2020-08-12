/****************************************************************************
 * Copyright (C) 2018-2019 Maschell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "dynamic_linking_defines.h"
#include "relocation_defines.h"
#include "replacement_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXIMUM_PLUGIN_SECTION_LENGTH                       10
#define MAXIMUM_PLUGIN_SECTION_NAME_LENGTH                  20

#define MAXIMUM_PLUGIN_PATH_NAME_LENGTH                     256
#define MAXIMUM_PLUGIN_NAME_LENGTH                          51
#define MAXIMUM_PLUGIN_DESCRIPTION_LENGTH                   255
#define MAXIMUM_PLUGIN_META_FIELD_LENGTH                    51

#define DYN_LINK_RELOCATION_LIST_LENGTH                     500

#define MAXIMUM_HOOKS_PER_PLUGIN                        25
#define MAXIMUM_FUNCTION_PER_PLUGIN                     100

struct plugin_section_info_t {
    char                            name[MAXIMUM_PLUGIN_SECTION_NAME_LENGTH] = "";
    uint32_t                        addr;
    uint32_t                        size;
};

struct plugin_meta_info_t {
    char                            name[MAXIMUM_PLUGIN_META_FIELD_LENGTH] = "";
    char                            author[MAXIMUM_PLUGIN_META_FIELD_LENGTH] = "";
    char                            version[MAXIMUM_PLUGIN_META_FIELD_LENGTH] = "";
    char                            license[MAXIMUM_PLUGIN_META_FIELD_LENGTH] = "";
    char                            buildTimestamp[MAXIMUM_PLUGIN_META_FIELD_LENGTH] = "";
    char                            descripion[MAXIMUM_PLUGIN_DESCRIPTION_LENGTH] = "";
    uint32_t                        size;
};

struct plugin_info_t {
    dyn_linking_relocation_entry_t  linking_entries[DYN_LINK_RELOCATION_LIST_LENGTH];
    plugin_section_info_t           sectionInfos[MAXIMUM_PLUGIN_SECTION_LENGTH];
    uint32_t                        number_used_functions;                          // Number of used function. Maximum is MAXIMUM_FUNCTION_PER_PLUGIN
    replacement_data_function_t     functions[MAXIMUM_FUNCTION_PER_PLUGIN];         // Replacement information for each function.
    uint32_t                        number_used_hooks;                              // Number of used hooks. Maximum is MAXIMUM_HOOKS_PER_PLUGIN
    replacement_data_hook_t         hooks[MAXIMUM_HOOKS_PER_PLUGIN];                // Replacement information for each function.
    uint8_t                         trampolinId;
};

struct plugin_data_t {
    char *                          buffer = NULL;
    size_t                          bufferLength = 0;
    int                             memoryType = 0;
    int                             heapHandle = 0;
};

struct plugin_information_single_t {
    plugin_meta_info_t              meta;
    plugin_info_t                   info;
    plugin_data_t                   data;
    int32_t                         priority;                                       // Priority of this plugin

};

#define MAXIMUM_PLUGINS                                     32

struct plugin_information_t {
    int32_t                         number_used_plugins = 0;                        // Number of used plugins. Maximum is MAXIMUM_PLUGINS
    plugin_information_single_t     plugin_data[MAXIMUM_PLUGINS];
    relocation_trampolin_entry_t    trampolines[DYN_LINK_TRAMPOLIN_LIST_LENGTH];
    dyn_linking_relocation_data_t   linking_data;                                   // RPL and function name list
};

#ifdef __cplusplus
}
#endif
