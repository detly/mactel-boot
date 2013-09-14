/*
 * bless.c - make hfs+ filesystems bootable
 *
 * Copyright 2011 Red Hat <mjg@redhat.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/vfs.h>
#include <fcntl.h>

#define HFSPLUS_IOC_BLESS _IO('h', 0x80)

int main(int argc, char **argv) {
	int fd;
	struct statfs fsinfo;

	if (argc != 2) {
		fprintf(stderr, "usage: %s filename\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDWR);

	if (fd < 0) {
		perror("Unable to open file");
		return -2;
	}

	if (fstatfs(fd, &fsinfo)) {
		perror("Unable to stat filesystem");
		return -3;
	}

	if (fsinfo.f_type != 0x482b) {
		fprintf(stderr, "Not an HFS+ filesystem\n");
		return -4;
	}

	if (ioctl(fd, HFSPLUS_IOC_BLESS, NULL)) {
		perror("Unable to bless filesystem");
		return -5;
	}

	close(fd);

	return 0;
}
