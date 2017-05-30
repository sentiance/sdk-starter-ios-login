//
//  SENTConfig.h
//  ALSDK
//
//  Created by gustavo nascimento on 12/12/16.
//  Copyright © 2016 Argus Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
@class SENTSDKStatus;
/*
 * SENTConfig interface declaration
 */
@interface SENTConfig : NSObject

@property (nonatomic, strong) NSString* appId;
@property (nonatomic, strong) NSString* secret;
@property (nonatomic, strong) NSDictionary* launchOptions;
@property (nonatomic, copy) void (^didReceiveSdkStatusUpdate)(SENTSDKStatus* issue);

- (id) initWithAppId: (NSString *)appId secret:(NSString*)secret launchOptions:(NSDictionary*)launchOptions;

@end
