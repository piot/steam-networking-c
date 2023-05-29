/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_NETWORKING_MESSAGES_FLAT_H
#define STEAM_NETWORKING_NETWORKING_MESSAGES_FLAT_H

#include <steam-networking/networking_shared_flat.h>

typedef void* ISteamNetworkingMessages;

typedef ISteamNetworkingMessages*(S_CALLTYPE* SteamAPI_SteamNetworkingMessages_SteamAPI_v002)(void);

typedef EResult(S_CALLTYPE* SteamAPI_ISteamNetworkingMessages_SendMessageToUser)(
    ISteamNetworkingMessages* self, const SteamNetworkingIdentity* identityRemote, const void* pubData,
    uint32_t cubData, int nSendFlags, int nRemoteChannel);

typedef SteamInt(S_CALLTYPE* SteamAPI_ISteamNetworkingMessages_ReceiveMessagesOnChannel)(
    ISteamNetworkingMessages* self, int nLocalChannel, SteamNetworkingMessage_t** ppOutMessages, int nMaxMessages);
typedef SteamBool(S_CALLTYPE* SteamAPI_ISteamNetworkingMessages_AcceptSessionWithUser)(
    ISteamNetworkingMessages* self, const SteamNetworkingIdentity* identityRemote);

typedef SteamBool(S_CALLTYPE* SteamAPI_ISteamNetworkingMessages_CloseSessionWithUser)(
    ISteamNetworkingMessages* self, const SteamNetworkingIdentity* identityRemote);

#endif
