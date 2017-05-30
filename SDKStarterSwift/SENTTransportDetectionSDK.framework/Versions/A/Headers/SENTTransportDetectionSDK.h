//
//  SENTTransportDetectionSDK.h
//  Sentiance SDK
//
//  Created by Sentiance.
//  Copyright © 2014 Sentiance. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SENTSDK.h"
#import "SENTConfig.h"
#import "SENTSDKStatus.h"
#import "SENTToken.h"
#import "SENTTrip.h"
#import "SENTStatusMessage.h"

/*
 * SDK Forward declarions
 */
@class SDKIssue;
@class SENTTransportDetectionSDK;


/*
 * type definition for MetaDataSubmissionStatus ENUM
 */
typedef NS_ENUM(NSUInteger, MetaDataSubmissionStatus) {
    SUCCESS,
    VALIDATION_ERROR,
    OTHER_ERROR
};

/*
 * type definition for TripTransportMode ENUM
 */
typedef NS_ENUM(NSUInteger, TripTransportMode) {
    TransportMode_UNKNOWN = 1,
    TransportMode_CAR = 2,
    TransportMode_BICYCLE = 3,
    TransportMode_ON_FOOT = 4,
    TransportMode_TRAIN = 5,
    TransportMode_TRAM = 6,
    TransportMode_BUS = 7,
    TransportMode_PLANE = 8,
    TransportMode_BOAT = 9,
    TransportMode_METRO = 10,
    TransportMode_RUNNING = 11
};

/*
 * type definition for TripStatus ENUM
 */
typedef NS_ENUM(NSUInteger, TripStatus) {
    TRIP_STATUS_UNKNOWN = 1,
    TRIP_ALREADY_IN_PROGRESS = 2,
    TRIP_STARTED_SUCCESSFULLY = 3
    
};

/*
 * type definition for EventType ENUM
 */
typedef NS_ENUM(NSUInteger, EventType) {
    EventType_OTHER = 1,
    EventType_BEACON = 2,
    EventType_CUSTOM_REGION = 3
};


/*
 * Sentiance SDK delegate - SENTTransportDetectionSDKDelegate
 */
@protocol SENTTransportDetectionSDKDelegate <NSObject>

@optional

- (void)didAuthenticationSuccess;                                    // Authentication success delegate method
- (void)didAuthenticationFailed : (NSError *)error;                  // Authentication failure delegate method
- (void)onSdkIssue:(SDKIssue*)issue :(SENTStatusMessage*)message;    // SDK status issue delegate method

@end

/*
 * Sentiance SDK trip timeout delegate - SENTTripTimeoutSDKDelegate
 */
@protocol SENTTripTimeoutSDKDelegate

@optional

- (void)onTripTimeout:(NSDictionary*)pTrip;                           // SDK trip timeout delegate method.

@end

/*
 * SDK interface declaration.
 */
@interface SENTTransportDetectionSDK : NSObject

// SENTTransportDetectionSDKDelegate delegate
@property NSObject<SENTTransportDetectionSDKDelegate>* delegate;

// SENTTripTimeoutSDKDelegate delegate
@property NSObject<SENTTripTimeoutSDKDelegate>* timeoutDelegate;

/*
 * SDK initializer with launch options as provided by the enclosing app
 *
 * param: NSDictionary : appLaunchOptions, a NSDictionary as provided by the caller
 * return: id
 *
 */
- (id)initWithLaunchOptions:(NSDictionary *)appLaunchOptions __deprecated_msg("use initWithConfigurationData method instead.");

/*
 * SDK initializer with app ID and secret along with launchOptions from enclosing app
 *
 * param: NSString : appID, a string application ID provided by the caller
 * param: NSString : secret, a string application secret provided by the caller
 * param: NSDictionary : appLaunchOptions, a NSDictionary as provided by the caller
 * return: id
 *
 */
- (id)initWithAppID:(NSString *)appID secret:(NSString *)secret launchOptions:(NSDictionary *)appLaunchOptions __deprecated_msg("use initWithConfigurationData instead.");

/*
 * SDK initializer with user name, password and app launch options as provided by the enclosing app
 *
 * param: NSString : username, a string user name provided by the caller
 * param: NSString : password, a string password provided by the caller
 * param: NSDictionary : appLaunchOptions, a NSDictionary as provided by the caller
 * return: id
 *
 */
- (id)initWithUserName:(NSString *)username password:(NSString *)password launchOptions:(NSDictionary *)appLaunchOptions __deprecated_msg("use initWithConfigurationData instead.");

/*
 * Instance method to get timeline associated with this user
 *
 * param: void (^)(NSArray *data) : success, a success block
 * param: void (^)(NSError *error) : failed, a failure block
 *
 */
- (void) getTimeline:(NSDate *)date
             success:(void (^)(NSArray *data))success
              failed:(void (^)(NSError *error))failed __deprecated_msg("use http api(see docs) instead.");

