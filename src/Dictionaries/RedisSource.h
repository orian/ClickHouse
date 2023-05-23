#pragma once

#include <Core/Block.h>

#include <Core/ExternalResultDescription.h>
#include <Processors/ISource.h>
#include <Poco/Redis/Array.h>
#include <Poco/Redis/Type.h>
#include <Storages/RedisCommon.h>
#include "RedisDictionarySource.h"


namespace DB
{
    class RedisSource final : public ISource
    {
    public:
        RedisSource(
            RedisConnectionPtr connection_,
            const RedisArray & keys_,
            const RedisStorageType & storage_type_,
            const DB::Block & sample_block,
            size_t max_block_size);

        RedisSource(
            RedisConnectionPtr connection_,
            const RedisArray & keys_,
            const RedisStorageType & storage_type_,
            const Block & sample_block,
            const RedisColumnTypes & columns_types_,
            size_t max_block_size);

        ~RedisSource() override;

        String getName() const override { return "Redis"; }

    private:
        Chunk generate() override;

        RedisConnectionPtr connection;
        Poco::Redis::Array keys;
        RedisStorageType storage_type;
        const size_t max_block_size;
        ExternalResultDescription description;
        /// Types is corresponding to description.sample_block one by one
        RedisColumnTypes columns_types;
        size_t cursor = 0;
        bool all_read = false;
    };

}

