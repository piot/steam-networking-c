/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_NETWORKING_MESSAGES_H
#define STEAM_NETWORKING_NETWORKING_MESSAGES_H

#include <steam-networking/networking_messages_flat.h>
#include <stddef.h>

typedef struct SteamNetworkingMessagesFunctions {
    SteamAPI_SteamNetworkingMessages_SteamAPI_v002 createNetworkingMessagesV002;
    SteamAPI_ISteamNetworkingMessages_SendMessageToUser sendMessageToUser;
    SteamAPI_ISteamNetworkingMessages_ReceiveMessagesOnChannel receiveMessagesOnChannel;
    SteamAPI_ISteamNetworkingMessages_AcceptSessionWithUser acceptSessionWithUser;
    SteamAPI_ISteamNetworkingMessages_CloseSessionWithUser closeSessionWithUser;
} SteamNetworkingMessagesFunctions;

typedef struct SteamNetworkingMessages {
    SteamNetworkingMessagesFunctions functions;
    ISteamNetworkingMessages messages;
} SteamNetworkingMessages;

int steamNetworkingMessagesInit(SteamNetworkingMessages* self, Atheneum* atheneum);

void steamNetworkingMessagesSendToUser(SteamNetworkingMessages* self, const SteamNetworkingIdentity* identity,
                                       const uint8_t* payload, size_t payloadOctetCount);

int steamNetworkingMessagesReceiveMessages(SteamNetworkingMessages* self, SteamNetworkingMessage_t** ppOutMessages,
                                           size_t nMaxMessages);
int steamNetworkingMessagesAcceptSessionWithUser(SteamNetworkingMessages* self,
                                                 const SteamNetworkingIdentity* identityRemote);

int steamNetworkingMessagesCloseSessionWithUser(SteamNetworkingMessages* self,
                                                const SteamNetworkingIdentity* identityRemote);

#endif
