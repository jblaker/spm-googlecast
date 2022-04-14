//
// BCOVReceiverAppConfig.h
// BrightcoveGoogleCast
//
// Copyright (c) 2022 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import "BCOVGoogleCastManager.h"

NS_ASSUME_NONNULL_BEGIN

@interface BCOVReceiverAppConfig : NSObject

/**
 * The accountId that a player should be setup to use.
 */
@property (nonatomic, copy, nullable) NSString *accountId;

/**
 * The policyKey that a player should be setup to use.
 */
@property (nonatomic, copy, nullable) NSString *policyKey;

/**
 * The authentication token used for verifying a license on a video.
 */
@property (nonatomic, copy, nullable) NSString *authToken;

/**
 * The watermarking token for use with Forensic Watermarking
 */
@property (nonatomic, copy, nullable) NSString *watermarkingToken;

/**
 * Provided for ssai ad setups
 */
@property (nonatomic, copy, nullable) NSString *adConfigId;

/**
 * Used for analytics.
 */
@property (nonatomic, copy, nullable) NSString *userId;

/**
 * Used for analytics.
 */
@property (nonatomic, copy, nullable) NSString *applicationId;

/**
 * If unspecified, the Brightcove v2.x receiver app will play a cast video using
 * a default Web player. Set the playerUrl string property to cause the Brightcove
 * v2.x receiver app to play using a different Web player.
*/
@property (nonatomic, copy, nullable) NSString *playerUrl;

/**
 * The "splash screen" that should be shown before a video and when videos are switching.
*/
@property (nonatomic, copy, nullable) NSString *splashScreen;

@end

@interface BCOVGoogleCastManager (BrightcoveCastReceiver)

/**
 * @param appConfig The Google Cast receiver app configuration
 * @return An instance of BCOVGoogleCastManager configured
 * to make use of the Brightcove Google Cast Receiver App.
 */
- (instancetype)initForBrightcoveReceiverApp:(BCOVReceiverAppConfig *)appConfig;

@property (nonatomic, strong, readonly) BCOVReceiverAppConfig *appConfig;



@end

NS_ASSUME_NONNULL_END
