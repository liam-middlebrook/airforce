#include "af/PNGDecoder.h"
#include "PNGUtils.h"
#include "Logger.h"
#include <string.h>
#include <errno.h>

namespace af
{
    class PNGDecoder::Impl
    {
    public:
        Impl(const std::string& path)
        : path_(path),
          f_(NULL),
          pngPtr_(NULL),
          pngInfoPtr_(NULL),
          width_(0),
          height_(0)
        {
        }

        ~Impl()
        {
            if (pngPtr_) {
                PNGCatch(pngPtr_) {
                    pngPtr_ = NULL;
                    pngInfoPtr_ = NULL;

                    if (f_) {
                        ::fclose(f_);
                    }

                    return;
                }

                ::png_destroy_read_struct(&pngPtr_, (pngInfoPtr_ ? &pngInfoPtr_ : NULL), NULL);

                pngPtr_ = NULL;
                pngInfoPtr_ = NULL;
            }

            if (f_) {
                ::fclose(f_);
            }
        }

        std::string path_;
        FILE *f_;
        PNGError pngError_;
        png_structp pngPtr_;
        png_infop pngInfoPtr_;
        UInt32 width_;
        UInt32 height_;
    };

    PNGDecoder::PNGDecoder(const std::string& path)
    : impl_(new Impl(path))
    {
    }

    PNGDecoder::~PNGDecoder()
    {
        delete impl_;
    }

    bool PNGDecoder::init()
    {
        LOG4CPLUS_INFO(afutil::logger(), "Opening " << impl_->path_ << "...");

        impl_->f_ = ::fopen(impl_->path_.c_str(), "rb");

        if (!impl_->f_) {
            int error = errno;

            LOG4CPLUS_ERROR(afutil::logger(), "Cannot open " << impl_->path_ << ": " << ::strerror(error));

            return false;
        }

        impl_->pngPtr_ = PNGCreateReadStruct(impl_->pngError_);

        if (!impl_->pngPtr_) {
            LOG4CPLUS_ERROR(afutil::logger(), "Cannot create PNG read struct");

            return false;
        }

        PNGCatch(impl_->pngPtr_) {
            LOG4CPLUS_ERROR(afutil::logger(), "Error reading PNG file");

            return false;
        }

        impl_->pngInfoPtr_ = ::png_create_info_struct(impl_->pngPtr_);

        if (!impl_->pngInfoPtr_) {
            LOG4CPLUS_ERROR(afutil::logger(), "Cannot create PNG info struct");

            return false;
        }

        ::png_init_io(impl_->pngPtr_, impl_->f_);

        ::png_read_info(impl_->pngPtr_, impl_->pngInfoPtr_);

        int bitDepth, colorType;

        ::png_get_IHDR(impl_->pngPtr_, impl_->pngInfoPtr_,
                       &impl_->width_, &impl_->height_,
                       &bitDepth, &colorType, NULL, NULL, NULL);

        if ((impl_->width_ == 0) ||
            (impl_->height_ == 0) ||
            (colorType != PNG_COLOR_TYPE_RGB_ALPHA) ||
            (bitDepth != 8)) {
            LOG4CPLUS_ERROR(afutil::logger(), "Bad PNG file");

            return false;
        }

        ::png_read_update_info(impl_->pngPtr_, impl_->pngInfoPtr_);

        if (::png_get_rowbytes(impl_->pngPtr_, impl_->pngInfoPtr_) != (impl_->width_ * 4)) {
            LOG4CPLUS_ERROR(afutil::logger(), "Bad PNG file");

            return false;
        }

        return true;
    }

    bool PNGDecoder::decode(std::vector<Byte>& data)
    {
        LOG4CPLUS_INFO(afutil::logger(), "Decoding " << impl_->path_ << "...");

        assert(impl_->pngPtr_);

        if (!impl_->pngPtr_) {
            LOG4CPLUS_ERROR(afutil::logger(), "PNG decoder not initialized");

            return false;
        }

        PNGCatch(impl_->pngPtr_) {
            LOG4CPLUS_ERROR(afutil::logger(), "Error reading PNG file");

            return false;
        }

        png_size_t rowBytes = ::png_get_rowbytes(impl_->pngPtr_, impl_->pngInfoPtr_);

        data.resize(rowBytes * impl_->height_);

        std::vector<png_bytep> rowPointers(impl_->height_);

        for (UInt32 i = 0; i < impl_->height_; ++i)
        {
            rowPointers[impl_->height_ - 1 - i] = &data[0] + i * rowBytes;
        }

        ::png_read_image(impl_->pngPtr_, &rowPointers[0]);

        return true;
    }

    UInt32 PNGDecoder::width() const
    {
        return impl_->width_;
    }

    UInt32 PNGDecoder::height() const
    {
        return impl_->height_;
    }
}
