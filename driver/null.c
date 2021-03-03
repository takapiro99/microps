#include <stdint.h>
#include <stdio.h>

#include "net.h"
#include "util.h"

#define NULL_MTU UINT16_MAX /* maximum size of IP datagram */

static int null_transmit(struct net_device *dev, uint16_t type,
                         const uint8_t *data, size_t len, const void *dst) {
  debugf("dev=%s, type=%s, len=%zu", dev->name, type, len);
  debugdump(data, len);
  // drop data
  return 0;
}

// デバイスドライバが実装している関数へのポインタ
static struct net_device_ops null_ops = {
    .transmit = null_transmit,
};

struct net_device *null_init(void) {
  struct net_device *dev;
  dev = net_device_alloc();
  if (!dev) {
    errorf("net_device_alloc() failure");
    return NULL;
  }
  dev->type = NET_DEVICE_TYPE_NULL;
  dev->mtu = NULL_MTU;
  dev->hlen = 0;  // no header;
  dev->alen = 0;  // no address;
  dev->ops = &null_ops;
  if (net_device_register(dev) == -1) {
    errorf("net_device_register() failed");
    return NULL;
  }
  debugf("initialized, dev=%s", dev->name);
  return dev;
}