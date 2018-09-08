#ifndef __BUFFER_WRAPPED_BUFFER_H_
#define __BUFFER_WRAPPED_BUFFER_H_

#include "buffer.h"

namespace buffer {
    class WrappedBuffer : Buffer {
     private:
        shared_ptr<Buffer> internal;
        
        WrappedBuffer(shared_ptr<Buffer> buffer, bool readonly, int capacity);
        
        ~WrappedBuffer();

     public:
        virtual int readIndex();

        virtual void readIndex(int pos);

        virtual int writeIndex();

        virtual void writeIndex(int pos);

        virtual int capacity();

        virtual void capacity(int capacity);

        virtual void compact();

        virtual int isReadable(int length = 1);

        virtual bool isWritable(int length = 1);

        virtual void markReadIndex();

        virtual void markWriteIndex();

        virtual void resetReadIndex();

        virtual void resetWriteIndex();

        virtual void skipRead(int length);

        virtual void skipWrite(int length);

        virtual shared_ptr<Buffer> readonly();

        virtual shared_ptr<Buffer> slice(int limit = -1);

        virtual char read();

        virtual int read(char buffer[]);

        virtual void write(char c);

        virtual void write(char buffer[]);

        virtual buffer_iterator begin();

        virtual buffer_iterator end();
    };
}
#endif
