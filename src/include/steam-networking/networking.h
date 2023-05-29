/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_NETWORKING_H
#define STEAM_NETWORKING_NETWORKING_H

#include <steam-networking/networking_messages.h>
#include <steam-networking/networking_utils.h>

typedef struct SteamNetworking {
    struct SteamApi* api;
    SteamNetworkingMessages messages;
    SteamNetworkingUtils utils;
} SteamNetworking;

int steamNetworkingInit(SteamNetworking* self, SteamApi* api);

#endif
