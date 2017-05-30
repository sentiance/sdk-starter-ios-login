//
//  SENTSDKStatus.h
//  ALSDK
//
//  Created by gustavo nascimento on 12/15/16.
//  Copyright © 2016 Argus Labs. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSUInteger, SENTQuotaStatus) {
    SENTQuotaStatusOK = 1,
    SENTQuotaStatusWarning = 2,
    SENTQuotaStatusExceeded = 3
};

typedef NS_ENUM(NSUInteger, SENTStartStatus) {
    SENTStartStatusNotStarted = 1,
    SENTStartStatusPending = 2,
    SENTStartStatusStarted = 3
};


/*
 * SENTSDKStatus interface declaration
 */
@interface SENTSDKStatus : NSObject


@property(nonatomic) SENTStartStatus startStatus;        // indicates the start status of the Sdk
@property(nonatomic) BOOL canDetect;        // true only if detections are possible (i.e. there are no issues blocking detection)
@property(nonatomic) BOOL isRemoteEnabled;        // true if kill-switch is not enabled
@property(nonatomic) BOOL isLocationPermGranted;        // true if location permissions are granted. If false, canDetect will be false.
@property(nonatomic) BOOL isBgAccessPermGranted;        // true if SDK is allowed to run in the background (iOS)
@property(nonatomic) BOOL isAccelPresent;        // true if device has an accelerometer
@property(nonatomic) BOOL isGyroPresent;        // true if device has a gyroscope
@property(nonatomic) BOOL isGpsPresent;          // true if device has a GPS unit
@property(nonatomic) SENTQuotaStatus wifiQuotaStatus; // indicates WiFi quota state
@property(nonatomic) SENTQuotaStatus mobileQuotaStatus; // indicates mobile data quota state
@property(nonatomic) SENTQuotaStatus diskQuotaStatus; // indicates disk quota state

- (BOOL) isEqualToSDKStatus:(SENTSDKStatus*) sdkStatus;

@end
