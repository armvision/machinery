#include "Factory.h"
#include "capture/Image.h"

#ifndef KERBEROS_BASESTREAM_H
#define KERBEROS_BASESTREAM_H

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

namespace kerberos {

    class BaseStream {

    protected:
        const char * name;

    public:

        BaseStream(){};

        virtual ~BaseStream(){};

        virtual void setup(kerberos::StringMap & settings) = 0;
        virtual void configureStreams(StringMap &settings) = 0;
        virtual bool release() = 0;
        virtual bool open() = 0;
        virtual bool isOpened() = 0;
        virtual bool connect() = 0;
        virtual void write(Image image) = 0;
        double wait;
    };

    template<const char *Alias, typename Class>
    class StreamCreator : public BaseStream {
    protected:
        StreamCreator() { name = ID; }

    public:
        static BaseStream *create() { return new Class(); };
        static const char *ID;
    };
}
#endif //KERBEROS_BASESTREAM_H
