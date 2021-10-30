/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// NORMAL SHIFT STATUS
// Sends (kc1) if no shift is held, (shift+kc2) if shift is held.
#define SHIFT_NORM(kc1, kc2) \
if (record->event.pressed) { \
  if (get_mods() & MOD_MASK_SHIFT) { \
    unregister_code(kc2); \
    register_code(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} return false;

// Never shifted
// Sends (kc1) if no shift is held, (kc2) if shift is held
#define SHIFT_NO(kc1, kc2) \
if (record->event.pressed) { \
  if (get_mods() & MOD_MASK_SHIFT) { \
    uint8_t mods_temp = get_mods(); \
    del_mods(MOD_MASK_SHIFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    set_mods(mods_temp); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} return false;


// Inverted shift status
// Sends (shift+kc1) if no shift is held, (kc2) if shift is held
#define SHIFT_SWITCH(kc1, kc2) \
if (record->event.pressed) { \
  if (get_mods() & MOD_MASK_SHIFT) { \
    uint8_t mods_temp = get_mods(); \
    del_mods(MOD_MASK_SHIFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_mods(mods_temp); \
  } else if (get_mods() & MOD_MASK_SHIFT) { \
    unregister_code(kc1); \
    register_code(kc1); \
    return false; \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} return false;
