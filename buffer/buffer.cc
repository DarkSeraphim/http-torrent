#include "buffer.h"
#include "wrapped_buffer.h"

namespace buffer {
    Buffer::Buffer() {
        this->readMarkers = vector<int>();
        this->writeMarkers = vector<int>();
        this->_self = shared_ptr<Buffer>(this);
    }
    
    Buffer::~Buffer() {
      this->_self.reset();
    }
    
    int Buffer::readIndex() {
        return this->_readIndex;
    }
        
    void Buffer::readIndex(int pos) {
        this->_readIndex = pos;
    }
        
    int Buffer::writeIndex() {
        return this->_writeIndex;
    }
        
    void Buffer::writeIndex(int pos) {
        this->_writeIndex = pos;
    }
    
    void Buffer::markReadIndex() {
        this->readMarkers.push_back(this->readIndex());
    }
    
    void Buffer::markWriteIndex() {
        this->writeMarkers.push_back(this->writeIndex());
    }
    
    void Buffer::resetReadIndex() {
        // TODO: Check length, throw error
        this->readIndex(this->readMarkers.back());
        this->readMarkers.pop_back();
    }
    
    void Buffer::resetWriteIndex() {
        // TODO: Check length, throw error
        this->writeIndex(this->writeMarkers.back());
        this->writeMarkers.pop_back();
    }
    
    void Buffer::skipRead(int length) {
        this->readIndex(this->readIndex() + length);
    }
    
    void Buffer::skipWrite(int length) {
        this->writeIndex(this->writeIndex() + length);
    }
    
    weak_ptr<Buffer> Buffer::readonly() {
      return weak_ptr<Buffer>(new WrappedBuffer(this));
    }
    
    weak_ptr<Buffer> Buffer::slice(int limit) {
      return weak_ptr<Buffer>(new WrappedBuffer(this));
    }
}
