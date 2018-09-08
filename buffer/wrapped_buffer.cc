#include "wrapped_buffer.h"

namespace buffer {
    WrappedBuffer::WrappedBuffer(shared_ptr<Buffer> buffer, bool readonly, int limit) {
        this->internal = buffer;
    }

    int WrappedBuffer::capacity() {
      return Buffer::capacity();
    }

    void WrappedBuffer::capacity(int capacity) {
      Buffer::capacity(capacity);
    }

    void WrappedBuffer::compact() {
      // TODO: what to do with this?
    }

    bool WrappedBuffer::isReadable(int amount) {
      return this->internal->isReadable(amount);
    }

    bool WrappedBuffer::isWritable(int amount) {
      return this->internal->isWritable(amount);
    }

    shared_ptr<Buffer> WrappedBuffer::readonly() {
      if (this->_readonly) {
        return this;
      }
      shared_ptr<Buffer> ptr = shared_ptr<Buffer>(this, true, this->_capacity);
      ptr->_readonly = true;
      return ptr;
    }

    shared_ptr<Buffer> WrappedBuffer::slice(int limit) {
      int pos = this->internal->position();
      int cap = this->capacity();
      if (limit >= 0) {
        cap = min(pos + limit, cap);
      }
      WrappedBuffer* buffer = new WrappedBuffer(this->internal, this->_readonly, this->cap);
      return shared_ptr<Buffer>(buffer);
    }

    char WrappedBuffer::read() {
      // TODO: assert position < capacity
      return this->internal->read();
    }

    void read(char buffer[]) {
      // TODO: assert position < capacity
      this->internal->read(buffer);
    }

    void WrappedBuffer::write(char c) {
      // TODO: assert writable, assert position < capacity
      this->internal->write(buffer);
    }

    void WrappedBuffer::write(char buffer[]) {
      // TODO: assert writable, assert position < capacity
      this->internal->write(buffer);
    }

    buffer_iterator WrappedBuffer::begin() {
      return this->internal->begin();
    }

    buffer_iterator WrappedBuffer::end() {
      return this->internal->end();
    }
}
