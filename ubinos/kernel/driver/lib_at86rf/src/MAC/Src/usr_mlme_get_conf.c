/**
 * @file usr_mlme_get_conf.c
 *
 * @brief This file contains user call back function for MLME-GET.confirm.
 *
 * $Id: usr_mlme_get_conf.c,v 1.2 2010-07-30 16:38:38 slb Exp $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

#include "../../../ubiconfig.h"

/* === Includes ============================================================= */

#include <stdint.h>
#include <stdbool.h>
#include "../Inc/mac_api.h"

#if (MAC_GET_SUPPORT == 1)

/* === Macros ============================================================== */

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */

void usr_mlme_get_conf(uint8_t status,
                       uint8_t PIBAttribute,
                       void *PIBAttributeValue)
{
    /* Keep compiler happy. */
    status = status;
    PIBAttribute = PIBAttribute;
    PIBAttributeValue = PIBAttributeValue;
}
#endif  /* (MAC_GET_SUPPORT == 1) */

/* EOF */