/*
 * Instance method to get moments for this user
 *
 * param: void (^)(NSDictionary *data) : success, a success block
 * param: void (^)(NSError *error) : failed, a failure block
 *
 */
- (void) getMoments:(void (^)(NSDictionary *data))success
             failed:(void (^)(NSError *error))failed __deprecated_msg("use http api(see docs) instead.");

/*
 * Register a user with app ID and secret
 *
 * param: NSString : appID, a string application ID provided by the caller
 * param: NSString : secret, a string application secret provided by the caller
 * param: void (^)() : success, a block called when user has been registered successfully
 * param: void (^)(NSError *error) : failed : a block called when user registration fails due to some reason
 *
 */
+ (void)registerUserWithAppID:(NSString *)appID
                       secret:(NSString *)secret
                      success:(void (^)())success
                       failed:(void (^)(NSError *error))failed;

/*
 * Register a user with user name and password
 *
 * param: NSString : username, a string user name provided by the caller
 * param: NSString : password, a string password provided by the caller
 * param: void (^)() : success, a block called when user has been registered successfully
 * param: void (^)(NSError *error) : failed : a block called when user registration fails due to some reason
 *
 */
+ (void)registerUserWithUserName:(NSString *)username
                        password:(NSString *)password
                         success:(void (^)())success
                          failed:(void (^)(NSError *error))failed __deprecated_msg("will be removed in upcoming release.");

/*
 * Return if sdk is ever authenticated successfully or not
 *
 * result: BOOL : status as TRUE or FALSE
 *
 */
+ (BOOL)isAuthenticated;

/*
 * Register a user with user name and password
 *
 * param: NSString : username, a string user name provided by the caller
 * param: NSString : password, a string password provided by the caller
 * param: void (^)() : success, a block called when user has been registered successfully
 * param: void (^)(NSError *error) : failed : a block called when user registration fails due to some reason
 *
 */
+ (void)registerForPushNotificationsWithDeviceToken:(NSData *)token
                                            success:(void (^)())success
                                             failed:(void (^)(NSError *error))failed __deprecated_msg("use sentiance firehose(see docs) instead.");

/*
 * Class method to get sdk user ID
 *
 * result: NSString : string sdk user ID
 *
 */
+ (NSString *)getUserId;

/*
 * Class method to get sdk user token
 *
 * result: NSString : string sdk user token
 *
 */
+ (NSString *)getUserToken;

/*
 * Class method to get sdk flavor set for current user
 *
 * result: NSString : string sdk flavor
 *
 */
+ (NSString *)getSDKFlavor;

/*
 * Class method to get sdk version
 *
 * result: NSString : string sdk version
 *
 */
+ (NSString *)getSDKVersion;

/*
 * Class method to log any message and exception from the enclosing app
 * Saves the reported message/exception as a crash report with current timestamp as name of the file.
 *
 * param: NSString : message, a text message as reported by the enclosing app.
 * param: NSException : exception, exception object as reporetd by the enclosing app.
 *
 */
+ (void)logError:(NSString *)message exception:(NSException *)exception;

/*
 * Interface method to set metadata for user
 * metadata is any additional data that enclosing app is willing to set for this user/app combination
 * This metadata could contain vital information related to procesing wrt to the enclosing app.
 *
 * param: NSDictionary : data, key value pair data from enclosing app, could have any structure as long as it can be contained in a dictionary.
 * param: void (^)(MetaDataSubmissionStatus submissionStatus) : completed, completion block from enclosing app
 *
 */
- (void)setUserMetadata:(NSDictionary *)data
              completed:(void (^)(MetaDataSubmissionStatus submissionStatus))completed __deprecated_msg("use addUserDataField/removeUserDataField instead.");
/*
 * Interface method to get metadata for user
 *
 * param: void (^)(NSDictionary *metaData) : completed, completion block from enclosing app inside which they can see the metadata in form of a NSDictionary
 *
 */
- (void)getUserMetadata:(void (^)(NSDictionary *metaData))completed;

/*
 * Method to add user data field to the sdk metadata (locally as well as on backend)
 *
 * param: NSString : csFieldName, field name for the new entry.
 * param: NSString : csValue, value for the new entry.
 * param: void (^)(MetaDataSubmissionStatus submissionStatus) : completed, completion block from the enclosing app
 *
 */
- (void)addUserDataField:(NSString*)csFieldName withStringValue:(NSString*)csValue
               completed:(void (^)(MetaDataSubmissionStatus submissionStatus))completed;

/*
 * Method to remove user data field to the sdk metadata (locally as well as on backend)
 *
 * param: NSString : csFieldName, field name for the new entry.
 * param: void (^)(MetaDataSubmissionStatus submissionStatus) : completed, completion block from the enclosing app
 *
 */
- (void)removeUserDataField:(NSString*)csFieldName
                  completed:(void (^)(MetaDataSubmissionStatus submissionStatus))completed;

