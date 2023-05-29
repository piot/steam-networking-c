/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_NETWORKING_UTILS_H
#define STEAM_NETWORKING_NETWORKING_UTILS_H

#include "networking_utils_flat.h"

typedef struct SteamNetworkingUtilsFunctions {
    SteamAPI_SteamNetworkingUtils_SteamAPI_v004 createNetworkingUtilsV004;
    SteamAPI_ISteamNetworkingUtils_InitRelayNetworkAccess initRelayNetworkAccess;
} SteamNetworkingUtilsFunctions;

typedef struct SteamNetworkingUtils {
    SteamNetworkingUtilsFunctions functions;
    ISteamNetworkingUtils utils;
} SteamNetworkingUtils;

int steamNetworkingUtilsInit(SteamNetworkingUtils* self, Atheneum* atheneum);

#endif
