#include "capture/WebRTCStream.h"
#include "api.h"

namespace kerberos
{
    void WebRTCStream::setup(kerberos::StringMap & settings)
    {
        configureStreams(settings);
    }
    // ----------------------------------
    // Configure stream thread settings

    void WebRTCStream::configureStreams(StringMap & settings)
    {
        //read url from settings
        m_signallingUrl = settings.at("streams.WebRTCStream.signallingUrl");
        m_enabled = (settings.at("streams.WebRTCStream.enabled") == "true");
        int fps = std::atoi(settings.at("streams.WebRTCStream.fps").c_str());
        m_turnserver = settings.at("streams.WebRTCStream.turnserver");
        m_turnserver_username = settings.at("streams.WebRTCStream.turnserverUserName");
        m_turnserver_password = settings.at("streams.WebRTCStream.turnserverPassword");
        configureStream(m_turnserver, m_turnserver_username, m_turnserver_password, m_signallingUrl);

        wait = 1. / fps;
    }

    bool WebRTCStream::release()
    {
        //release webrtc here

        LINFO << "Stream: Succesfully closed streaming";
        releaseRTC();

        return false;
    }

    bool WebRTCStream::open()
    {
        if(m_enabled)
        {

            //open webrtc here
            //LINFO << "Stream: Configured stream on port " << helper::to_string(m_streamPort) << " with quality: " << helper::to_string(m_quality);
            return openRTC();
        }

        return false;
    }

    bool WebRTCStream::isOpened()
    {
        return isRTCOpened();
    }

    bool WebRTCStream::connect()
    {
        //connect webrtc here
        return true;
    }

    void WebRTCStream::write(Image image)
    {
        try
        {
            // Check if some clients connected
            // if not drop this shit..
            //if(clients.size()==0) return;

            // Encode the image
            cv::Mat frame = image.getImage();
            if(frame.cols > 0 && frame.rows > 0)
            {
                if (isRTCOpened()) {
                    writeRTC(frame);
                }
            }


        }
        catch(cv::Exception & ex){}
    }
}
