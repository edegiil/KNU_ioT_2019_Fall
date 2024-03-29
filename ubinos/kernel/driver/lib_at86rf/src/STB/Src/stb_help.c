/**
 * @file stb.c
 *
 * @brief High-level security tool box
 *
 * This file implements the security tool box including
 * CCM* encryption and decryption using the SAL API.
 *
 * $Id: stb_help.c,v 1.4 2010-08-01 16:38:27 slb Exp $
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

#include "../../../ubiconfig.h"

#ifdef STB_ON_SAL

/* === Includes ============================================================ */

#include <string.h>
#include "../../TAL/Inc/tal.h"
#include "../../Include/ieee_const.h"
#include "../Inc/stb.h"

/* === Macros ============================================================== */

/* Check if correct SAL type is used. */
#if ((SAL_TYPE != AT86RF2xx) && (SAL_TYPE != ATMEGARF_SAL) && \
     (SAL_TYPE != ATXMEGA_SAL) && (SAL_TYPE != SW_AES_SAL))
#error "unknown SAL type"
#endif

#define MIN(a,b)                ((a) < (b)) ? (a) : (b)

/* === Types =============================================================== */

/* === Globals ============================================================= */

/* === Implementation ====================================================== */

/* help functions ---------------------------------------------------------- */

/**
 * @brief CBC Encrypt data stream with null padding at the end.
 *
 * This function preforms CBC Encryption in the actual mode with actual key
 * and portions of AES_BLOCKSIZE length.
 * If the last block has less than AES_BLOCKSIZE bytes, it is padded with
 * null bytes to this length and then encrypted.
 *
 * No result is return; the CBC-MAC must be read separately.
 *
 * @param start Pointer to start address
 * @param buflen Number of bytes to be encrypted; if 0, nothing happens
 */
void encrypt_with_padding(uint8_t *start, uint8_t buflen)
{
    /* Encrypt the "full blocks". */
    while (buflen >= AES_BLOCKSIZE)
    {
#if (SAL_TYPE == AT86RF2xx)
        sal_aes_wrrd(start, NULL);
#else
        sal_aes_exec(start);
#endif
        start += AES_BLOCKSIZE;
        buflen -= AES_BLOCKSIZE;
    }

    /* Pad the possible rest and encrypt it. */
    if (buflen)
    {
        uint8_t locbuf[AES_BLOCKSIZE];

        memcpy(locbuf, start, buflen);
        memset(locbuf+buflen, 0, AES_BLOCKSIZE-buflen);
#if (SAL_TYPE == AT86RF2xx)
        sal_aes_wrrd(locbuf, NULL);
#else
        sal_aes_exec(locbuf);
#endif
    }
}



/**
 * @brief Computes MIC
 *
 * This function computes the MIC according to CCM.
 *
 * The key was initialized in other functions before.
 *
 * @param[in]  buffer  Input data (frame, not padded yet)
 * @param[out] mic     Computed MIC of size AES_BLOCKSIZE
 * @param[in]  nonce   The nonce: Initialization Vector (IV) as used in
 *                     cryptography; the ZigBee nonce are the bytes 2...14
 *                     of this nonce
 * @param[in]  hdr_len  Size of plaintext header in bytes (may be 0)
 * @param[in]  pld_len Length of payload in bytes (may be 0)
 */
void compute_mic(uint8_t *buffer,
                        uint8_t *mic,
                        uint8_t *nonce,
                        uint8_t hdr_len,
                        uint8_t pld_len)
{
    nonce[AES_BLOCKSIZE-1] = pld_len;

    sal_aes_setup(NULL, AES_MODE_ECB, AES_DIR_ENCRYPT);
#if (SAL_TYPE == AT86RF2xx)
    sal_aes_wrrd(nonce, NULL);
#else
    sal_aes_exec(nonce);
#endif
    sal_aes_setup(NULL, AES_MODE_CBC, AES_DIR_ENCRYPT);

    if (hdr_len)
    {
        uint8_t locbuf[AES_BLOCKSIZE];
        uint8_t firstlen;

        firstlen = MIN(AES_BLOCKSIZE - 2, hdr_len);

        /* Prepend L(a). */
        locbuf[0] = 0;
        locbuf[1] = hdr_len;
        memcpy(locbuf + 2, buffer, firstlen);

        encrypt_with_padding(locbuf, firstlen + 2);

        if (firstlen < hdr_len)
        {
            /* No padding up to now since firstlen is AES_BLOCKSIZE - 2. */
            encrypt_with_padding(buffer + firstlen, hdr_len - firstlen);
        }
    }

    encrypt_with_padding(buffer + hdr_len, pld_len);

    sal_aes_read(mic);
}


