#pragma once

//подключаем "hash.h"
#include <string>

// определение целочисленных типов фиксированного размера
#ifdef _MSC_VER
// Windows
typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
// GCC
#include <stdint.h>
#endif

class SHA256 //: публичный хэш
{
public:
    // split into 64 byte blocks (=> 512 bits), hash is 32 bytes long
    enum { BlockSize = 512 / 8, HashBytes = 32 };

    // то же самое, что и сброс()
    SHA256();

    // вычислить SHA256 блока памяти
    std::string operator()(const void* data, size_t numBytes);
    // вычислить SHA256 строки, исключая последний ноль
    std::string operator()(const std::string& text);

    // добавить произвольное количество байтов
    void add(const void* data, size_t numBytes);

    //возвращает последний хэш в виде 64 шестнадцатеричных символов
    std::string getHash();
    //возвращает последний хэш в виде байтов
    void        getHash(unsigned char buffer[HashBytes]);

    //рестарт
    void reset();

private:
    //обрабатывает 64 байт
    void processBlock(const void* data);
    //обработать все, что осталось во внутреннем буфере
    void processBuffer();

    //размер обрабатываемых данных в байтах
    uint64_t m_numBytes;
    //допустимые байты в m_buffer
    size_t   m_bufferSize;
    //байты еще не обработаны
    uint8_t  m_buffer[BlockSize];

    enum { HashValues = HashBytes / 4 };
    //хэш, хранящийся в виде целых чисел
    uint32_t m_hash[HashValues];
};
