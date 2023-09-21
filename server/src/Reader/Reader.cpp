#include "Reader.hpp"

Reader::Reader(asio::ip::udp::socket &socket, Queue<Reader::Packet> &queueIn, std::vector<std::shared_ptr<Client>> &clients): _socket(socket), _queueIn(queueIn), _clients(clients)
{
    _thread = std::thread(&Reader::Clock, this);
}

Reader::~Reader()
{
    _thread.join();
}

void Reader::Clock()
{
    asio::ip::udp::endpoint sender;
    bool pass = false;
    std::pair<size_t, std::string> tmpInst;
    enum
    {
        max_length = 1024
    };
    char data[max_length];

    while (true)
    {
        pass = false;
        asio::error_code ec;
        size_t len = this->_socket.receive_from(asio::buffer(data, max_length), sender, 0, ec);
        data[len] = '\0';

        for (auto i = this->_clients.begin(); i != this->_clients.end(); i++)
        {
            if ((**i).getEndpoint() == sender) {
                pass = true;
                (**i).pushBuffer(std::string(data));
                while ((tmpInst = (**i).getNextInst()).first != 0) {
                    _queueIn.push(Reader::Packet(*i, tmpInst.second, tmpInst.first));
                }
                break;
            }
        }

        if (!pass)
        {
            this->_clients.push_back(std::make_shared<Client>(_socket, sender));
            this->_clients.back()->pushBuffer(std::string(data));
            while ((tmpInst = this->_clients.back()->getNextInst()).first != 0) {
                _queueIn.push(Reader::Packet(this->_clients.back(), tmpInst.second, tmpInst.first));
            }
        }

        if (ec)
        {
            Reader::ReadError error;
            error._message = "Error during receive: " + ec.message();
            throw error;
        }
    }
}

Reader::Packet::Packet(std::shared_ptr<Client> client, const std::string &data, int instruction) : _client(client), _data(data), _instruction(instruction)
{
}

Reader::Packet::~Packet()
{
}

int Reader::Packet::getInstruction() const
{
    return _instruction;
}

const std::string &Reader::Packet::getData() const
{
    return _data;
}

std::shared_ptr<Client> Reader::Packet::getClient() const
{
    return _client;
}

int Reader::Packet::getDataInt()
{
    int out = 0;
    out += this->_data[0];
    out += this->_data[1] << 8;
    out += this->_data[2] << 16;
    out += this->_data[3] << 24;
    this->_data = this->_data.substr(4);
    return out;
}

short Reader::Packet::getDataShort()
{
    short out = 0;
    out += this->_data[0];
    out += this->_data[1] << 8;
    this->_data = this->_data.substr(2);
    return out;
}

char Reader::Packet::getDataChar()
{
    char out = 0;
    out += this->_data[0];
    this->_data = this->_data.substr(1);
    return out;
}
