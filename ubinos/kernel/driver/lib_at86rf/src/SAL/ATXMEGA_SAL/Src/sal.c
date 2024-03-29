/**
 * @file sal.c
 *
 * @brief Low-level crypto API for an AES unit implemented in ATxmega MCUs .
 *
 * This file implements the low-level crypto API based on an AES unit
 * implemented in an Atmel's ATxmega MCU family.
 *
 * $Id: sal.c,v 1.3 2010-08-04 02:16:00 slb Exp $
 *
 */
/**
 * @author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2009, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

#include "../../../../ubiconfig.h"

#ifdef ENABLE_STB

/* === Includes ============================================================ */

#include "../../Inc/sal_types.h"
#if (SAL_TYPE == ATXMEGA_SAL)
#include <stdio.h>
#include <string.h>
#include "../../../PAL/Inc/pal.h"
#include "../../Inc/sal.h"

/* === Macros ============================================================== */

/* Values for SR_AES_DIR */
#define AES_DIR_VOID      (AES_DIR_ENCRYPT + AES_DIR_DECRYPT + 1)
                                /* Must be different from both summands */

/* Compute absolute value for subregister 'SUB' with value 'val' */
#define COMP_SR(SUB, val)       (((val) << SUB ## _bp) & SUB ## _bm)

/* === Types =============================================================== */


/* === Data ============================================================= */

/* True if decryption key is actual and was computed. */
static bool dec_initialized = false;
/* Encryption mode with flags. */
static uint8_t mode_byte;
/* Last value of "dir" parameter in sal_aes_setup(). */
static uint8_t last_dir = AES_DIR_VOID;
/* Actual encryption key. */
static uint8_t enc_key[AES_KEYSIZE];
/* Actual decryption key (valid if last_dir == AES_DIR_DECRYPT). */
static uint8_t dec_key[AES_KEYSIZE];
/* Pointer to actual key. */
static uint8_t *keyp;

/* === Implementation ====================================================== */

/**
 * @brief Initialization of SAL.
 *
 * This functions initializes the SAL.
 */
void sal_init(void)
{
    /* reset AES unit - only a precaution */
    AES_CTRL = COMP_SR(AES_RESET, 1);
}



/**
 * @brief Setup AES unit
 *
 * This function performs the following tasks as part of the setup of the
 * AES unit: key initialization, set encryption direction and encryption mode.
 *
 * In general, the contents of SRAM buffer is destroyed. When using
 * sal_aes_wrrd(), sal_aes_read() needs to be called in order to get the result
 * of the last AES operation before you may call sal_aes_setup() again.
 *
 * @param[in] key AES key or NULL (NULL: use last key)
 * @param[in] enc_mode  AES_MODE_ECB or AES_MODE_CBC
 * @param[in] dir AES_DIR_ENCRYPT or AES_DIR_DECRYPT
 *
 * @return  False if some parameter was illegal, true else
 */
bool sal_aes_setup(uint8_t *key,
                   uint8_t enc_mode,
                   uint8_t dir)
{
    uint8_t i;

    /* Init mode_byte: AES low-level interrupt and autostart enabled */

    mode_byte = COMP_SR(AES_INTLVL0, 1) | COMP_SR(AES_AUTO, 1);

    if (key != NULL)
    {
        /* Setup for new key. */
        dec_initialized = false;

        last_dir = AES_DIR_VOID;

        /* Save key for later use after decryption or sleep. */
        memcpy(enc_key, key, AES_KEYSIZE);

        keyp = enc_key;
    }

    /* Set encryption direction. */
    switch(dir)
    {
        case AES_DIR_ENCRYPT:
            if (last_dir == AES_DIR_DECRYPT)
            {
                /*
                 * If the last operation was decryption, the encryption
                 * key must be stored in enc_key, so re-initialize it.
                 */
                keyp = enc_key;
            }
            break;

        case AES_DIR_DECRYPT:
            if (last_dir != AES_DIR_DECRYPT)
            {
                if (!dec_initialized)
                {
                    uint8_t dummy[AES_BLOCKSIZE];

                    /* Compute decryption key. */

                    /* Dummy ECB encryption. */
                    AES_CTRL = mode_byte;

                    keyp = enc_key;
                    sal_aes_exec(dummy);

                    /* Read last round key. */
                    for(i = 0; i < AES_BLOCKSIZE; ++i)
                    {
                        dec_key[i] = AES_KEY;
                    }

                    dec_initialized = true;
                }
                keyp = dec_key;
            }
            break;

        default:
            return false;
    }

    last_dir = dir;

    /* Set encryption mode and direction. */
    switch(enc_mode)
    {
        case AES_MODE_ECB:
        case AES_MODE_CBC:
            {
                uint8_t xorflag;
                uint8_t dirflag = 0;

                xorflag = (enc_mode == AES_MODE_CBC);
                dirflag = (dir == AES_DIR_DECRYPT);

                mode_byte |=
                    COMP_SR(AES_XOR, xorflag) | COMP_SR(AES_DECRYPT, dirflag);
                AES_CTRL = mode_byte;
            }
            break;

        default:
            return (false);
    }

    return (true);
}



/**
 * @brief Re-inits key and state after a sleep or chip reset
 *
 * This function is void for ATxmega since the key must be
 * re-initialized before every block encryption anyway.
 */

void sal_aes_restart(void)
{
    /* Nothing to be done for ATxmega */
}



/**
 * @brief En/decrypt one AES block.
 *
 * The function returns after the AES operation is finished.
 *
 * @param[in]  data  AES block to be en/decrypted
 */
void sal_aes_exec(uint8_t *data)
{
    uint8_t i;
    uint8_t *pkeyp;

    /* Initialize key in encryption unit. */
    for(pkeyp = keyp, i = 0; i < AES_BLOCKSIZE; ++i)
    {
        AES_KEY = *pkeyp++;
    }

    /* Store data to encryption to encryption unit; autostart. */
    for(i = 0; i < AES_BLOCKSIZE; ++i)
    {
        AES_STATE = *data++;
    }

    /*
     * Wait for the operation to finish - poll the
     * AES State Ready Interrupt flag.
     */
    while(!(AES_STATUS & (AES_SRIF_bm | AES_ERROR_bm)));

    AES_STATUS = AES_SRIF_bm;
}



/**
 * @brief Reads the result of previous AES en/decryption
 *
 * This function returns the result of the previous AES operation.
 *
 * @param[out] data     - result of previous operation
 */
void sal_aes_read(uint8_t *data)
{
    uint8_t i;

    for(i = 0; i < AES_BLOCKSIZE; ++i)
    {
        *data++ = AES_STATE;
    }
}

#endif /* ATXMEGA_SAL */

#endif /* ENABLE_STB */

/* EOF */
