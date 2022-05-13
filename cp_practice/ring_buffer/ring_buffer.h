#ifndef __RINGBUF_H
#define __RINGBUF_H

#define RBUF_SIZE 256
typedef struct ringBufS
{
     //unsigned char buf[RBUF_SIZE];
     unsigned char *buf;
     int head;
     int tail;
     int count;
} ringBufS;

void ringBufS_init(ringBufS *_this);
int ringBufS_empty(ringBufS *_this);
int ringBufS_full(ringBufS *_this);
int ringBufS_get(ringBufS *_this);
void ringBufS_put(ringBufS *_this, const unsigned char c);
void ringBufS_flush(ringBufS *_this, const int clearBuffer);

#endif