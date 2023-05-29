/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_H
#define STEAM_NETWORKING_H

#include "networking_sockets_flat.h"
#include <stdint.h>
#include <steam-api/steam_api.h>

typedef struct SteamNetworkingSocketsFunctions {

    SteamAPI_SteamNetworkingSockets_SteamAPI_v012 createNetworkingSocketsV012;

    SteamAPI_ISteamNetworkingSockets_CreateListenSocketP2P createListenSocketP2P;
    SteamAPI_ISteamNetworkingSockets_CloseListenSocket closeListenSocket;

    SteamAPI_ISteamNetworkingSockets_ConnectP2P connectP2P;

    SteamAPI_ISteamNetworkingSockets_ReceiveMessagesOnConnection receiveMessagesOnConnection;
    SteamAPI_ISteamNetworkingSockets_AcceptConnection acceptConnection;

    SteamAPI_ISteamNetworkingSockets_SendMessageToConnection sendMessageToConnection;

} SteamNetworkingSocketsFunctions;

typedef struct SteamNetworkingSockets {
    SteamNetworkingSocketsFunctions functions;
    ISteamNetworkingSockets sockets;
    HSteamListenSocket listenSocketHandle;
} SteamNetworkingSockets;

HSteamListenSocket steamNetworkingSocketsListenP2p(SteamNetworkingSockets* self);
int steamNetworkingSocketsListenClose(SteamNetworkingSockets* self);

HSteamNetConnection steamNetworkingSocketsConnectP2p(SteamNetworkingSockets* self, SteamId userIdToConnectTo);
void steamNetworkingSocketsAcceptConnection(SteamNetworkingSockets* self, HSteamNetConnection connection);

int steamNetworkingSocketsReceiveMessagesOnConnection(SteamNetworkingSockets* self, HSteamNetConnection hConn,
                                               SteamNetworkingMessage_t** ppOutMessages, int nMaxMessages);

int steamNetworkingSocketsSendMessageToConnection(SteamNetworkingSockets* self, HSteamNetConnection hConn, const void* pData,
                                           uint32_t cbData);

#endif
