/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "atheneum_bind.h"
#include <clog/clog.h>
#include <steam-networking/networking_utils.h>

static int initFunctions(SteamNetworkingUtilsFunctions* self, Atheneum* atheneum)
{
    ATHENEUM_BIND(SteamAPI_SteamNetworkingUtils_SteamAPI_v004, createNetworkingUtilsV004)
    ATHENEUM_BIND(SteamAPI_ISteamNetworkingUtils_InitRelayNetworkAccess, initRelayNetworkAccess)

    return 0;
}

/// Initialize steam networking utils
/// Primarily to initialize relay network access
/// @param self
/// @param atheneum
/// @return
int steamNetworkingUtilsInit(SteamNetworkingUtils* self, Atheneum* atheneum)
{
    int err = initFunctions(&self->functions, atheneum);
    if (err < 0) {
        return err;
    }
    CLOG_DEBUG("creating networking utils")
    self->utils = self->functions.createNetworkingUtilsV004();

    CLOG_DEBUG("init relay network")
    self->functions.initRelayNetworkAccess(self->utils);

    return 0;
}
