# Hey! I'm Filing Here

UCLA UID 506043010 TAE HWAN KIM

In this lab, I successfully implemented a basic ext2 filesystem on a 1 MiB disk image.
The implementation includes setting up the superblock, block group descriptor table, block and inode bitmaps, and inodes for specific directories and files; root, lost+found, hello-world, and hello symlink.

## Building
```shell
make
```

## Running

Run the following commands to the execute the program and mount the filesystem:
```shell
./ext2-create
mkdir mnt
sudo mount -o loop cs111-base.img mnt
ls -ain mnt
```

Run the following commands to check the filesystem for errors:
```shell
dumpe2fs cs111-base.img
fsck.ext2 cs111-base.img
```

## Cleaning up

Run the following commands to clean up:
```shell
sudo umount mnt
make clean
rmdir mnt
```