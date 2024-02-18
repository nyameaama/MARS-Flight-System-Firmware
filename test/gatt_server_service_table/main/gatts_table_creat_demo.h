/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Attributes State Machine */
enum
{
    IDX_SVC,
    IDX_CHAR_1,
    IDX_CHAR_VAL_1,

    IDX_CHAR_2,
    IDX_CHAR_VAL_2,

    IDX_CHAR_3,
    IDX_CHAR_VAL_3,

    IDX_CHAR_4,
    IDX_CHAR_VAL_4,

    IDX_CHAR_5,
    IDX_CHAR_VAL_5,

    IDX_CHAR_6,
    IDX_CHAR_VAL_6,

    IDX_CHAR_7,
    IDX_CHAR_VAL_7,

    IDX_CHAR_8,
    IDX_CHAR_VAL_8,

    IDX_CHAR_9,
    IDX_CHAR_VAL_9,

    IDX_CHAR_10,
    IDX_CHAR_VAL_10,

    IDX_CHAR_11,
    IDX_CHAR_VAL_11,

    IDX_CHAR_12,
    IDX_CHAR_VAL_12,

    IDX_CHAR_13,
    IDX_CHAR_VAL_13,

    IDX_CHAR_14,
    IDX_CHAR_VAL_14,

    IDX_CHAR_15,
    IDX_CHAR_VAL_15,

    IDX_CHAR_16,
    IDX_CHAR_VAL_16,

    IDX_CHAR_17,
    IDX_CHAR_VAL_17,

    IDX_CHAR_18,
    IDX_CHAR_VAL_18,

    IDX_CHAR_19,
    IDX_CHAR_VAL_19,

    IDX_CHAR_20,
    IDX_CHAR_VAL_20,
    
    HRS_IDX_NB,
};
