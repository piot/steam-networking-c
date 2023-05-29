/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <steam-networking/networking_shared.h>

void steamNetworkingIdentityFromUserSteamID(SteamNetworkingIdentity* self, SteamId steamId)
{
    self->m_eType = k_ESteamNetworkingIdentityType_SteamID;
    self->m_cbSize = sizeof(self->m_steamID64);
    self->m_steamID64 = steamId;
}
