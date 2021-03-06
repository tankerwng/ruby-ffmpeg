#ifndef	RUBY_FFMPEG_VIDEO_FRAME_PRIVATE_H
#define	RUBY_FFMPEG_VIDEO_FRAME_PRIVATE_H

#include "ruby_ffmpeg.h"

// Internal Data
typedef struct {
	AVPicture *				picture;					// FFMPEG: Decoded picture from the stream
	int 					owner;						// Set to "1" if we own this picture and have to fully free it

	int						width;						// FFMPEG: Picture width (in pixel)
	int						height;						// FFMPEG: Picture height (in pixel)
	enum PixelFormat		format;						// FFMPEG: Format of the picture data
	VALUE					aspect_ratio;				// Ruby: aspect ratio of a pixel, or Qnil if not available
	VALUE					picture_type;				// Ruby: picture type of the frame, or Qnil of not available
	VALUE					key;						// Ruby: Qtrue if this is a key frame, Qfalse otherwise

	VALUE					timestamp;					// Ruby: timestamp for this image (in seconds), or Qnil if not available
	VALUE					duration;					// Ruby: duration of this image (in seconds), or Qnil if not available
} VideoFrameInternal;

// Object Lifetime
VALUE video_frame_alloc(VALUE klass);
void video_frame_mark(void * opaque);
void video_frame_free(void * opaque);

// Properties
VALUE video_frame_data(int argc, VALUE * argv, VALUE self);
VALUE video_frame_timestamp(VALUE self);
VALUE video_frame_duration(VALUE self);
VALUE video_frame_format(VALUE self);

VALUE video_frame_width(VALUE self);
VALUE video_frame_height(VALUE self);
VALUE video_frame_aspect_ratio(VALUE self);
VALUE video_frame_picture_type(VALUE self);
VALUE video_frame_key(VALUE self);

// Methods
VALUE video_frame_resampler(int argc, VALUE * argv, VALUE self);
VALUE video_frame_resample(VALUE self, VALUE resampler);

// Export Methods
VALUE video_frame_to_rgba(VALUE self);
VALUE video_frame_to_gd2(VALUE self);
VALUE video_frame_to_bmp(VALUE self);

// Helper Functions
void copy_buffer_with_format(VideoFrameInternal * internal, uint8_t * buffer, int format);

#endif // RUBY_FFMPEG_VIDEO_FRAME_PRIVATE_H
