//
//  SENTTrip.h
//  ALSDK
//
//  Created by gustavo nascimento on 12/19/16.
//  Copyright © 2016 Argus Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * SENTTrip interface declaration
 */

@interface SENTTrip : NSObject

@property (nonatomic, strong) NSString* tripId;
@property (nonatomic) long long start;
@property (nonatomic) long long stop;
@property (nonatomic) long long distance;
@property (nonatomic, retain) NSMutableArray* pWaypointsArray;


@end


