/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_SOCKETS_FLAT_H
#define STEAM_NETWORKING_SOCKETS_FLAT_H

#include <stdint.h>
#include <steam-networking/networking_shared_flat.h>

typedef void* ISteamNetworkingSockets;


typedef uint32_t HSteamListenSocket;
const static HSteamListenSocket k_HSteamListenSocket_Invalid = 0;

typedef ISteamNetworkingSockets(S_CALLTYPE* SteamAPI_SteamNetworkingSockets_SteamAPI_v012)(void);

typedef HSteamListenSocket(S_CALLTYPE* SteamAPI_ISteamNetworkingSockets_CreateListenSocketP2P)(
    ISteamNetworkingSockets* self, int nLocalVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions);

typedef SteamBool(S_CALLTYPE* SteamAPI_ISteamNetworkingSockets_CloseListenSocket)(ISteamNetworkingSockets* self,
                                                                                  HSteamListenSocket hSocket);

typedef HSteamNetConnection(S_CALLTYPE* SteamAPI_ISteamNetworkingSockets_ConnectP2P)(
    ISteamNetworkingSockets* self, const SteamNetworkingIdentity* identityRemote, int nRemoteVirtualPort, int nOptions,
    const SteamNetworkingConfigValue_t* pOptions);

typedef SteamInt(S_CALLTYPE* SteamAPI_ISteamNetworkingSockets_ReceiveMessagesOnConnection)(
    ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetworkingMessage_t** ppOutMessages,
    int nMaxMessages);

typedef EResult(S_CALLTYPE* SteamAPI_ISteamNetworkingSockets_AcceptConnection)(ISteamNetworkingSockets* self,
                                                                               HSteamNetConnection hConn);

typedef EResult(S_CALLTYPE* SteamAPI_ISteamNetworkingSockets_SendMessageToConnection)(ISteamNetworkingSockets* self,
                                                                                      HSteamNetConnection hConn,
                                                                                      const void* pData,
                                                                                      uint32_t cbData, int nSendFlags,
                                                                                      int64_t* pOutMessageNumber);

#endif
