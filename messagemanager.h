#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <list>

struct Message
{
    // Destinataire
    // Content (key, value)
    // bool Ack
    // VectorClock
};

class MessageManager
{
private:
    std::list<Message> messagesToSend;
    std::list<Message> messagesSent;

public:
    MessageManager();
};

#endif // MESSAGEMANAGER_H
