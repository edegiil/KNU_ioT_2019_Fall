/**
 * @file ieee_const.h
 *
 * @brief This header holds all IEEE 802.15.4-2006 constants and attribute identifiers
 *
 * $Id: ieee_const.h,v 1.2 2010-07-30 18:06:27 slb Exp $
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
#ifndef IEEE_CONST_H
#define IEEE_CONST_H

#include "../../ubiconfig.h"

#if (HIGHEST_STACK_LAYER == TINY_TAL)
#include "../TAL/Inc/tiny_tal.h"
#else
#include "../TAL/Inc/tal.h"
#endif

#if !defined(RF_BAND)
#error "Please define RF_BAND to BAND_2400 or BAND_900."
#endif /* !defined(RF_BAND) */

/* === Includes ============================================================= */


/* === Macros =============================================================== */

/**
 * Minimum size of a valid frame other than an Ack frame
 */
#define MIN_FRAME_LENGTH                (8)

/**
 * Maximum size of the management frame(Association Response frame)
 */
#define MAX_MGMT_FRAME_LENGTH           (30)

/* === MAC Constants ======================================================== */

/**
 * Maximum size of PHY packet
 * @ingroup apiMacConst
 */
#define aMaxPHYPacketSize               (127)

/**
 * Maximum turnaround Time of the radio to switch from Rx to Tx or Tx to Rx
 * in symbols
 * @ingroup apiMacConst
 */
#define aTurnaroundTime                 (12)

/* 7.4.1 MAC Layer Constants */

/**
 * The number of symbols forming a superframe slot
 * when the superframe order is equal to 0.
 * @ingroup apiMacConst
 */
#define aBaseSlotDuration               (60)

/**
 * The number of symbols forming a superframe when
 * the superframe order is equal to 0.
 * @ingroup apiMacConst
 */
#define aBaseSuperframeDuration         (aBaseSlotDuration * aNumSuperframeSlots)

/**
 * The number of superframes in which a GTS descriptor
 * exists in the beacon frame of a PAN coordinator.
 * @ingroup apiMacConst
 */
#define aGTSDescPersistenceTime         (4)

/**
 * The maximum number of octets added by the MAC
 * sublayer to the payload of its beacon frame.
 * @ingroup apiMacConst
 */
#define aMaxBeaconOverhead              (75)

/**
 * The maximum size, in octets, of a beacon payload.
 * @ingroup apiMacConst
 */
#define aMaxBeaconPayloadLength         (aMaxPHYPacketSize - aMaxBeaconOverhead)

/**
 * The number of consecutive lost beacons that will cause the MAC sublayer of
 * a receiving device to declare a loss of synchronization.
 * @ingroup apiMacConst
 */
#define aMaxLostBeacons                 (4)

/**
 * The maximum number of octets that can be transmitted in the MAC Payload
 * field.
 * @ingroup apiMacConst
 */
#define aMaxMACPayloadSize              (aMaxPHYPacketSize - aMinMPDUOverhead)

/**
 * The maximum number of octets that can be transmitted in the MAC Payload
 * field of an unsecured MAC frame that will be guaranteed not to exceed
 * aMaxPHYPacketSize.
 * @ingroup apiMacConst
 */
#define aMaxMACSafePayloadSize          (aMaxPHYPacketSize - aMaxMPDUUnsecuredOverhead)

/**
 * The maximum number of octets added by the MAC sublayer to the PSDU without
 * security.
 * @ingroup apiMacConst
 */
#define aMaxMPDUUnsecuredOverhead       (25)

/**
 * The maximum size of an MPDU, in octets, that can be followed by a SIFS
 * period.
 * @ingroup apiMacConst
 */
#define aMaxSIFSFrameSize               (18)

/**
 * The minimum number of symbols forming the CAP. This ensures that MAC
 * commands can still be transferred to devices when GTSs are being used.
 * An exception to this minimum shall be allowed for the accommodation
 * of the temporary increase in the beacon frame length needed to perform GTS
 * maintenance (see 7.2.2.1.3).
 * @ingroup apiMacConst
 */
