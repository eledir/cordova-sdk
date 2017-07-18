#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>
#import <BeaconService/BIBeaconService.h>

@interface BeaconinsideSdkPlugin : CDVPlugin

- (void)init:(CDVInvokedUrlCommand *)command;

@end

@implementation BeaconinsideSdkPlugin

- (void)init:(CDVInvokedUrlCommand *)command {
    NSString *appToken = command.arguments[0];

    [BIBeaconService initWithToken:appToken];
}

@end
