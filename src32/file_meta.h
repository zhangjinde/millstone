#ifndef _FILE_META_H_
#define _FILE_META_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <millstone.h> /* status_t  */
#include <connection.h> /* connection_t  */

extern status_t read_file_meta (connection_t * connection, typeof (((config_t *)NULL)->compress_level) * compress_level);
extern status_t send_file_meta (connection_t * connection);

#endif /* _FILE_META_H_ */
