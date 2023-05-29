/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "atheneum_bind.h"
#include <clog/clog.h>
#include <steam-networking/networking_messages.h>

static int steamNetworkingInitFunctions(SteamNetworkingMessagesFunctions* self, Atheneum* atheneum)
{
    ATHENEUM_BIND(SteamAPI_SteamNetworkingMessages_SteamAPI_v002, createNetworkingMessagesV002)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingMessages_SendMessageToUser, sendMessageToUser)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingMessages_ReceiveMessagesOnChannel, receiveMessagesOnChannel)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingMessages_AcceptSessionWithUser, acceptSessionWithUser)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingMessages_CloseSessionWithUser, closeSessionWithUser)

    return 0;
}

/// Initialize SteamNetworkingMessages
/// @param self
/// @param atheneum shared library to bind functions from
/// @return
int steamNetworkingMessagesInit(SteamNetworkingMessages* self, Atheneum* atheneum)
{
    int err = steamNetworkingInitFunctions(&self->functions, atheneum);
    if (err < 0) {
        return err;
    }

    self->messages = self->functions.createNetworkingMessagesV002();
    if (self->messages == 0) {
        return -4;
    }

    CLOG_DEBUG("messages initialized")

    return 0;
}



/// Send datagram to specified Identity (User SteamID)
/// @param self
/// @param identity
/// @param payload
/// @param payloadOctetCount
void steamNetworkingMessagesSendToUser(SteamNetworkingMessages* self, const SteamNetworkingIdentity* identity,
                                       const uint8_t* payload, size_t payloadOctetCount)
{
    EResult result = self->functions.sendMessageToUser(self->messages, identity, payload, payloadOctetCount,
                                                       k_nSteamNetworkingSend_UnreliableNoDelay, 0);

    if (result != k_EResultOK) {
        CLOG_SOFT_ERROR("problem: %d", result)
    }

    CLOG_VERBOSE("sent message to %016llx", identity->m_steamID64);
}

/// Receive messages from anyone in the relay
/// @param self
/// @param ppOutMessages
/// @param nMaxMessages
/// @return number of messages received
int steamNetworkingMessagesReceiveMessages(SteamNetworkingMessages* self, SteamNetworkingMessage_t** ppOutMessages,
                                           size_t nMaxMessages)
{
    SteamInt receivedMessageCount = self->functions.receiveMessagesOnChannel(self->messages, 0, ppOutMessages,
                                                                             nMaxMessages);

    return receivedMessageCount;
}

/// Accepting a session with a user / identity
/// @param self
/// @param identityRemote
/// @return negative if failed
int steamNetworkingMessagesAcceptSessionWithUser(SteamNetworkingMessages* self,
                                                 const SteamNetworkingIdentity* identityRemote)
{
    CLOG_DEBUG("accepting session with user %016llX", identityRemote->m_steamID64)
    SteamBool worked = self->functions.acceptSessionWithUser(self->messages, identityRemote);
    if (worked) {
        return 0;
    }

    return -1;
}

/// Close session with a user
/// @param self
/// @param identityRemote
/// @return negative if failed
int steamNetworkingMessagesCloseSessionWithUser(SteamNetworkingMessages* self,
                                                const SteamNetworkingIdentity* identityRemote)
{
    SteamBool worked = self->functions.closeSessionWithUser(self->messages, identityRemote);
    if (worked) {
        return 0;
    }

    return -1;
}