#if (SAL_TYPE == AT86RF2xx)
/**
 * @brief Encrypts and decrypts payload and MIC
 *
 * This function perform encryption and decryption of the payload and the MIC.
 *
 * @param[in]  buffer  Input data (frame, not padded yet)
 * @param[in]  nonce   The nonce
 * @param[in]  mic_len  Size of MIC in bytes (may be 0)
 * @param[in]  pld_len Length of payload in bytes (may be 0)
 */
void encrypt_pldmic(uint8_t *buffer,
                           uint8_t *nonce,
                           uint8_t mic_len,
                           uint8_t pld_len)
{
    uint8_t ctr;
    uint8_t i;
    uint8_t keystream[AES_BLOCKSIZE];
    uint8_t *keystreamptr;

    sal_aes_setup(NULL, AES_MODE_ECB, AES_DIR_ENCRYPT);

    /* Init first keystream block. */
    nonce[AES_BLOCKSIZE - 1] = ctr = 1;

    if (pld_len > 0)
    {
        sal_aes_wrrd(nonce, NULL);
    }

    while (true)
    {
        /* Compute next keystream block and get the previous one. */
        if (pld_len <= AES_BLOCKSIZE)        /* Last block */
        {
            if (mic_len)
            {
                /* Prepare the keystream for MIC. */
                nonce[AES_BLOCKSIZE-1] = 0;

                sal_aes_wrrd(nonce, keystream);
            }
            else
            {
                sal_aes_read(keystream);
            }
        }
        else
        {
            /* Prepare the next keystream block. */
            nonce[AES_BLOCKSIZE-1] = ++ctr;

            sal_aes_wrrd(nonce, keystream);
        }

        /* En/decrypt payload. */

        for (i = MIN(pld_len,AES_BLOCKSIZE), keystreamptr = keystream;
             i--;
             /* */)
        {
            *buffer++ ^= *keystreamptr++;
        }

        if (pld_len <= AES_BLOCKSIZE)
        {
            break;
        }

        pld_len -= AES_BLOCKSIZE;
    }

    /* En/decrypt MIC. */

    if (mic_len)
    {
        sal_aes_read(keystream);

        for (i = mic_len, keystreamptr = keystream; i--; /* */)
        {
            *buffer++ ^= *keystreamptr++;
        }
    }
}

#else   /* #if (SAL_TYPE == AT86RF2xx) */

void encrypt_pldmic(uint8_t *buffer,
                           uint8_t *nonce,
                           uint8_t mic_len,
                           uint8_t pld_len)
{
    uint8_t ctr;
    uint8_t i;
    uint8_t keystream[AES_BLOCKSIZE];
    uint8_t *keystreamptr;
    int spld_len;

    spld_len = (int)pld_len;    /* max. value: 0x7f */

    sal_aes_setup(NULL, AES_MODE_ECB, AES_DIR_ENCRYPT);

    ctr = 0;

    while(spld_len > 0)
    {
        /* Compute the keystream block. */
        nonce[AES_BLOCKSIZE-1] = ++ctr;
        sal_aes_exec(nonce);
        sal_aes_read(keystream);

        /* En/decrypt payload. */

        for(i = MIN(spld_len, AES_BLOCKSIZE), keystreamptr = keystream;
             i--;
             /* */)
        {
            *buffer++ ^= *keystreamptr++;
        }

        spld_len -= AES_BLOCKSIZE;
    }

    /* En/decrypt MIC. */

    if(mic_len)
    {
        /* Prepare the keystream for MIC. */
        nonce[AES_BLOCKSIZE-1] = 0;
        sal_aes_exec(nonce);
        sal_aes_read(keystream);

        for(i = mic_len, keystreamptr = keystream; i--; /* */)
        {
            *buffer++ ^= *keystreamptr++;
        }
    }
}
#endif  /* #if (SAL_TYPE == AT86RF2xx) */


#endif /* #ifndef STB_ON_SAL */


/* EOF */
