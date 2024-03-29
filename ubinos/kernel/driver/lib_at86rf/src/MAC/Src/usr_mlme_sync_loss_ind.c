/**
 * @file usr_mlme_sync_loss_ind.c
 *
 * @brief This file contains user call back function for
 * MLME-SYNC-LOSS.indication
 *
 * $Id: usr_mlme_sync_loss_ind.c,v 1.2 2010-07-30 16:38:38 slb Exp $
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

#if (MAC_SYNC_LOSS_INDICATION == 1)

/* === Macros ============================================================== */


/* === Globals ============================================================= */


/* === Prototypes ========================================================== */


/* === Implementation ====================================================== */

void usr_mlme_sync_loss_ind(uint8_t LossReason,
                            uint16_t PANId,
                            uint8_t LogicalChannel,
                            uint8_t ChannelPage)
{
    /* Keep compiler happy. */
    LossReason = LossReason;
    PANId = PANId;
    LogicalChannel = LogicalChannel;
    ChannelPage = ChannelPage;
}

#endif /* (MAC_SYNC_LOSS_INDICATION == 1) */

/* EOF */
