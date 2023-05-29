/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <steam-networking/networking_sockets.h>
#include "atheneum_bind.h"
#include <clog/clog.h>
#include <steam-networking/networking_shared.h>

static int steamNetworkingInitFunctions(SteamNetworkingSocketsFunctions* self, Atheneum* atheneum)
{
    ATHENEUM_BIND(SteamAPI_SteamNetworkingSockets_SteamAPI_v012, createNetworkingSocketsV012)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingSockets_CreateListenSocketP2P, createListenSocketP2P)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingSockets_CloseListenSocket, closeListenSocket)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingSockets_ConnectP2P, connectP2P)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingSockets_AcceptConnection, acceptConnection)
    return 0;
}


HSteamListenSocket steamNetworkingSocketsListenP2p(SteamNetworkingSockets* self)
{
    HSteamListenSocket socketHandle = self->functions.createListenSocketP2P(self->sockets, 0, 0, 0);

    self->listenSocketHandle = socketHandle;

    CLOG_DEBUG("listening on handle %08X", self->listenSocketHandle)

    return socketHandle;
}

HSteamNetConnection steamNetworkingSocketsConnectP2p(SteamNetworkingSockets* self, SteamId userIdToConnectTo)
{
    SteamNetworkingIdentity identity;

    steamNetworkingIdentityFromUserSteamID(&identity, userIdToConnectTo);

    HSteamNetConnection connection = self->functions.connectP2P(self->sockets, &identity, 0, 0, 0);

    CLOG_OUTPUT("connectP2p %08X", connection)

    return connection;
}

int steamNetworkingSocketsListenClose(SteamNetworkingSockets* self)
{
    SteamBool worked = self->functions.closeListenSocket(self->sockets, self->listenSocketHandle);
    if (!worked) {
        return -2;
    }

    return 0;
}


void steamNetworkingSocketsAcceptConnection(SteamNetworkingSockets* self, HSteamNetConnection connection)
{
}

int steamNetworkingSocketsSendMessageToConnection(SteamNetworkingSockets* self, HSteamNetConnection hConn, const void* pData,
                                           uint32_t cbData)
{
    int64_t messageNumber;
    EResult result = self->functions.sendMessageToConnection(self->sockets, hConn, pData, cbData,
                                                             k_nSteamNetworkingSend_UnreliableNoDelay, &messageNumber);
    CLOG_VERBOSE("sent message to connection %08X with code %08X and got %016llX as message number", hConn, result,
                 messageNumber)

    return 0;
}

