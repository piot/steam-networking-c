/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_NETWORKING_UTILS_FLAT_H
#define STEAM_NETWORKING_NETWORKING_UTILS_FLAT_H

#include <steam-api/steam_api.h>

typedef void* ISteamNetworkingUtils;

typedef void(S_CALLTYPE* SteamAPI_ISteamNetworkingUtils_InitRelayNetworkAccess)(ISteamNetworkingUtils* self);
typedef ISteamNetworkingUtils(S_CALLTYPE* SteamAPI_SteamNetworkingUtils_SteamAPI_v004)(void);

#endif

