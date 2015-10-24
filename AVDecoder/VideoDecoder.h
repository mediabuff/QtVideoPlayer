#ifndef VIDEODECODER_H
#define VIDEODECODER_H
#include "AVDecoder.h"
//#include <QtAV/VideoFrame.h>
#include "FactoryDefine.h"
#include "avdecoder_global.h"

class QSize;
struct SwsContext;

typedef int VideoDecoderId;
class VideoDecoder;
FACTORY_DECLARE(VideoDecoder)

/*!
    Useful properties.
    A key is a string, a value can be int, bool or string. Both int and string are valid for enumerate
    properties. Flag properties must use int if more than 1 value is used.
    e.g. decoder->setProperty("display", 1) equals decoder->setProperty("display", "GLX")
    setOptions() also applies the properties.
    avcodec (also for VA-API, DXVA, VDA)
      Use AVCodecContext options
    CUDA
      surfaces: 0 is auto
      deinterlace: 0 "Weave", 1 "Bob", 2 "Adaptive"
    VA-API
      display: 0 "X11", 1 "GLX", 2 "DRM"
    DXVA, VA-API
      surfaces: 0 default
    DXVA, VA-API, VDA:
      sse4: bool
    CedarV
      neon: bool
    FFmpeg
      skip_loop_filter, skip_idct, skip_frame: -16 "None", 0: "Default", 8 "NoRef", 16 "Bidir", 32 "NoKey", 64 "All"
      threads: int, 0 is auto
      vismv(motion vector visualization): flag, 0 "NO", 1 "PF", 2 "BF", 4 "BB"
 */

class VideoDecoderPrivate;
class AVDECODER_EXPORT VideoDecoder : public AVDecoder
{
    DPTR_DECLARE_PRIVATE(VideoDecoder)
public:
    static VideoDecoder* create(VideoDecoderId id);
    /*!
     * \brief create
     * create a decoder from registered name
     * \param name can be "FFmpeg", "CUDA", "VDA", "VAAPI", "DXVA", "Cedarv"
     * \return 0 if not registered
     */
    static VideoDecoder* create(const QString& name);
    VideoDecoder();
    virtual VideoDecoderId id() const = 0;
    virtual QString name() const; //name from factory
    virtual bool prepare();
    virtual bool decode(const QByteArray &encoded);
    virtual VideoFrame frame();
    //TODO: new api: originalVideoSize()(inSize()), decodedVideoSize()(outSize())
    //size: the decoded(actually then resized in ImageConverter) frame size
    void resizeVideoFrame(const QSize& size);
    virtual void resizeVideoFrame(int width, int height);
    //TODO: decodedSize()
    int width() const;
    int height() const;

protected:
    VideoDecoder(VideoDecoderPrivate& d);
};

#endif // QTAV_VIDEODECODER_H