#define aMinCAPLength                   (440)


/**
 * The minimum number of octets added by the MAC sublayer to the PSDU.
 * @ingroup apiMacConst
 */
#define aMinMPDUOverhead                 (9)

/**
 * The number of slots contained in any superframe.
 * @ingroup apiMacConst
 */
#define aNumSuperframeSlots             (16)

/**
 * The number of symbols forming the basic time period
 * used by the CSMA-CA algorithm.
 * @ingroup apiMacConst
 */
#define aUnitBackoffPeriod              (20)

/* PHY PIB Attributes */

/**
 * @ingroup apiPhyPib
 * @{
 */

/* Standard PIB attributes */

/**
 * The RF channel to use for all following transmissions and receptions.
 */
#define phyCurrentChannel               (0x00)

/**
 * The 5 most significant bits (MSBs) (b27, ..., b31) of phyChannelsSupported
 * shall be reserved and set to 0, and the 27 LSBs (b0, b1, ..., b26) shall
 * indicate the status (1 = available, 0 = unavailable) for each of the 27 valid
 * channels (bk shall indicate the status of channel k).
 */
#define phyChannelsSupported            (0x01)

/**
 * The 2 MSBs represent the tolerance on the transmit power: 00 = 1 dB
 * 01 = 3 dB 10 = 6 dB The 6 LSBs represent a signed integer in
 * twos-complement format, corresponding to the nominal transmit power of the
 * device in decibels relative to 1 mW. The lowest value of phyTransmitPower
 * shall be interpreted as less than or equal to 32 dBm.
 */
#define phyTransmitPower                (0x02)

/**
 * The CCA mode
 *  - CCA Mode 1: Energy above threshold. CCA shall report a busy medium
 * upon detecting any energy above the ED threshold.
 *  - CCA Mode 2: Carrier sense only. CCA shall report a busy medium only upon
 * the detection of a signal with the modulation and spreading characteristics
 * of IEEE 802.15.4. This signal may be above or below the ED threshold.
 *  - CCA Mode 3: Carrier sense with energy above threshold. CCA shall report a
 * busy medium only upon the detection of a signal with the modulation and
 * spreading characteristics of IEEE 802.15.4 with energy above the ED
 * threshold. */
#define phyCCAMode                      (0x03)

/**
 * This is the current PHY channel page. This is used in conjunction with
 * phyCurrentChannel to uniquely identify the channel currently being used.
 */
#define phyCurrentPage                  (0x04)

/**
 * The maximum number of symbols in a frame:
 * = phySHRDuration + ceiling([aMaxPHYPacketSize + 1] x phySymbolsPerOctet)
 */
#define phyMaxFrameDuration             (0x05)

/**
 * The duration of the synchronization header (SHR) in symbols for the current
 * PHY.
 */
#define phySHRDuration                  (0x06)

/**
 * The number of symbols per octet for the current PHY.
 */
#define phySymbolsPerOctet              (0x07)

/**
 * Number of octets added by the PHY: 4 sync octets + SFD octet.
 */
#define PHY_OVERHEAD                    (5)

/*@}*//* apiPhyPib */

/* 7.4.2 MAC PIB Attributes */

/**
 * The maximum number of symbols to wait for an acknowledgment frame to arrive
 * following a transmitted data frame. This value is dependent on the currently
 * selected logical channel. For 0 <= phyCurrentChannel <= 10, this
 * value is equal to 120. For 11 <= phyCurrentChannel <= 26, this  value is
 * equal to 54.
 *
 * - @em Type: Integer
 * - @em Range: 54 or 120
 * - @em Default: 54
 */
#define macAckWaitDuration              (0x40)

#if (RF_BAND == BAND_2400)
/**
 * Default value for MIB macAckWaitDuration
 */
#define macAckWaitDuration_def          (54)
#elif (RF_BAND == BAND_900)
/**
 * Default value for MIB macAckWaitDuration
 */

/**
 * The default value for this PIB attribute depends on the current channel page
 * (i.e. the modulation scheme: BPSK or O-QPSK).
 */
