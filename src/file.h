#ifndef _FILE_H_
#define _FILE_H_

#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif /* _LARGEFILE64_SOURCE */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <millstone.h> /* status_t, config_t, MAX_BLOCK_SIZE */
#include <block.h> /* block_id_t */
#include <llist.h> /* llist_t */
#include <sync_storage.h> /* sync_storage_t */

#define _GNU_SOURCE /* TEMP_FAILURE_RETRY */
#include <fcntl.h> /* off64_t */
#include <inttypes.h> /* uint8_t */
#include <stdbool.h> /* bool */

#define MAX_MAPPED_MEMORY (1 << 30) /* 1Gb */

TYPEDEF_STRUCT (chunk_t,
		(block_id_t, block_id),
		int ref_count,
		NONE (uint8_t *, data),
		)

TYPEDEF_FUNC (void, chunk_release_t, (chunk_t * /* chunk */, void * /* context */))

TYPEDEF_STRUCT (file_t,
		(config_t *, config),
		(bool, file_exists),
		int fd,
		(off64_t, size),
		int protect,
		int flags,
		(size_t, chunk_size),
		(chunk_t, chunks, [MAX_MAPPED_MEMORY / MAX_BLOCK_SIZE]),
		(sync_storage_t, chunks_index),
		(llist_t, chunks_pool),
		(chunk_release_t, chunk_release),
		(void *, context),
		)

extern chunk_t * chunk_ref (file_t * file, off64_t offset);
extern status_t chunk_unref (file_t * file, off64_t offset);
extern void * file_chunks_get_addr (file_t * file, off64_t offset);
extern void file_chunks_init (file_t * file, int protect, int flags, size_t size);
extern void file_chunks_cancel (file_t * file);
extern void file_chunks_finilize (file_t * file);
extern void file_chunks_set_release_handler (file_t * file, chunk_release_t chunk_release, void * context);

#endif /* _FILE_H_ */