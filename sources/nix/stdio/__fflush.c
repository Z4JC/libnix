#include <errno.h>
#include <unistd.h>
#include "stdio.h"

int __fflush(FILE *stream) /* fflush exactly one file */
{
	unsigned char *subbuf;
	long size, subsize;

	__STDIO_LOCK(stream);
	if (stream->_flags & __SERR) /* Error on stream */
	{
		errno = EPERM;
		__STDIO_UNLOCK(stream);
		return EOF;
	}
	if (stream->_flags & __SWR) /* Works only on output streams */
	{
		size = stream->_p - stream->_bf._base; /* calculate size */
		subbuf = stream->_bf._base;
		while (size) {
			if ((subsize = write(stream->file, subbuf, size)) < 0) {
				stream->_flags |= __SERR; /* error flag */
				__STDIO_UNLOCK(stream);
				return EOF;
			}
			size -= subsize;
			subbuf += subsize;
		}
		stream->_flags &= ~__SWR; /* unset write state */
		stream->_w = 0;
		stream->linebufsize = 0;
	} /* Nothing to be done for input streams */
	__STDIO_UNLOCK(stream);
	return 0;
}
