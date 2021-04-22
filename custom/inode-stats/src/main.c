// Credit: https://stackoverflow.com/a/42666377/10714490

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    dev_t       device[argc];
    int         devices = 0;
    uint64_t    total_inodes = 0;
    uint64_t    avail_inodes = 0; /* Free to normal users */
    uint64_t    free_inodes = 0;  /* Free to superuser */
    int         arg, i;

    if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        printf("\n");
        printf("Usage: %s [ -h | --help ]\n", argv[0]);
        printf("       %s mountpoint [ mountpoint ... ]\n", argv[0]);
        printf("\n");
        printf("This program will report the percentage of inodes in use,\n");
        printf("the number free inodes available for normal users,\n");
        printf("the number of free inodes available for root,\n");
        printf("and the total number of inodes,\n");
        printf("in the filesystems referred to the supplied paths.\n");
        printf("\n");
        printf("Each mount is only counted once, even if multiple paths\n");
        printf("to the same mount are given as parameters.\n");
        printf("\n");
        return EXIT_SUCCESS;
    }

    for (arg = 1; arg < argc; arg++) {
        struct stat     info;
        struct statvfs  vfsinfo;

        if (stat(argv[arg], &info) == -1) {
            fprintf(stderr, "%s: %s.\n", argv[arg], strerror(errno));
            continue;
        }
        if (statvfs(argv[arg], &vfsinfo) == -1) {
            fprintf(stderr, "%s: %s.\n", argv[arg], strerror(errno));
            continue;
        }

        /* Check if device already seen. */
        for (i = 0; i < devices; i++)
            if (info.st_dev == device[i])
                break;
        if (i < devices)
            continue;

        /* Add to known devices. */
        device[devices++] = info.st_dev;

        /* Add to inode counters. */
        total_inodes += (uint64_t)vfsinfo.f_files;
        avail_inodes += (uint64_t)vfsinfo.f_favail;
        free_inodes  += (uint64_t)vfsinfo.f_ffree;
    }

    if (total_inodes < 0) {
        fprintf(stderr, "No inodes!\n");
        return EXIT_FAILURE;
    }

    /* Print result. */
    printf("%.3f%% - %" PRIu64 " free (%" PRIu64 " for root) out of %" PRIu64 " inodes.\n",
           100.0 - 100.0 * (double)avail_inodes / (double)total_inodes,
           avail_inodes, free_inodes, total_inodes);
    return EXIT_SUCCESS;
}
