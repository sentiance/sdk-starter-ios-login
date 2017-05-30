//
//  SENTSDK.h
//  ALSDK
//
//  Created by gustavo nascimento on 12/12/16.
//  Copyright © 2016 Argus Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * SDK Forward declarions
 */
@class SENTConfig;
@class SENTSDKStatus;
@class SENTTrip;
@class SENTToken;
#import "SENTInitIssue.h"


/*
 * type definition for TripTransportMode ENUM
 */
typedef NS_ENUM(NSUInteger, SENTTransportMode) {
    SENTTransportModeUnknown = 1,
    SENTTransportModeCar = 2,
    SENTTransportModeBicycle = 3,
    SENTTransportModeOnFoot = 4,
    SENTTransportModeTrain = 5,
    SENTTransportModeTram = 6,
    SENTTransportModeBus = 7,
    SENTTransportModePlane = 8,
    SENTTransportModeBoat = 9,
    SENTTransportModeMetro = 10,
    SENTTransportModeRunning = 11
};


/*
 * type definition for SENTExternalEventType ENUM
 */
typedef NS_ENUM(NSUInteger, SENTExternalEventType) {
    SENTExternalEventTypeOther = 1,
    SENTExternalEventTypeBeacon = 2,
    SENTExternalEventTypeCustomRegion = 3
};


@interface SENTSDK : NSObject
/**
 Method to call the shared instance of the SDK.
 */
+ (id) sharedInstance;
/**
 SDK intialization method. It sets up the modules internally and handles user authentication.
 
 @param config The configuration used to authenticate the user.
 @param success The success block called when init succeeded.
 @param failure The failure block called when init failed. It takes a SENTInitIssue issue indicating the reason of the failure.
 @warning Init should only be called once, unless initialisation fails.
 */
- (void) initWithConfig: (SENTConfig *) config success:(void (^)())success failure:(void (^)(SENTInitIssue issue))failure;
/**
 Start the SDK.
 
 @param completion The completion block called when the SDK has started. SENTSDKStatus object indicates any issue that occured when the SDK started.
 @warning start should be called only after the SDK has been successfully initialised.
 */
- (void) start: (void (^)(SENTSDKStatus* status))completion;
/**
 Stop the SDK.
 */
- (void) stop;
/**
 Stop the SDK after a period of time.
 @param secondsToWait the time (in seconds) to wait.
 */
- (void) stopAfter: (int)secondsToWait;
/**
 Returns the user ID.
 */
- (NSString *) getUserId;
/**
 Retrieve the user's access token.
 @param success Success block called when the user's access token could be retrieved.
 @param failure Failure block called when the user's access token could not be retrieved.
 */
- (void) getUserAccessToken:(void (^)(SENTToken *token))success failure:(void (^)())failure;
/**
 Interface method to set metadata for user.
 Metadata is any additional data that enclosing app is willing to set for this user/app combination
 This metadata could contain vital information related to procesing wrt to the enclosing app.
 
 @param label Field name for the new entry.
 @param value Value for the new entry.
 @param success Success block
 @param failure Failure block
 
 */
- (void) addUserMetadataField: (NSString*) label value:(NSString*) value success:(void (^)())success failure:(void (^)())failure;
/**
 Interface method to set metadata for user.
 Metadata is any additional data that enclosing app is willing to set for this user/app combination
 This metadata could contain vital information related to procesing wrt to the enclosing app.
 
 @param data, key value pair data from enclosing app, could have any structure as long as it can be contained in a dictionary.
 @param success Success block
 @param failure Failure block
 
 */
- (void) addUserMetadataFields: (NSDictionary *) metadata success:(void (^)())success failure:(void (^)())failure;
/**
 Method to remove user data field to the sdk metadata (locally as well as on backend).
 
 @param label Field name for the new entry.
 @param success Success block
 @param failure Failure block
 
 */
- (void) removeUserMetadataField:(NSString*)label
                        success:(void (^)())success failure:(void (^)())failure;
/**
 Start a trip.
 
 @param metadata Any meta data which user wants to provide.
 @param mode Transport mode for this trip as indicated by the user.
 @warning Should only be used with the Triggered Trips flavor of the SDK.
 
 */
- (void) startTrip:(NSDictionary*)metadata
transportModeHint:(SENTTransportMode)mode;
/**
 Stop a trip.
 @return Returns a SENTTrip object containing information about the trip.
 @warning Should only be used with the Triggered Trips flavor of the SDK.
 */
- (SENTTrip *) stopTrip;
/**
 Set a trip timeout block
 */
- (void) setTripTimeOutListener: (void (^)(SENTTrip* trip))tripDidTimeOut;
/**
 Interface method to check if trip is in progress or not.
 */
- (BOOL) isTripOngoing;
/**
 Method to register external event. External event payload is sent to backend immediately if internet availability is there.
 Kept otherwise locally and will be submitted to the backend asap
 
 @param eventType Type of external event to register.
 @param lTimestamp Timed stamp to of the event.
 @param csId ID of the external event, if any
 @param csLabel Label of the external event, if any
 @return True if call was successfull, false otherwise.
 */
- (BOOL) registerExternalEvent:(SENTExternalEventType)eventType
                     timestamp:(long long)lTimestamp
                            id:(NSString*)csId
                         label:(NSString*)csLabel;
/**
 Method to deregister external event.
 
 @param eventType Type of external event to register.
 @param lTimestamp Timestamp to of the event.
 @param csId ID of the external event, if any
 @param csLabel Label of the external event, if any
 @return True if call was successfull, false otherwise.
 
 */
- (BOOL) deregisterExternalEvent:(SENTExternalEventType)eventType
                       timestamp:(long long)lTimestamp
                              id:(NSString*)csId
                           label:(NSString*)csLabel;
/**
 Submits all the pending detections  to backend, without considering any quota related updates and returns the status of these submission via a callback to the enclosing app.
 
 @param callback Callback from enclosing app which is to be called when either forced submission completes or fails.
 
 */
- (void) submitDetections:(void (^)(BOOL bStatus, NSError* error))callback;

/**
 Return true if sdk has ever initialized successfully or not
 */
- (BOOL) isInitialised;
/**
 Get SDK status information
 */
- (SENTSDKStatus*) getSdkStatus;
/**
 Get SDK version
 */
- (NSString *) getVersion;
/**
 Get SDK WiFi quota limit
 */
- (long) getWifiQuotaLimit;
/**
 Get SDK WiFi quota usage
 */
- (long) getWiFiQuotaUsage;
/**
 Get SDK mobile data quota limit
 */
- (long) getMobileQuotaLimit;
/**
 Get SDK mobile data quota usage
 */
- (long) getMobileQuotaUsage;
/**
 Get SDK disk quota limit
 */
- (long) getDiskQuotaLimit;
/**
 Get SDK disk quota usage
 */
- (long) getDiskQuotaUsage;
/**
 Get timestamp of when WiFi was last connected
 */
- (long long) getWiFiLastSeenTimestamp;

@end
