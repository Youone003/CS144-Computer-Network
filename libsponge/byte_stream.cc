#include "byte_stream.hh"
#include<iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
{
    //DUMMY_CODE(capacity); 
    _capacity=capacity;
}

size_t ByteStream::write(const string &data) {
    //DUMMY_CODE(data);
    size_t len=data.size();

    //std::cout<<"Write length:"<<len<<"Remaining size"<<_capacity-_buffer.size()<<endl;
    if(len>_capacity-_buffer.size())
    {
        len=_capacity-_buffer.size();
    }
    _written_size+=len;

    //std::cout<<"Actually write length:"<<len;
    
    for(size_t i=0;i<len;++i)
    {
        _buffer.push_back(data[i]);
    }

    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    //DUMMY_CODE(len);
    //Did not change any data
    size_t length=len;
    if(length>_buffer.size())
    {
        length=_buffer.size();
    }
    
    return string().assign(_buffer.begin(),_buffer.begin()+length) ;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) 
{ 
    //DUMMY_CODE(len); 
    size_t length=len;
    if(length>_buffer.size())
    {
        length=_buffer.size();
    }
    _read_size+=length;
    while(length--)
    {
        _buffer.pop_front();
    }
    
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    //DUMMY_CODE(len);
    size_t length=len;
    if(length>_buffer.size())
    {
        length=_buffer.size();
    }
    _read_size+=length;
    string data=string().assign(_buffer.begin(),_buffer.begin()+length);
    ByteStream::pop_output(length);
    return data;
}

void ByteStream::end_input() {_write_end=true;}

bool ByteStream::input_ended() const { return _write_end; }

size_t ByteStream::buffer_size() const { return _buffer.size(); }

bool ByteStream::buffer_empty() const { return _buffer.size()==0; }

bool ByteStream::eof() const { return buffer_empty()&&input_ended(); }

size_t ByteStream::bytes_written() const { return _written_size; }

size_t ByteStream::bytes_read() const { return _read_size; }

size_t ByteStream::remaining_capacity() const { return _capacity-_buffer.size(); }
