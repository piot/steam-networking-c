/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <clog/console.h>
#include <stdbool.h>
#include <steam-api/steam_api.h>
#include <steam-networking/networking.h>
#include <unistd.h>

clog_config g_clog;

typedef struct ExampleData {
    int data;
} ExampleData;

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    g_clog.log = clog_console;
    g_clog.level = CLOG_TYPE_VERBOSE;

    SteamApi api;
    steamApiInit(&api);

    SteamNetworking networking;
    steamNetworkingInit(&networking, &api);

    ExampleData data;
    data.data = 42;

    SteamNetworkingMessages* messages = &networking.messages;

    if (true) {
    }

    uint64_t tickCount = 0;
    while (true) {
        steamApiUpdate(&api);
        SteamNetworkingMessage_t* incoming[8];
        int foundMessageCount = steamNetworkingMessagesReceiveMessages(messages, incoming, 8);
        if (foundMessageCount > 0) {
            for (int i = 0; i < foundMessageCount; ++i) {
                CLOG_VERBOSE("found message:%016llX", incoming[i]->m_nMessageNumber);
                incoming[i]->m_pfnRelease(incoming[i]);
            }
        }
        usleep(16 * 1000);
        tickCount++;
    }
}
