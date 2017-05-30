//
//  SENTToken.h
//  ALSDK
//
//  Created by gustavo nascimento on 12/20/16.
//  Copyright © 2016 Argus Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SENTToken : NSObject

@property (nonatomic, strong) NSString * tokenId;
@property (nonatomic, strong) NSDate * expiryDate;

@end
