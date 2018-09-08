#ifndef __BUFFER_BUFFER_H_
#define __BUFFER_BUFFER_H_

#include <memory>
#include <vector>

using namespace std;

typedef iterator<input_iterator_tag, char, char, const char*, char> buffer_iterator;

namespace buffer {
    class Buffer {
     private:
        vector<int> readMarkers;
        
        vector<int> writeMarkers;
        
     protected:
        int _readIndex;
        
        int _writeIndex;

        bool _readonly;
        
        shared_ptr<Buffer> _self;
     
        Buffer();
        ~Buffer();
    
     public:
        virtual int readIndex();
        
        virtual void readIndex(int pos);
        
        virtual int writeIndex();
        
        virtual void writeIndex(int pos);
        
        virtual int capacity() = 0;
        
        virtual void capacity(int capacity) = 0;
        
        virtual void compact() = 0;
        
        virtual int isReadable(int length = 1) = 0;
        
        virtual bool isWritable(int length = 1) = 0;
        
        virtual void markReadIndex();
        
        virtual void markWriteIndex();
        
        virtual void resetReadIndex();
        
        virtual void resetWriteIndex();
        
        virtual void skipRead(int length);
        
        virtual void skipWrite(int length);
        
        virtual weak_ptr<Buffer> readonly();
        
        virtual weak_ptr<Buffer> slice(int limit = 0);
        
        virtual char read() = 0;
        
        virtual int read(char buffer[]) = 0;
        
        virtual void write(char c) = 0;
        
        virtual void write(char buffer[]) = 0;
        
        virtual buffer_iterator begin() = 0;
        
        virtual buffer_iterator end() = 0;
    };
};
#endif
