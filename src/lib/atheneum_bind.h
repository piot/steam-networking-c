/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef STEAM_NETWORKING_ATHENEUM_BIND_H
#define STEAM_NETWORKING_ATHENEUM_BIND_H

#define ATHENEUM_BIND(formalName, fieldName)                                                                           \
    self->fieldName = (formalName) atheneumAddress(atheneum, #formalName);                                             \
    if (self->fieldName == 0) {                                                                                        \
        CLOG_ERROR("could not find '%s'", #formalName)                                                                 \
        return -1;                                                                                                     \
    }

#endif
