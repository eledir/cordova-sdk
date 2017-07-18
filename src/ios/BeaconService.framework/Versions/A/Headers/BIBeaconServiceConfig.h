//
//  BIBeaconServiceConfig.h
//  BeaconService
//
//  Created by Cornelius Rabsch on 14.05.16.
//  Copyright © 2016 Beaconinside GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 Location manager update behavior.
 
 By default significant location updates are used.
 */
typedef enum {
    // Use significant location updates to fetch new content
    kBILocationManagerUpdateIntervalOptimized = 0,
    
    // Highest responsiveness to location changes, high resource consumption (only recommended for testing)
    kBILocationManagerUpdateIntervalHighest,
    
    // Do not enforce continuous location updates
    kBILocationManagerUpdateIntervalOff
    
} BILocationManagerUpdateInterval;




@interface BIBeaconServiceConfig : NSObject

/**
 Designated initializer for configuration builder
 */
+ (BIBeaconServiceConfig*)defaultConfig;

/**
 Set a custom ID for your own reporting and analytics tasks.
 This can be a hashed email address or your own hashed user ids.
 Do not send personal identifiable information.
 
 @param identifier Your own user identifier
 */
- (void)setCustomID1:(NSString*)identifier;

/**
 Set another custom ID for your own reporting and analytics tasks.
 This can be a hashed email address or your own hashed user ids.
 Do not send personal identifiable information.
 
 @param identifier Your own user identifier
 */
- (void)setCustomID2:(NSString*)identifier;


/**
 Set context data to use custom targeting criteria that can be used to personalize the user experience.
 The block will be called by the SDK in background states, with or without internet and upon entering a beacon or geofence.

 @param block Block which is called to get dictionary with context params as key value pairs
 */
- (void)setContextDataHandler:(NSDictionary*(^)(void))block;


/**
 Set beacon detection accuracy level. 
 Use with caution as it can a high impact on battery drain.
 
 @param interval Recommended location manager settings
 */
- (void)setLocationManagerUpdateInterval:(BILocationManagerUpdateInterval)interval;


/**
 Configure beacon ranging interval, i.e. only capture
 beacon events every x seconds.
 
 @param interval Interval of beacon ranging events in seconds
 */
- (void)setBeaconRangingUpdateInterval:(NSUInteger)interval;


/**
 Set custom notification handler to intercept beacon in-app handling
 Tracking is not impacted by overwriting opening behavior.
 
 If block returns false than default actions will be triggered

 @param block Block that handles local notification
 */
- (void)setCustomNotificationHandler:(BOOL (^)(UILocalNotification*))block;

/**
 Read-only property to access custom notification handler
 */
@property (readonly, nonatomic, copy) BOOL (^customNotificationHandler)(UILocalNotification*);


/**
 Read-only property to handle location manager configuration values
 */
@property (readonly, assign, nonatomic) BILocationManagerUpdateInterval locationManagerUpdateInterval;

/**
 Read-only property to handle beacon ranging update interval
 */
@property (readonly, assign, nonatomic) NSUInteger beaconRangingUpdateInterval;


@end
