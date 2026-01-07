#include "hashtable.h"

uint myhash(Item i, uint tablesize) {
  return i % tablesize;
}
