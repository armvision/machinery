#ifndef KERBEROS_WEBRTCSTREAM_H
#define KERBEROS_WEBRTCSTREAM_H

#include "capture/BaseStream.h"

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>


namespace kerberos
{
    char WebRTCStreamName[] = "WebRTCStream";
    class WebRTCStream : public StreamCreator<WebRTCStreamName, WebRTCStream>
    {

        bool m_enabled;
        std::string m_signallingUrl;

        public:

            WebRTCStream()
            {

            }

            virtual ~WebRTCStream(){};

            void setup(kerberos::StringMap & settings);
            void configureStream(StringMap & settings);
            bool release();
            bool open();
            bool isOpened();
            bool connect();
            void write(Image image);
    };
}
#endif //KERBEROS_WEBRTCSTREAM_H

