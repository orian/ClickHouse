-- Tags: shard

-- remote() does not have sharding key, while force_optimize_skip_unused_shards=2 requires from table to have it.
-- But due to only one node, everything works.

SET allow_experimental_parallel_reading_from_replicas = 0;

select * from remote('127.1', system.one) settings optimize_skip_unused_shards=1, force_optimize_skip_unused_shards=2 format Null;