#define macAckWaitDuration_def          \
                  (tal_pib_CurrentPage == 0 ? 120 : 54)

#else   /* Can't happen because RF_BAND is checked above. */
#error "You have got no license for that RF band."
#endif /* RF_BAND */

/**
 * Indication of whether a coordinator is currently allowing association.
 * A value of true indicates that association is permitted.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macAssociationPermit            (0x41)

/**
 * Default value for PIB macAssociationPermit
 */
#define macAssociationPermit_def        (false)

/**
 * Indication of whether a device automatically sends a data request command
 * if its address is listed in the beacon frame. A value of true indicates
 * that the data request command is automatically sent.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: true
 */
#define macAutoRequest                  (0x42)

/**
 * Default value for PIB macAutoRequest
 */
#define macAutoRequest_def              (true)

/**
 * Indication of whether battery life extension, by reduction of coordinator
 * receiver operation time during the CAP, is enabled. A value of
 * true indicates that it is enabled.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macBattLifeExt                  (0x43)

/**
 * Default value for PIB macBattLifeExt
 */
#define macBattLifeExt_def              (false)

/**
 * The number of backoff periods during which the receiver is enabled following
 * a beacon in battery life extension mode. This value is dependent on the
 * currently selected logical channel. For 0 <= * phyCurrentChannel <= 10, this
 * value is equal to 8. For 11 <= * phyCurrentChannel <= 26, this value
 * is equal to 6.
 *
 * - @em Type: Integer
 * - @em Range: 6 or 8
 * - @em Default: 6
 */
#define macBattLifeExtPeriods           (0x44)

/**
 * Default value for PIB macBattLifeExtPeriods
 */
#define macBattLifeExtPeriods_def       (6)

/**
 * The contents of the beacon payload.
 *
 * - @em Type: Set of octets
 * - @em Range: --
 * - @em Default: NULL
 */
#define macBeaconPayload                (0x45)

/**
 * The length, in octets, of the beacon payload.
 *
 * - @em Type: Integer
 * - @em Range: 0 - aMaxBeaconPayloadLength
 * - @em Default: 0
 */
#define macBeaconPayloadLength          (0x46)

/**
 * Default value for PIB macBeaconPayloadLength
 */
#define macBeaconPayloadLength_def      (0)

/**
 * Specification of how often the coordinator transmits a beacon.
 * The macBeaconOrder, BO, and the beacon interval, BI, are related as
 * follows: for 0 <= BO <= 14, BI = aBaseSuperframeDuration * 2^BO symbols.
 * If BO = 15, the coordinator will not transmit a beacon.
 *
 * - @em Type: Integer
 * - @em Range: 0 - 15
 * - @em Default: 15
 */
#define macBeaconOrder                  (0x47)

/**
 * Default value for PIB macBeaconOrder
 */
#define macBeaconOrder_def              (15)

/**
 * BO value for nonbeacon-enabled network
 */
#define NON_BEACON_NWK                  (0x0F)

/**
 * The time that the device transmitted its last beacon frame, in symbol
 * periods. The measurement shall be taken at the same symbol boundary within
 * every transmitted beacon frame, the location of which is implementation
 * specific. The precision of this value shall be a minimum of 20 bits, with
 * the lowest four bits being the least significant.
 *
 * - @em Type: Integer
 * - @em Range: 0x000000 - 0xffffff
 * - @em Default: 0x000000
 */
#define macBeaconTxTime                 (0x48)

/**
 * Default value for PIB macBeaconTxTime
 */
#define macBeaconTxTime_def             (0x000000)

/**
 * The sequence number added to the transmitted beacon frame.
 *
 * - @em Type: Integer
 * - @em Range: 0x00 - 0xFF
 * - @em Default: Random value from within the range.
 */
#define macBSN                          (0x49)

/**
 * The 64 bit address of the coordinator with which the device is associated.
 *
 * - @em Type: IEEE address
 * - @em Range: An extended 64bit IEEE address
 * - @em Default: -
 */