/*
 * Start Trip interface method
 * Controls the intialization and start of Detection Module which handles all the sub modules
 *
 * param: NSDictionary : metadata,  any meta data which user wants to provide
 * param: TripTransportMode : mode, Transport mode for this trip as indicated by the user (see TripTransportMode enum in header file)
 * param: void (^)(TripStatus tStatus, NSString* csMessage) : callback, callback to let enclosing app know what happend to the startign trip and report it back to the enclosing app.
 *
 */
- (void)startTrip:(NSDictionary*)metadata
transportModeHint:(TripTransportMode)mode
         callback:(void (^)(TripStatus tStatus, NSString* csMessage))callback;

/*
 * Stop Trip Interface Method
 *
 * result: NSDictionary : Trip information is returned whenever we stop the trip.
 *
 */
- (NSDictionary*)stopTrip;

/*
 * Set transport mode and stop Trip Interface Method
 *
 * result: NSDictionary : Trip information is returned when we stop the trip.
 *
 */
- (NSDictionary*)stopTrip:(TripTransportMode)mode;

/*
 * Cancels an ongoing trip, the trip is immediately removed and trip manager is stopped
 *
 */
- (void)cancelTrip;

/*
 * Get distance travelled by current trip
 *
 * return: long long : total distance travelled in current trip
 *
 */
- (long long)getCurrentTripDistance;

/*
 * Get SDK status information
 *
 * return: NSDictionary : Dictionary containing the status parameters of SDK at this time
 *
 */
- (NSDictionary*)getSDKStatusInfo;

/*
 * Interface method to check if trip is in progress or not.
 *
 * return: BOOL : true if trip is in progress, otherwise false
 *
 */
- (BOOL)isTripOngoing;

/*
 * Method to register external event. External event payload is sent to backend immediately if internet availability is there
 * kept otherwise locally and will be submitted to the backend asap
 *
 * param: EventType : eventType, type of external event to register.
 * param: long long : lTimestamp, timed stamp to of the event.
 * param: NSString : csId, ID of the external event, if any
 * param: NSString : csLabel, Label of the external event, if any
 * return: BOOL : true
 *
 */
- (BOOL)registerExternalEvent:(EventType)eventType
                    timestamp:(long long)lTimestamp
                           id:(NSString*)csId
                        label:(NSString*)csLabel;

/*
 * Method to deregister external event.
 *
 * param: EventType : eventType, type of external event to register.
 * param: long long : lTimestamp, timed stamp to of the event.
 * param: NSString : csId, ID of the external event, if any
 * param: NSString : csLabel, Label of the external event, if any
 * return: BOOL : true
 *
 */
- (BOOL)deregisterExternalEvent:(EventType)eventType
                      timestamp:(long long)lTimestamp
                             id:(NSString*)csId
                          label:(NSString*)csLabel;

/*
 * SDK intialization method
 * initWithConfigurationData method is new way to initialize the sdk
 * - introduced to make the sdk initialization process uniform for iOS and android sdks.
 * - init method with additional parameters
 * - autostart addition to sdk, autostart = TRUE or FALSE, will start sdk automatically if true, if not startDetections is expected
 * - sdk initialization callback is also provided in the sdk delegate, will let enclosing app know if the sdk initialization was completed successfully or not
 * - app id and secret could also be provided
 * - username, password could also be provided
 *
 * Following could be the dictionary structure provided as configuration to sdk:
 * configData = {
 *      "autostart" : BOOL,
 *      "appid" : NSString,
 *      "secret" : NSString,
 *      "username" : NSString,
 *      "password" : NSString,
 *      "appLaunchOptions" : NSDictionary
 * }
 * NOTE: The username/password/appid/secret are optional keys in the dictionary
 * username/password is required when you have username/password and want to initialize SDK using them
 * appid/secret is required when you have appid/secret
 *
 * param: NSDictionary : configData, as described above.
 * return: id : sdk instance
 *
 */
- (id)initWithConfigurationData:(NSDictionary *)configData;

/*
 * Method to start detections from sdk
 *
 */
- (void) startDetections;

/*
 * Method to stop detections from sdk
 *
 */
- (void) stopDetections;

/*
 * Method to stop detections from sdk after a certain time
 *
 * param: int : secondsToWait, number of seconds to wait before sdk is stopped actually.
 *
 */
- (void) scheduleStopDetections:(int)secondsToWait;

/*
 * Interface method to get status of sdk
 *
 * return: SENTStatusMessage : status message as requested
 *
 */
- (SENTStatusMessage*) getStatusMessage;

/*
 * Submits all the pending detettions till this time to backend, without considering any quota related updates and
 * returns the status of these submission via a cllback to the enclosing app.
 *
 * param: void (^)(BOOL bStatus, NSError* error) : callback, callback from enclosing app which is to be called when either forced submission completes or fails.
 *
 */
- (void) submitDetectionsWithCallback:(void (^)(BOOL bStatus, NSError* error))callback;

@end
