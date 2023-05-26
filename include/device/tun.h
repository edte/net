#ifndef _TUN_H
#define _TUN_H

int tun_device(char *dev);
void tun_init();
int tun_read(char *buf, int len);
int tun_write(char *buf, int len);
void tun_free();

#endif
