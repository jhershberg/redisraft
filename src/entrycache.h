/*
 * This file is part of RedisRaft.
 *
 * Copyright (c) 2020-2022 Redis Ltd.
 *
 * RedisRaft is licensed under the Redis Source Available License (RSAL).
 */

#ifndef REDISRAFT_ENTRYCACHE_H
#define REDISRAFT_ENTRYCACHE_H

#include "raft.h"

#include <stdlib.h>

typedef struct EntryCache {
    raft_index_t size;                 /* Size of ptrs */
    raft_index_t len;                  /* Number of entries in cache */
    raft_index_t start_idx;            /* Log index of first entry */
    raft_index_t start;                /* ptrs array index of first entry */
    unsigned long int entries_memsize; /* Total memory used by entries */
    raft_entry_t **ptrs;
} EntryCache;

EntryCache *EntryCacheNew(raft_index_t initial_size);
void EntryCacheFree(EntryCache *cache);
void EntryCacheAppend(EntryCache *cache, raft_entry_t *ety, raft_index_t idx);
raft_entry_t *EntryCacheGet(EntryCache *cache, raft_index_t idx);
long EntryCacheDeleteHead(EntryCache *cache, raft_index_t idx);
long EntryCacheDeleteTail(EntryCache *cache, raft_index_t index);
long EntryCacheCompact(EntryCache *cache, size_t max_memory);

#endif