#define macCoordExtendedAddress         (0x4A)

/**
 * The 16 bit short address assigned to the coordinator with which the device
 * is associated. A value of 0xfffe indicates that the coordinator is only
 * using its 64 bit extended address. A value of 0xffff indicates that this
 * value is unknown.
 *
 * - @em Type: Integer
 * - @em Range: 0x0000 - 0xffff
 * - @em Default: 0xffff
 */
#define macCoordShortAddress            (0x4B)

/**
 * Default value for PIB macCoordShortAddress
 */
#define macCoordShortAddress_def        (0xFFFF)

/**
 * The sequence number added to the transmitted data or MAC command frame.
 *
 * - @em Type: Integer
 * - @em Range: 0x00 - 0xFF
 * - @em Default: Random value from within the range.
 */
#define macDSN                          (0x4C)

/**
 * macGTSPermit is true if the PAN coordinator is to accept GTS requests,
 * false otherwise.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: true
 */
#define macGTSPermit                    (0x4D)

/**
 * Default value for PIB macGTSPermit
 */
#define macGTSPermit_def                (true)

/**
 * The maximum number of backoffs the CSMA-CA algorithm will
 * attempt before declaring a channel access failure.
 *
 * - @em Type: Integer
 * - @em Range: 0 - 5
 * - @em Default: 4
 */
#define macMaxCSMABackoffs              (0x4E)

/**
 * Default value for PIB macMaxCSMABackoffs
 */
#define macMaxCSMABackoffs_def          (4)

/**
 * The minimum value of the backoff exponent in the CSMA-CA algorithm.
 * Note that if this value is set to 0, collision avoidance is disabled
 * during the first iteration of the algorithm. Also note that for the
 * slotted version of the CSMACA algorithm with the battery life extension
 * enabled, the minimum value of the backoff exponent will be the lesser of
 * 2 and the value of macMinBE.
 *
 * - @em Type: Integer
 * - @em Range: 0 - 3
 * - @em Default: 3
 */
#define macMinBE                        (0x4F)

/**
 * The 16 bit identifier of the PAN on which the device is operating. If this
 * value is 0xffff, the device is not associated.
 *
 * - @em Type: Integer
 * - @em Range: 0x0000 - 0xffff
 * - @em Default: 0xffff
 */
#define macPANId                        (0x50)

/**
 * Default value for PIB macPANId
 */
#define macPANId_def                    (0xFFFF)

/**
 * This indicates whether the MAC sublayer is in a promiscuous (receive all)
 * mode. A value of true indicates that the MAC sublayer accepts all frames
 * received from the PHY.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macPromiscuousMode              (0x51)

/**
 * This indicates whether the MAC sublayer is to enable its receiver
 * during idle periods.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macRxOnWhenIdle                 (0x52)

/**
 * Default value for PIB macRxOnWhenIdle
 */
#define macRxOnWhenIdle_def             (false)

/**
 * The 16 bit address that the device uses to communicate in the PAN.
 * If the device is a PAN coordinator, this value shall be chosen before a
 * PAN is started. Otherwise, the address is allocated by a coordinator
 * during association. A value of 0xfffe indicates that the device has
 * associated but has not been allocated an address. A value of 0xffff
 * indicates that the device does not have a short address.
 *
 * - @em Type: Integer
 * - @em Range: 0x0000 - 0xffff
 * - @em Default: 0xffff
 */
#define macShortAddress                 (0x53)

/**
 * Default value for PIB macShortAddress
 */
#define macShortAddress_def             (0xFFFF)

/**
 * This specifies the length of the active portion of the superframe, including
 * the beacon frame. The macSuperframeOrder, SO, and the superframe duration,
 * SD, are related as follows: for 0 <= SO <= BO <= 14, SD =
 * aBaseSuperframeDuration * 2SO symbols. If SO = 15, the superframe will
 * not be active following the beacon.
 *
 * - @em Type: Integer
 * - @em Range: 0 - 15
 * - @em Default: 15
 */
#define macSuperframeOrder              (0x54)

