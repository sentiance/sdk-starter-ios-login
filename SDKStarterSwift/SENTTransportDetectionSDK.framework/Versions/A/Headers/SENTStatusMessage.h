//
//  SENTStatusMessage.h
//  SENTSDK
//
//  Created by Muhammad Iqbal on 14/12/2015.
// 
//  Copyright © 2015 Sentiance. All rights reserved.
//

/*
 * Includes
 */
#import <Foundation/Foundation.h>

/*
 * SDKMode enum
 */
typedef NS_ENUM(NSUInteger, SDKMode) {
    SDKMode_SUPPORTED = 1,
    SDKMode_UNSUPPORTED = 2
};

/*
 * SDKIssueType enum
 */
typedef NS_ENUM(NSUInteger, SDKIssueType) {
    SDK_LocationPermissionIssue = 1,
    SDK_SensorPermissionIssue = 2,
    SDK_NetworkPermissionIssue = 3,
    SDK_BGAccessPermissionIssue = 4,
    SDK_DiskUsePermissionIssue = 5,
    SDK_GpsIssue = 6,
    SDK_GyroscopeIssue = 7,
    SDK_MotionsensorIssue = 8,
    SDK_AccelerometerIssue = 9,
    SDK_PlatformIssue = 10,
    SDK_ManufacturerIssue = 11,
    SDK_ModelIssue = 12,
    SDK_OSIssue = 13,
    SDK_SDKVersionIssue = 14,
    SDK_DiskQuotaExceeded = 15,
    SDK_WifiQuotaExceeded = 16,
    SDK_MobileQuotaExceeded = 17
};

/*
 * SDKIssue interface declaration
 */
@interface SDKIssue : NSObject {

}

@property(nonatomic) SDKIssueType type;                         // SDK issue type
@property(nonatomic, retain) NSString* description;             // SDK issue description

/*
 * Init method with SDK issue type
 */
- (id)initWithIssue:(SDKIssueType)type;

@end


/*
 * SENTStatusMessage interface declaration
 */
@interface SENTStatusMessage : NSObject {
    
}

@property(nonatomic) SDKMode mode;                              // SDK Mode in which sdk is operating
@property(nonatomic, retain) NSMutableArray* issues;            // List of issues experienced by SDK, if any
@property(nonatomic) BOOL isDetecting;                          // BOOL value specifying if the detections are in progress from SDK or not
@property(nonatomic) int detectionCount;                        // Detections count
@property(nonatomic) long long wifiLastSeenTimestamp;           // Last wifi access timestamp in epoch
@property(nonatomic) long long wifiQuotaUsed;                   // Number of bytes sent over WiFi by the sdk
@property(nonatomic) long long wifiQuotaLimit;                  // Total number of bytes allowed to be sent over WiFi
@property(nonatomic) long long mobileQuotaUsed;                 // Number of bytes sent over Mobile newtwork by the sdk
@property(nonatomic) long long mobileQuotaLimit;                // Total number of bytes allowed to be sent over Mobile network
@property(nonatomic) long long diskQuotaUsed;                   // Number of bytes on local storage used by SDK
@property(nonatomic) long long diskQuotaLimit;                  // Total number of bytes aloowed to be used by SDK on local storage
@property(nonatomic) BOOL isRemoteEnabled;                      // Kill switch status

/*
 * Method to check equivalence between two SENTStatusMessage objects
 *
 * param: SENTStatusMessage : pMessage, status message to compare the current instance with
 *
 * return: BOOL : TRUE/FALSE depending upon if the two objects are equivalent or not.
 */
- (BOOL)isEqualToStatusMessage:(SENTStatusMessage*)pMessage;
- (NSString *) description;

@end
