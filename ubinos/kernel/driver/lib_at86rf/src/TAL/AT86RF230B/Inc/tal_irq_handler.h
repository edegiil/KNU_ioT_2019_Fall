/**
 * @file tal_irq_handler.h
 *
 * @brief This header file contains the interrupt handling definitions
 *
 * $Id: tal_irq_handler.h,v 1.2 2010-07-30 16:58:57 slb Exp $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

/* Prevent double inclusion */
#ifndef TAL_IRQ_HANDLER_H
#define TAL_IRQ_HANDLER_H

#include "../../../../ubiconfig.h"

/* === INCLUDES ============================================================ */


/* === EXTERNALS =========================================================== */


/* === TYPES =============================================================== */


/* === MACROS ============================================================== */


/* === PROTOTYPES ========================================================== */

#ifdef __cplusplus
extern "C" {
#endif


void trx_irq_handler_cb(void);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* TAL_IRQ_HANDLER_H */

/* EOF */
