#include "request.h"

#include <iostream>
#include <utility>

using namespace API;

Request::Request(std::vector<std::byte> bytes):
    m_rawBytes(std::move(bytes))
{
    // TODO: decode data
}

Request::Request(Request &&other) noexcept
{
    if (this != &other) {
        m_rawBytes = std::move(other.m_rawBytes);
        m_decodedData = std::move(other.m_decodedData);
    }
}

Request &Request::operator=(Request &&other) noexcept
{
    if (this != &other) {
        m_rawBytes = std::move(other.m_rawBytes);
        m_decodedData = std::move(other.m_decodedData);
    }
    return *this;
}

void Request::sendReply(const std::vector<std::byte> &bytes)
{
    // TODO: send reply
    std::cout << "Send Reply!" << std::endl;
}
