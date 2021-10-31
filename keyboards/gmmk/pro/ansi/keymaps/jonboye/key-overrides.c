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

//Aqui se define el modificador, la tecla con la que se activa la funcion y el resultado de ambos
const key_override_t shiftComm_override = ko_make_basic(MOD_MASK_SHIFT, ES_COMM, ES_LABK);

const key_override_t shift2_override = ko_make_basic(MOD_MASK_SHIFT, ES_2, ALGR(ES_2));   //Aqui se especifican un Shift, un 2, y su resultado (@)
const key_override_t shift3_override = ko_make_basic(MOD_MASK_SHIFT, ES_3, ALGR(ES_3));

const key_override_t shift6_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, S(ES_GRV));
const key_override_t shift7_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, S(ES_6));
const key_override_t shift8_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, S(ES_PLUS));
const key_override_t shift9_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, S(ES_8));
const key_override_t shift0_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, S(ES_9));
const key_override_t shiftDot_override = ko_make_basic(MOD_MASK_SHIFT, ES_DOT, S(ES_LABK));

const key_override_t shiftEql_override = ko_make_basic(MOD_MASK_SHIFT, S(ES_0), ES_PLUS);

const key_override_t shiftLbrc_override = ko_make_basic(MOD_MASK_SHIFT, ALGR(ES_GRV), ALGR(ES_ACUT));
const key_override_t shiftRbrc_override = ko_make_basic(MOD_MASK_SHIFT, ALGR(ES_PLUS), ALGR(ES_CCED));
const key_override_t shiftBsls_override = ko_make_basic(MOD_MASK_SHIFT, ALGR(ES_MORD), ALGR(ES_1));


const key_override_t shiftQuot_override = ko_make_basic(MOD_MASK_SHIFT, ES_ACUT, S(ES_2));
const key_override_t shiftGrv_override = ko_make_basic(MOD_MASK_SHIFT, ES_QUOT, ES_MORD);


const key_override_t shiftSlsh_override = ko_make_basic(MOD_MASK_SHIFT, S(ES_7), S(ES_QUOT));
const key_override_t shiftScln_override = ko_make_basic(MOD_MASK_SHIFT, S(KC_COMM), S(KC_DOT));

// This globally defines all key overrides to be used
//Aqui se especifica que overrides se van a usar en el keymap
const key_override_t **key_overrides = (const key_override_t *[]){

    &shiftGrv_override,

    &shift2_override,
    &shift3_override,

    &shift6_override,
    &shift7_override,
    &shift8_override,
    &shift9_override,
    &shift0_override,
    &shiftDot_override,

    &shiftEql_override,

    &shiftLbrc_override,
    &shiftRbrc_override,
    &shiftBsls_override,


    &shiftQuot_override,
    &shiftComm_override,

    &shiftSlsh_override,
    &shiftScln_override,

    NULL // Null terminate the array of overrides!
};