/**
 * Default value for PIB macSuperframeOrder
 */
#define macSuperframeOrder_def          (15)

/**
 * The maximum time (in superframe periods) that a transaction is stored by a
 * coordinator and indicated in its beacon.
 *
 * - @em Type: Integer
 * - @em Range: 0x0000 - 0xffff
 * - @em Default: 0x01f4
 */
#define macTransactionPersistenceTime   (0x55)

/**
 * Default value for PIB macTransactionPersistenceTime
 */
#define macTransactionPersistenceTime_def (0x01F4)

/**
 * Indication of whether the device is associated to the PAN through the PAN
 * coordinator. A value of TRUE indicates the device has associated through the
 * PAN coordinator. Otherwise, the value is set to FALSE.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macAssociatedPANCoord           (0x56)

/**
 * Default value for PIB macAssociatedPANCoord
 */
#define macAssociatedPANCoord_def       (false)

/**
 * The maximum value of the backoff exponent, BE, in the CSMA-CA algorithm.
 * See 7.5.1.4 for a detailed explanation of the backoff exponent.
 *
 * - @em Type: Integer
 * - @em Range: 3 - 8
 * - @em Default: 5
 */
#define macMaxBE                        (0x57)

/**
 * The maximum number of CAP symbols in a beaconenabled PAN, or symbols in a
 * nonbeacon-enabled PAN, to wait either for a frame intended as a response to
 * a data request frame or for a broadcast frame following a beacon with the
 * Frame Pending subfield set to one.
 * This attribute, which shall only be set by the next higher layer, is
 * dependent upon macMinBE, macMaxBE, macMaxCSMABackoffs and the number of
 * symbols per octet. See 7.4.2 for the formula relating the attributes.
 *
 * - @em Type: Integer
 * - @em Range: See equation (14)
 * - @em Default: Dependent on currently selected PHY, indicated by phyCurrentPage
 */
#define macMaxFrameTotalWaitTime        (0x58)

/**
 * Default value for PIB macMaxBE (see equation 14 in section 7.4.2)
 * The default value is valid for:
 * macMinBE = 3
 * macMaxBE = 5
 * macMaxCSMABackoffs = 4
 */
#if (RF_BAND == BAND_2400)
 /* O-QPSK 2.4 GHz */
#define macMaxFrameTotalWaitTime_def    (1986)

#elif (RF_BAND == BAND_900)
 /* BPSK 900 MHz */
#define macMaxFrameTotalWaitTime_def    (2784)

#else   /* Can't happen because RF_BAND is checked above. */
#error "You have got no license for that RF band."
#endif /* RF_BAND */

/**
 * The maximum number of retries allowed after a transmission failure.
 *
 * - @em Type: Integer
 * - @em Range: 0 - 7
 * - @em Default: 3
 */
#define macMaxFrameRetries              (0x59)

/**
 * The maximum time, in multiples of aBaseSuperframeDuration, a device shall
 * wait for a response command frame to be available following a request
 * command frame.
 *
 * - @em Type: Integer
 * - @em Range: 2 - 64
 * - @em Default: 32
 */
#define macResponseWaitTime             (0x5A)

/**
 * Default value for PIB macResponseWaitTime
 */
#define macResponseWaitTime_def         (32 * aBaseSuperframeDuration)

/**
 * The offset, measured in symbols, between the symbol boundary at which the
 * MLME captures the timestamp of each transmitted or received frame, and the
 * onset of the first symbol past the SFD, namely, the first symbol of the
 * Length field.
 *
 * - @em Type: Integer
 * - @em Range: 0x000-0x100 for the 2.4 GHz PHY
 *              0x000-0x400 for the 868/915 MHz PHY
 * - @em Default: Implementation specific
 */
#define macSyncSymbolOffset             (0x5B)

/**
 * Indication of whether the MAC sublayer supports the optional timestamping
 * feature for incoming and outgoing data frames.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macTimestampSupported           (0x5C)

/**
 * Indication of whether the MAC sublayer has security enabled. A value of
 * TRUE indicates that security is enabled, while a value of FALSE indicates
 * that security is disabled.
 *
 * - @em Type: Boolean
 * - @em Range: true or false
 * - @em Default: false
 */
