#include "utils.h"
#include "tun.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/if_tun.h>

static int tun_fd;
static char* dev;

void tun_init()
{
    dev = calloc(10, 1);
    tun_fd = tun_device(dev);
}

// open tun device
// return fd, if fd >0 that not error
int tun_device(char *dev)
{
    int fd, err;

    if( (fd = open("/dev/net/tap", O_RDWR)) < 0 ) {
        perror("Cannot open TUN/TAP dev\n"
                    "Make sure one exists with " 
                    "'$ mknod /dev/net/tap c 10 200'");
        return -1;
    }

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    if( *dev ) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        perror("ERR: Could not ioctl tun");
        close(fd);
        return err;
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}


int tun_read(char *buf, int len)
{
    return read(tun_fd, buf, len);
}

int tun_write(char *buf, int len)
{
    return write(tun_fd, buf, len);
}


void tun_free()
{
    free(dev);
}
