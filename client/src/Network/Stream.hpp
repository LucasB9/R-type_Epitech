#pragma once

#include <vector>
#include <iostream>
#include <string>

namespace TypesLitterals {
    constexpr char operator""_c(unsigned long long c) { return static_cast<char>(c); }
    constexpr short operator""_s(unsigned long long c) { return static_cast<short>(c); }
    constexpr int operator""_i(unsigned long long c) { return static_cast<int>(c); }
    constexpr u_char operator""_uc(unsigned long long c) { return static_cast<u_char>(c); }
    constexpr u_short operator""_us(unsigned long long c) { return static_cast<u_short>(c); }
    constexpr u_int operator""_ui(unsigned long long c) { return static_cast<u_int>(c); }
}

class Stream
{
private:
    std::vector<unsigned char> _buffer;

public:
    Stream();
    Stream(const Stream &stream);
    Stream(const std::vector<unsigned char> &buffer);
    Stream(const std::string &str);
    Stream(const char str[], size_t size);
    ~Stream();

    const std::vector<unsigned char> &getBuffer() const;

    void operator += (const Stream &stream);
    void operator += (const unsigned char &data);
    void operator += (const std::string &str);

    Stream operator = (const Stream &stream);

    unsigned char operator[](size_t index) const;
    unsigned char operator[](size_t index);

    void setDataCharArray(const char *data, size_t size);

    void setDataUInt(unsigned int data);
    void setDataUShort(unsigned short data);
    void setDataUChar(unsigned char data);
    void setDataInt(int data);
    void setDataShort(short data);
    void setDataChar(char data);

    Stream &operator<<(const Stream &stream);
    Stream &operator<<(u_char data);
    Stream &operator<<(u_short data);
    Stream &operator<<(u_int data);
    Stream &operator<<(char data);
    Stream &operator<<(short data);
    Stream &operator<<(int data);
    Stream &operator<<(bool data);

    size_t size() const;
    void clear();

    unsigned int getDataUInt();
    unsigned short getDataUShort();
    unsigned char getDataUChar();
    int getDataInt();
    short getDataShort();
    char getDataChar();

    Stream &operator>>(u_char &data);
    Stream &operator>>(u_short &data);
    Stream &operator>>(u_int &data);
    Stream &operator>>(char &data);
    Stream &operator>>(short &data);
    Stream &operator>>(int &data);
    Stream &operator>>(bool &data);

    Stream subStream(size_t pos) const;
    Stream subStream(size_t pos, size_t len) const;
    std::string toString() const;

    class SubStreamError : public std::exception
    {
    public:
        std::string _message;
        const char *what() const noexcept override { return _message.c_str(); }
    };

};

std::ostream &operator<<(std::ostream &os,const Stream &stream);