#define macSecurityEnabled              (0x5D)

/**
 * Default value for PIB macResponseWaitTime
 */
#define macSecurityEnabled_def          (false)

/**
 * The minimum number of symbols forming a LIFS period.
 *
 * - @em Type: Integer
 * - @em Range: See Table 3 in Clause 6 (40 symbols)
 * - @em Default: Dependent on currently selected PHY, indicated by phyCurrentPage
 */
#define macMinLIFSPeriod                (0x5E)

/**
 * Default value for PIB macMinLIFSPeriod
 */
#define macMinLIFSPeriod_def            (40)


/**
 * The minimum number of symbols forming a SIFS period.
 *
 * - @em Type: Integer
 * - @em Range: See Table 3 in Clause 6 (12 symbols)
 * - @em Default: Dependent on currently selected PHY, indicated by phyCurrentPage
 */
#define macMinSIFSPeriod                (0x5F)

/**
 * Default value for PIB macMinSIFSPeriod
 */
#define macMinSIFSPeriod_def            (12)

/**
 * Private MAC PIB attribute to allow setting the MAC address in test mode.
 * @todo numbering needs to alligned with other special speer attributes
 */
#define macIeeeAddress                  (0xF0)


/**
 * @ingroup apiPhyConst
 *  @{
 */
/* 6.2.3 PHY Enumeration Definitions */
typedef enum phy_enum_tag
{
    /**
     * The CCA attempt has detected a busy channel.
     */
    PHY_BUSY                              = (0x00),

    /**
     * The transceiver is asked to change its state while receiving.
     */
    PHY_BUSY_RX                           = (0x01),

    /**
     * The transceiver is asked to change its state while transmitting.
     */
    PHY_BUSY_TX                           = (0x02),

    /**
     * The transceiver is to be switched off.
     */
    PHY_FORCE_TRX_OFF                     = (0x03),

    /**
     * The CCA attempt has detected an idle channel.
     */
    PHY_IDLE                              = (0x04),

    /**
     * A SET/GET request was issued with a parameter in the primitive that is out
     * of the valid range.
     */
    PHY_INVALID_PARAMETER                 = (0x05),

    /**
     * The transceiver is in or is to be configured into the receiver enabled
     * state.
     */
    PHY_RX_ON                             = (0x06),

    /**
     * A SET/GET, an ED operation, or a transceiver state change was successful.
     */
    PHY_SUCCESS                           = (0x07),

    /**
     * The transceiver is in or is to be configured into the transceiver disabled
     * state.
     */
    PHY_TRX_OFF                           = (0x08),

    /**
     * The transceiver is in or is to be configured into the transmitter enabled
     * state.
     */
    PHY_TX_ON                             = (0x09),

    /**
     * A SET/GET request was issued with the identifier of an attribute that is not
     * supported.
     */
    PHY_UNSUPPORTED_ATTRIBUTE             = (0x0A),

    /**
     * A SET/GET request was issued with the identifier of an attribute that is
     * read-only.
     */
    PHY_READ_ONLY                         = (0x0B)
} __attribute__((packed, aligned(4))) phy_enum_t;


/* Non-standard values / extensions */

/**
 * PHY_SUCCESS in phyAutoCSMACA when received ACK frame had the pending bit set
 */
#define PHY_SUCCESS_DATA_PENDING        (0x10)

/**
 * ED scan/sampling duration
 */
#define ED_SAMPLE_DURATION_SYM          (8)

/*@}*/ /* apiPhyConst */


/* MLME-SCAN.request type */

/**
 * @brief Energy scan (see @link wpan_mlme_scan_req() @endlink)
 * @ingroup apiConst
 */
#define MLME_SCAN_TYPE_ED               (0x00)

/**
 * @brief Active scan (see @link wpan_mlme_scan_req() @endlink)
 * @ingroup apiConst
 */
