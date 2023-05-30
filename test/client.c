#include "tun.h"
#include <net/if.h>
#include <linux/if_tun.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    int tun_fd, nread;
    char buffer[4096];
    char tun_name[IFNAMSIZ];

    tun_name[0] = '\0';

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *        IFF_NO_PI - Do not provide packet information
     */
    tun_fd = tun_device(tun_name);

    if (tun_fd < 0) {
        perror("Allocating interface");
        exit(1);
    }

    printf("Open tun/tap device: %s for reading...\n", tun_name);
    
    while (1) {
        unsigned char ip[4];
        // 收包
        // tun_read(, int len)
        nread = read(tun_fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("Reading from interface");
            close(tun_fd);
            exit(1);
        }
        
        printf("Read %d bytes from tun/tap device\n", nread);
        
        // 简单对收到的包调换一下顺序
        memcpy(ip, &buffer[12], 4);
        memcpy(&buffer[12], &buffer[16], 4);
        memcpy(&buffer[16], ip, 4);

        buffer[20] = 0;
        *((unsigned short *)&buffer[22]) += 8;
        
        // 发包
        nread = write(tun_fd, buffer, nread);

        printf("Write %d bytes to tun/tap device, that's %s\n", nread, buffer);
    }
    return 0;
}
