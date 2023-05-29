/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <atheneum/atheneum.h>
#include <steam-networking/networking.h>

/// @defgroup SteamNetworking
/// @{


int steamNetworkingInit(SteamNetworking* self, SteamApi* api)
{
    steamNetworkingUtilsInit(&self->utils, &api->atheneum);
    int err = steamNetworkingMessagesInit(&self->messages, &api->atheneum);
    if (err < 0) {
        return err;
    }

    return 0;
}



