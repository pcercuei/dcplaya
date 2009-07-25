/*
 * Buffered file io for ffmpeg system
 * Copyright (c) 2001 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "avformat.h"

#ifdef ARCH_SH4

#include <kos.h>
#define O_TRUNC		 01000	/* not fcntl */
#define O_CREAT		 0100	/* not fcntl */

/* standard file protocol */

/* VP : dcplaya extensions  */
int ff_packet_size = 16*1024;
int ff_cur_fd;

static int file_open(URLContext *h, const char *filename, int flags)
{
    int access;
    file_t fd;

    strstart(filename, "file:", &filename);
    if (flags & URL_RDWR) {
        access = O_CREAT | O_TRUNC | O_RDWR;
    } else if (flags & URL_WRONLY) {
        access = O_CREAT | O_TRUNC | O_WRONLY;
    } else {
        access = O_RDONLY;
    }

    //printf("Trying to open '%s' with access %x\n", filename, access);

    fd = fs_open(filename, access);
    if (fd == 0)
        return -ENOENT;
    //printf("SUCCESS !\n");

    h->max_packet_size = ff_packet_size;
    ff_cur_fd = fd;

    h->priv_data = (void *)(size_t)fd;
    return 0;
}

static int file_read(URLContext *h, unsigned char *buf, int size)
{
  file_t fd = (size_t)h->priv_data;
    return fs_read(fd, buf, size);
}

static int file_write(URLContext *h, unsigned char *buf, int size)
{
  file_t fd = (size_t)h->priv_data;
    return fs_write(fd, buf, size);
}

/* XXX: use llseek */
static offset_t file_seek(URLContext *h, offset_t pos, int whence)
{
  file_t fd = (size_t)h->priv_data;
    return fs_seek(fd, pos, whence);
}

static int file_close(URLContext *h)
{
  file_t fd = (size_t)h->priv_data;
  fs_close(fd);

  ff_cur_fd = -1;

  return 0;
}

URLProtocol file_protocol = {
    "file",
    file_open,
    file_read,
    file_write,
    file_seek,
    file_close,
};

/* pipe protocol */

static int pipe_open(URLContext *h, const char *filename, int flags)
{
    return -1;
}

static int pipe_read(URLContext *h, unsigned char *buf, int size)
{
  return -1;
}

static int pipe_write(URLContext *h, unsigned char *buf, int size)
{
  return -1;
}

static int pipe_close(URLContext *h)
{
  return -1;
}

URLProtocol pipe_protocol = {
    "pipe",
    pipe_open,
    pipe_read,
    pipe_write,
    NULL,
    pipe_close,
};


#else
#include <fcntl.h>
#ifndef CONFIG_WIN32
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#else
#include <io.h>
#define open(fname,oflag,pmode) _open(fname,oflag,pmode)
#endif /* CONFIG_WIN32 */


/* standard file protocol */

static int file_open(URLContext *h, const char *filename, int flags)
{
    int access;
    int fd;

    strstart(filename, "file:", &filename);

    if (flags & URL_RDWR) {
        access = O_CREAT | O_TRUNC | O_RDWR;
    } else if (flags & URL_WRONLY) {
        access = O_CREAT | O_TRUNC | O_WRONLY;
    } else {
        access = O_RDONLY;
    }
#if defined(CONFIG_WIN32) || defined(CONFIG_OS2) || defined(__CYGWIN__)
    access |= O_BINARY;
#endif
    fd = open(filename, access, 0666);
    if (fd < 0)
        return -ENOENT;
    h->priv_data = (void *)(size_t)fd;
    return 0;
}

static int file_read(URLContext *h, unsigned char *buf, int size)
{
    int fd = (size_t)h->priv_data;
    return read(fd, buf, size);
}

static int file_write(URLContext *h, unsigned char *buf, int size)
{
    int fd = (size_t)h->priv_data;
    return write(fd, buf, size);
}

/* XXX: use llseek */
static offset_t file_seek(URLContext *h, offset_t pos, int whence)
{
    int fd = (size_t)h->priv_data;
#if defined(CONFIG_WIN32) && !defined(__CYGWIN__) 
    return _lseeki64(fd, pos, whence);
#else
    return lseek(fd, pos, whence);
#endif
}

static int file_close(URLContext *h)
{
    int fd = (size_t)h->priv_data;
    return close(fd);
}

URLProtocol file_protocol = {
    "file",
    file_open,
    file_read,
    file_write,
    file_seek,
    file_close,
};

/* pipe protocol */

static int pipe_open(URLContext *h, const char *filename, int flags)
{
    int fd;

    if (flags & URL_WRONLY) {
        fd = 1;
    } else {
        fd = 0;
    }
#if defined(CONFIG_WIN32) || defined(CONFIG_OS2) || defined(__CYGWIN__)
    setmode(fd, O_BINARY);
#endif
    h->priv_data = (void *)(size_t)fd;
    return 0;
}

static int pipe_read(URLContext *h, unsigned char *buf, int size)
{
    int fd = (size_t)h->priv_data;
    return read(fd, buf, size);
}

static int pipe_write(URLContext *h, unsigned char *buf, int size)
{
    int fd = (size_t)h->priv_data;
    return write(fd, buf, size);
}

static int pipe_close(URLContext *h)
{
    return 0;
}

URLProtocol pipe_protocol = {
    "pipe",
    pipe_open,
    pipe_read,
    pipe_write,
    NULL,
    pipe_close,
};
#endif
