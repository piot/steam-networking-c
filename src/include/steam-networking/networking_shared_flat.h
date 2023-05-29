/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_NETWORKING_SHARED_FLAT_H
#define STEAM_NETWORKING_NETWORKING_SHARED_FLAT_H

#include <steam-api/steam_api.h>

typedef enum ESteamNetworkingIdentityType {
    k_ESteamNetworkingIdentityType_Invalid = 0,

    k_ESteamNetworkingIdentityType_SteamID = 16,
    k_ESteamNetworkingIdentityType_XboxPairwiseID = 17,
    k_ESteamNetworkingIdentityType_SonyPSN = 18,
    k_ESteamNetworkingIdentityType__Force32bit = 0x7fffffff,
} ESteamNetworkingIdentityType;

typedef struct SteamNetworkingIdentity {
    ESteamNetworkingIdentityType m_eType;
    int m_cbSize;
    union {
        uint64_t m_steamID64;
        uint8_t m_genericBytes[128];
    };
} SteamNetworkingIdentity;

typedef struct SteamNetworkingConfigValue_t {
    int dummy;
} SteamNetworkingConfigValue_t;

typedef uint32_t HSteamNetConnection;
const static HSteamNetConnection k_HSteamNetConnection_Invalid = 0;

typedef int64_t SteamNetworkingMicroseconds;

typedef enum EResult {
    k_EResultNone = 0, // no result
    k_EResultOK = 1,   // success
    k_EResultFail = 2,
} EResult;

// A message that has been received.
typedef struct SteamNetworkingMessage_t {
    void* m_pData;
    int m_cbSize;
    HSteamNetConnection m_conn;
    SteamNetworkingIdentity m_identityPeer;
    int64_t m_nConnUserData;
    SteamNetworkingMicroseconds m_usecTimeReceived;
    int64_t m_nMessageNumber;
    void (*m_pfnFreeData)(struct SteamNetworkingMessage_t* pMsg);
    void (*m_pfnRelease)(struct SteamNetworkingMessage_t* pMsg);
    int m_nChannel;
    int m_nFlags;
    int64_t m_nUserData;
    uint16_t m_idxLane;
    uint16_t _pad1__;
} SteamNetworkingMessage_t;

const static int k_nSteamNetworkingSend_Unreliable = 0;
const static int k_nSteamNetworkingSend_NoNagle = 1;
const static int k_nSteamNetworkingSend_NoDelay = 4;
const static int k_nSteamNetworkingSend_UnreliableNoDelay = k_nSteamNetworkingSend_Unreliable |
                                                            k_nSteamNetworkingSend_NoDelay |
                                                            k_nSteamNetworkingSend_NoNagle;

#endif