#define MLME_SCAN_TYPE_ACTIVE           (0x01)

/**
 * @brief Passive scan (see @link wpan_mlme_scan_req() @endlink)
 * @ingroup apiConst
 */
#define MLME_SCAN_TYPE_PASSIVE          (0x02)

/**
 * @brief Orphan scan (see @link wpan_mlme_scan_req() @endlink)
 * @ingroup apiConst
 */
#define MLME_SCAN_TYPE_ORPHAN           (0x03)

/**
 * Value for TxOptions parameter im @ref wpan_mcps_data_req().
 * @ingroup apiConst
 */
#define WPAN_TXOPT_OFF                  (0x00)

/**
 * Value for TxOptions parameter im @ref wpan_mcps_data_req().
 * @ingroup apiConst
 */
#define WPAN_TXOPT_ACK                  (0x01)

/**
 * Value for TxOptions parameter im @ref wpan_mcps_data_req().
 * @ingroup apiConst
 */
#define WPAN_TXOPT_INDIRECT            (0x04)

/**
 * Value for TxOptions parameter im @ref wpan_mcps_data_req().
 * @ingroup apiConst
 */
#define WPAN_TXOPT_INDIRECT_ACK        (0x05)

/* Various constants */

/*
 * Channel numbers and channel masks for scanning.
 */
#if (RF_BAND == BAND_2400) || defined(DOXYGEN)
    /** Minimum channel */
    #define MIN_CHANNEL                 (11)
    /** Maximum channel */
    #define MAX_CHANNEL                 (26)
    /** Valid channel masks for scanning */
    #define VALID_CHANNEL_MASK          (0x07FFF800UL)
#else   /* 900 MHz */
    #define MIN_CHANNEL                 (0)
    #define MAX_CHANNEL                 (10)
    #define VALID_CHANNEL_MASK          (0x000007FFUL)
#endif

/**
 * Inverse channel masks for scanning.
 */
#define INVERSE_CHANNEL_MASK            (~VALID_CHANNEL_MASK)

/* Association status values from table 68 */

/**
 * Association status code value (see @link wpan_mlme_associate_resp() @endlink).
 * @ingroup apiConst
 */
#define ASSOCIATION_SUCCESSFUL          (0)

/**
 * Association status code value (see @link wpan_mlme_associate_resp() @endlink).
 * @ingroup apiConst
 */
#define PAN_AT_CAPACITY                 (1)

/**
 * Association status code value (see @link wpan_mlme_associate_resp() @endlink).
 * @ingroup apiConst
 */
#define PAN_ACCESS_DENIED               (2)

/**
 * Association status code value (see @link wpan_mlme_associate_resp() @endlink).
 * @ingroup apiConst
 */
#define ASSOCIATION_RESERVED            (3)

/**
 * Defines the beacon frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_BEACON            (0x00)

/**
 * Define the data frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_DATA              (0x01)

/**
 * Define the ACK frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_ACK               (0x02)

/**
 * Define the command frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_MAC_CMD           (0x03)

/**
 * A macro to set the frame type.
 */
#define FCF_SET_FRAMETYPE(x)            (x)

/**
 * The mask for the security enable bit of the FCF.
 */
#define FCF_SECURITY_ENABLED            (1 << 3)

/**
 * The mask for the frame pending bit of the FCF
 */
#define FCF_FRAME_PENDING               (1 << 4)

/**
 * The mask for the ACK request bit of the FCF
 */
#define FCF_ACK_REQUEST                 (1 << 5)

/**
 * The mask for the PAN ID compression bit of the FCF
 */
#define FCF_PAN_ID_COMPRESSION          (1 << 6)

/**
 * The mask for a IEEE 802.15.4-2006 compatible frame in the
 * frame version subfield
 */
#define FCF_FRAME_VERSION_2006          (1 << 12)

/**
 * Address Mode: NO ADDRESS
 */
#define FCF_NO_ADDR                     (0x00)

/**
 * Address Mode: RESERVED
 */
#define FCF_RESERVED_ADDR               (0x01)

