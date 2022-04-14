//
// BCOVGoogleCastManager.h
// BrightcoveGoogleCast
//
// Copyright (c) 2022 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

/**
 * The application ID of the Brightcove CAF Receiver
 */
extern NSString * _Nonnull const kBCOVCAFReceiverApplicationID;

@class GCKUICastButton, GCKImage, GCKMediaInformationBuilder, BCOVSource, GCKMediaLoadOptions;

/**
 * Conform to this protocol to receive information about the state
 * the Google Cast session
 */
@protocol BCOVGoogleCastManagerDelegate<NSObject>


@property (nonatomic, strong, readonly) id<BCOVPlaybackController> _Nullable playbackController;

@optional

/**
 * @abstract This method is called when a cast session ends
 *
 * @discussion You can use this to show/hide UI elements, or trigger
 * other events, once a cast session ends
 *
 * @param lastKnownStreamPosition An NSTimeInterval value of the last known stream position
 * @param error If we received an error from the Google Cast SDK, it will be passed through here
 *
 */
- (void)switchedToLocalPlayback:(NSTimeInterval)lastKnownStreamPosition withError:(nullable NSError *)error;

/**
 * @abstract This method is called when a cast session starts
 *
 * @discussion You can use this to show/hide UI elements, or trigger
 * other events, once a cast session begins.
 */
- (void)switchedToRemotePlayback;

/**
 * @abstract This method is called when a cast video has finished playing.
 *
 * @discussion You can use this to show/hide UI elements, or trigger
 * other events, once a cast video has completed playback
 */
- (void)currentCastedVideoDidComplete;

/**
 * @abstract This method is called when a cast video fails to play.
 *
 * @discussion You can use this to show/hide UI elements, or trigger
 * other events, once a cast video fails to play
 */
- (void)castedVideoFailedToPlay;

/**
 * @abstract This method is called when a suitable source is not found.
 *
 * @discussion The BCOVGoogleCastManager will look for HTTPS version of
 * HLS v3, then check for DASH, and finally an MP4 source. If no HTTPS
 * versions are found it will then check for HTTP versions of the same
 * source types. If no HTTP versions are found this method will be called.
 */
- (void)suitableSourceNotFound;

/**
 * @discussion This method is called prior to calling `build` on the current
 * instance of GCKMediaInformationBuilder set up for the current video about
 * to be cast. This will allow you to add any additional values to the builder
 * as needed. You can use this method to pass custom data to the builder in
 * your receiver app.
 */
- (void)willBuildMediaInformationBuilder:(GCKMediaInformationBuilder *_Nonnull)builder;

/**
 * @abstract This method is called prior invoking `loadMedia:withOptions` on
 * the current cast session's remoteMediaClient.
 *
 * @discussion You can use this delegate method to further configure GCKMediaLoadOptions
 * as needed prior to it being sent fo the remoteMediaClient.
 */
- (void)willSendMediaLoadOptions:(GCKMediaLoadOptions *_Nonnull)mediaLoadOptions;

/**
 * @abstract This method is called when a source needs to be parsed prior to being cast.
 *
 * @discussion You can use this method to specify the source you want to be used
 * with the Cast Receiver.
 * If you do not implement this method, BCOVGoogleCastManager
 * will perform source selecton on its own (see `suitiableSourceNotFound` for more information).
*/
- (BCOVSource *_Nonnull)useSourceFromSources:(NSArray<BCOVSource *> *_Nonnull)sources;

/**
 * @abstract This method is called after BCOVGoogleCastManager has
 * received a new playback session.
 *
 * @discussion When BCOVGoogleCastManager receives a new BCOVVideo from a playback
 * session it will attempt to compare it to the previous BCOVVideo, if there is one, to prevent the cast
 * session from restarting with the same video. You can use this method to override the internal check
 * so that you have control over if the current video should be cast or not.
 */
-(BOOL)shouldCastVideo:(BCOVVideo *_Nonnull)video;

@end

NS_ASSUME_NONNULL_BEGIN

@interface BCOVGoogleCastManager : NSObject<BCOVPlaybackSessionConsumer>

/**
 * @abstract Resets the state of the BCOVGoogleCastManager instance
 *
 * @discussion If using a shared BCOVGoogleCastManager instance across
 * view controllers you can call this method as needed to clear out data pertaining
 * to the previously cast video.
 */
- (void)prepareForReuse;

/**
 * The delegate object that will receive events from the manager
 */
@property (nonatomic, weak) id<BCOVGoogleCastManagerDelegate> delegate;

/**
 * The GCKImage that will be used when there is no poster image
 * available for a video
 */
@property (nonatomic, strong) GCKImage *fallbackPosterImage;

/**
 * The height and width that you want to use for the GCKImage object
 * image that is created. Defaults to 480h x 720w
 */
@property (nonatomic, assign) CGSize posterImageSize;
/**
 * Whether to use a language variant, if available, with GCKMediaMetadata
 *
 * Defaults to YES
 */
@property (nonatomic, assign) BOOL useLocalizedVariantForCastMediaMedadata;

@end

NS_ASSUME_NONNULL_END
