#include <string.h>
#include <stdio.h>
#include "ring_buffer.h"

int modulo_inc(const int value, const int modules)
{
    int my_value = value + 1;
    if (my_value >= modules)
    {
        my_value = 0;
    }
    return my_value;
}

int modulo_dec(const int value, const int modules)
{
    int my_value = (0 == value) ? (modules - 1) : (value - 1);
    return my_value;
}

void ringBufS_init(ringBufS *_this)
{
    /*****
     * The following clears:
     * -> buf
     * -> head
     * -> tail
     * -> count
     * and sets head = tail
     ***/
    memset(_this, 0, sizeof(*_this));
}

int ringBufS_empty(ringBufS *_this)
{
    return (0 == _this->count);
}

int ringBufS_full(ringBufS *_this)
{
    return (_this->count >= RBUF_SIZE);
}

int ringBufS_get(ringBufS *_this)
{
    int c;
    if (_this->count > 0)
    {
        c = _this->buf[_this->tail];
        _this->tail = modulo_inc(_this->tail, RBUF_SIZE);
        --_this->count;
    }
    else
    {
        c = -1;
    }
    return (c);
}

void ringBufS_put(ringBufS *_this, const unsigned char c)
{
    if (_this->count < RBUF_SIZE)
    {
        _this->buf[_this->head] = c;
        _this->head = modulo_inc(_this->head, RBUF_SIZE);
        ++_this->count;
    }
}

void ringBufS_flush(ringBufS *_this, const int clearBuffer)
{
    _this->count = 0;
    _this->head = 0;
    _this->tail = 0;
    if (clearBuffer)
    {
        memset(_this->buf, 0, sizeof(_this->buf));
    }
}

void main()
{
    unsigned char buff[RBUF_SIZE];
    ringBufS my_ringBuffer;
    ringBufS_init(&my_ringBuffer);
    my_ringBuffer.buf = buff;

    int my_status, i;
    printf("\nfifo empty status = %d", ringBufS_empty(&my_ringBuffer));

    puts("\nThe following is the FIFO FULL status");
    for (i = 0; i < RBUF_SIZE; i++)
    {
        ringBufS_put(&my_ringBuffer, (unsigned char)i);
        my_status = ringBufS_full(&my_ringBuffer);
        if (0 == (i % 16))
        {
            putchar('\n');
        }
        printf("%2d ", my_status);
    }

    printf("\nfifo empty status = %d", ringBufS_empty(&my_ringBuffer));
    puts("\nThe following is the contents of the FIFO");
    for (i = 0; i < RBUF_SIZE; i++)
    {
        int my_datum = ringBufS_get(&my_ringBuffer);
        if (0 == (i % 16))
        {
            putchar('\n');
        }
        printf("%02X ", my_datum);
    }
    printf("\nfifo empty status = %d", ringBufS_empty(&my_ringBuffer));

    putchar('\n');
}