/**
 * Address Mode: SHORT
 */
#define FCF_SHORT_ADDR                  (0x02)

/**
 * Address Mode: LONG
 */
#define FCF_LONG_ADDR                   (0x03)

/**
 * Defines the offset of the destination address
 */
#define FCF_DEST_ADDR_OFFSET            (10)

/**
 * Defines the offset of the source address
 */
#define FCF_SOURCE_ADDR_OFFSET          (14)

/**
 * Macro to set the source address mode
 */
#define FCF_SET_SOURCE_ADDR_MODE(x)     ((unsigned int)((x) << FCF_SOURCE_ADDR_OFFSET))

/**
 * Macro to set the destination address mode
 */
#define FCF_SET_DEST_ADDR_MODE(x)       ((unsigned int)((x) << FCF_DEST_ADDR_OFFSET))

/**
 * Mask for the number of short addresses pending
 */
#define NUM_SHORT_PEND_ADDR(x)          ((x) & 0x07)

/**
 * Mask for the number of long addresses pending
 */
#define NUM_LONG_PEND_ADDR(x)           (((x) & 0x70) >> 4)

/**
 * Generic 16 bit broadcast address
 */
#define BROADCAST                       (0xFFFF)

/**
 * Unused EUI-64 address
 */
#define CLEAR_ADDR_64                   (0ULL)

/**
 * MAC is using long address (by now).
 */
#define MAC_NO_SHORT_ADDR_VALUE         (0xFFFE)

/**
 * Invalid short address
 */
#define INVALID_SHORT_ADDRESS           (0xFFFF)

/* But position within beacon Superframe Specification field */
/**
 * Battery life extention bit position.
 */
#define BATT_LIFE_EXT_BIT_POS               (12)

/**
 * PAN coordinator bit position.
 */
#define PAN_COORD_BIT_POS                   (14)

/**
 * Association permit bit position.
 */
#define ASSOC_PERMIT_BIT_POS                (15)

/**
 * @brief Converts a phyTransmitPower value to a dBm value
 *
 * @param phyTransmitPower_value phyTransmitPower value
 *
 * @return dBm using signed integer format
 */
#define CONV_phyTransmitPower_TO_DBM(phyTransmitPower_value)                      \
            (                                                                     \
             ((phyTransmitPower_value & 0x20) == 0x00) ?                          \
              ((int8_t)(phyTransmitPower_value & 0x3F)) :                         \
              ((-1) * (int8_t)((~((phyTransmitPower_value & 0x1F) - 1)) & 0x1F))  \
            )


/**
 * @brief Converts a dBm value to a phyTransmitPower value
 *
 * @param dbm_value dBm value
 *
 * @return phyTransmitPower_value using IEEE-defined format
 */
#define CONV_DBM_TO_phyTransmitPower(dbm_value)                                         \
            (                                                                           \
                dbm_value < -32 ?                                                       \
                0x20 :                                                                  \
                (                                                                       \
                    dbm_value > 31 ?                                                    \
                    0x1F :                                                              \
                    (                                                                   \
                        dbm_value < 0 ?                                                 \
                        ( ((~(((uint8_t)((-1) * dbm_value)) - 1)) & 0x1F) | 0x20 ) :    \
                        (uint8_t)dbm_value                                              \
                    )                                                                   \
                )                                                                       \
            )                                                                           \


/* === Types ================================================================ */

#if !defined(DOXYGEN)
typedef enum trx_cca_mode_tag
{
    TRX_CCA_MODE0 = 0,  /* Carrier sense OR energy above threshold */
    TRX_CCA_MODE1 = 1,  /* Energy above threshold */
    TRX_CCA_MODE2 = 2,  /* Carrier sense only */
    TRX_CCA_MODE3 = 3   /* Carrier sense AND energy above threshold */
} __attribute__((packed, aligned(4))) trx_cca_mode_t;
/**
 * CCA Modes of the transceiver
 */

#endif

/* === Externals ============================================================ */


/* === Prototypes =========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* IEEE_CONST_H */
/* EOF */
