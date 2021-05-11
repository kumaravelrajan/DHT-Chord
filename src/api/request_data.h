#ifndef DHT_API_REQUEST_DATA_H
#define DHT_API_REQUEST_DATA_H

#include <vector>
#include <cstdint>

namespace API
{
    struct RequestData
    {
        std::vector<uint8_t> m_rawBytes;

    private:
        [[maybe_unused]] virtual void temporary() {}
    };

    struct Request_DHT_PUT: RequestData
    {
        std::vector<uint8_t> key, value;
    };

    struct Request_DHT_GET: RequestData
    {
        std::vector<uint8_t> key;
    };
} // namespace API

#endif //DHT_REQUEST_DATA_H
