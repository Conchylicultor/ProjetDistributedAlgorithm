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
    std::list<Message> messagesSent; // After acknowledgement

    // When remove the messages sent ? (when the message has been brodcast to all receiver ?)
public:
    MessageManager();
};

#endif // MESSAGEMANAGER_H
