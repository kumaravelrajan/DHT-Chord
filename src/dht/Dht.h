#ifndef DHT_DHT_H
#define DHT_DHT_H

#include <api.h>
#include <future>
#include <utility>
#include <vector>
#include <cstddef>
#include <memory>
#include <message_data.h>
#include <shared_mutex>
#include <peer.capnp.h>
#include "Peer.h"

namespace dht
{
    struct Options
    {
        std::string address = "127.0.0.1";
        uint16_t port = 6969;
    };

    class Dht
    {
    public:
        explicit Dht(Options options = {}) :
            m_options(std::move(options)),
            m_mainLoop(std::async(std::launch::async, [this]() { mainLoop(); }))
        {}
        ~Dht()
        {
            m_api = nullptr;
            m_dhtRunning = false;
            m_mainLoop.wait(); // This happens after the destructor anyway, but this way it is clearer
        };
        Dht(const Dht &) = delete;
        Dht(Dht &&) = delete;

        /**
         * The api is used to receive requests.
         * @param api - unique, transfers ownership
         */
        void setApi(std::unique_ptr<api::Api> api);

    private:
        /**
         * This is where the actual work happens.
         * mainLoop is called asynchronously from the constructor of Dht.
         * It needs to worry about stopping itself.
         */
        void mainLoop();

        Options m_options;

        std::string getSuccessor(kj::Vector <kj::byte> key) const;
        std::vector<uint8_t> onDhtPut(const api::Message_KEY_VALUE &m, std::atomic_bool &cancelled);
        std::vector<uint8_t> onDhtGet(const api::Message_KEY &m, std::atomic_bool &cancelled);

        std::future<void> m_mainLoop;
        std::unique_ptr<api::Api> m_api;
        std::atomic_bool m_dhtRunning{true};
    };
}

#endif //DHT_DHT_H
