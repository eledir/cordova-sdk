## Summary

Beaconinside Cordova SDK for Android &amp; iOS platform.

See also the documentation for the [native SDKs](https://github.com/beaconinside/sdks).

## Table of contents

* [Example apps](#examples)
* [Get the SDK](#get-sdk)
* [Integrate the SDK](#integrate-sdk)
* [Ask for location permission](#permissions)
* [Set up an account](#account)
* [FAQs & Guides](#faq)
* [Advanced features](#advanced-features)
   * [Callbacks with meta data](#callbacks)
   * [Access the API](#api)

## <a id="examples"></a>Examples

You can easily set up a sample project.

```bash
cordova create BeaconinsideApp
cd BeaconinsideApp
cordova platform add android
cordova platform add ios
cordova plugin add https://github.com/beaconinside/cordova-sdk
cordova plugin add cordova-plugin-geolocation
cordova run android
cordova run ios
```

Initialize the Beaconinside SDK in the *index.js*. See [account setup](#account) to get your own application token.

```js
onDeviceReady: function() {
  this.receivedEvent('deviceready');

  // Change YOUR_APP_TOKEN with your own token
  window.initBeaconinsideSDK("YOUR_APP_TOKEN");
}
```

## <a id="get-sdk"></a>Get the SDK

You can get the latest version from the [releases](https://github.com/beaconinside/cordova-sdk/releases) page or use the *master branch*.


## <a id="integrate-sdk"></a>Integrate the SDK

Add the Beaconinside SDK as a Cordova plugin.

```bash
cordova plugin add https://github.com/beaconinside/cordova-sdk
```

Initialize the Beaconinside SDK with the `initBeaconinsideSDK()` method. See [account setup](#account) to get your own application token.

```js
onDeviceReady: function() {
  this.receivedEvent('deviceready');

  // Change YOUR_APP_TOKEN with your own token
  window.initBeaconinsideSDK("YOUR_APP_TOKEN");
}
```

Continue with the next section to ask for the user's permission to use the device's location.


## <a id="permissions"></a>Ask for location permission

For the Beaconinside SDK to work, the app needs to be authorized to use the device's location in the background.

The easiest way is to use the [geolocation plugin](https://github.com/apache/cordova-plugin-geolocation).

```bash
cordova plugin add cordova-plugin-geolocation
```

Make sure that for iOS10+ you have set the *NSLocationAlwaysUsageDescription* value in the

You have to change the description for the `NSLocationAlwaysUsageDescription` and since iOS 10 the `NSBluetoothPeripheralUsageDescription` key in the `/{project}/platforms/ios/{project}/Info.plist` with a short and friendly text why you are using it.

```xml
<key>NSLocationAlwaysUsageDescription</key>
<string>Specifies the reason for accessing the user's location information.</string>
<key>NSBluetoothPeripheralUsageDescription</key>
<string>This app requires Bluetooth to detect nearby beacons</string>
```

You can check the logfiles if there are location errors.

```bash
adb logcat

# java.lang.SecurityException: Need ACCESS_COARSE_LOCATION or ACCESS_FINE_LOCATION permission to get scan results
```

On Android and iOS you check in the settings app what permissions are provided for each app.


## <a id="account"></a>Account setup

* Sign up for a [Beaconinside Account][dmp] to access the web and mobile dashboards to manage all beacons, geofences and proximity services.

* Add nearby beacons and/or geofences in *MANAGE* for initial testing. For beacons you should select the right vendor and UUID, Major and Minor values.

* Create a campaign with _All Beacons_ group selected and a notification text. Make sure the scheduling criteria are valid for today and the status is *Published*.

* Get your `Application Token` under `Account -> Applications`. It should be kept secret as it uniquely identifies your mobile application.


## <a id="faq"></a>FAQs & Guides

### Requirements

**iOS**

* [Sign up][dmp] for an application token
* iOS 8.0+

**Android**

* [Sign up][dmp] for an application token
* Android 2.3 (API Level 9) or above
* Beacon detection only works with Android 4.3 (API Level 18)
* Google Play services

### Usage Guides

* [Campaign Demo Guide](http://developers.beaconinside.com/docs/demoing-beacons-and-geofences)
* [Setting up a virtual beacon](http://developers.beaconinside.com/docs/virtual-ibeacon)
* [Getting started with geofencing](http://developers.beaconinside.com/docs/geofencing-getting-started)
* [Advantages SDK over API](http://developers.beaconinside.com/docs/sdk-vs-api-integration)
* [SDK battery drain analysis](http://developers.beaconinside.com/docs/sdk-battery-drain)
* [Apple iBeacon guide](https://developer.apple.com/ibeacon/)


## <a id="examples"></a>Advanced features

### <a id="callbacks"></a>Callbacks with meta data

The SDK broadcasts by default entry, exit and update events for beacon and geofencer zones via the NSNotificationCenter on iOS or local broadcasts on Android. Update events are defined by proximity changes between immediate, near, far and rough distance changes +/- 10m.

Just add an observer with these notification names.

```
BeaconServiceRegionEnter
BeaconServiceRegionUpdate
BeaconServiceRegionExit

GeofenceServiceRegionEnter
GeofenceServiceRegionExit
```

The notifications dictionary include for beacons
`BeaconID, proximity UUID, major, minor, proximity and source`. The latter defaults to "com.beaconinside". For geofences it's `GeofenceID, latitude, longitude, radius and source`.

Custom meta data (e.g. internal venue or zone IDs) can be added in the web panel with key=value pairs for beacons and geofences.

For Cordova the easiest way is to use the *cordova-broadcaster plugin* (forked version because of a required bug fix).

```bash
cordova plugin add https://github.com/beaconinside/cordova-broadcaster
```

In you code you can now receive beacon and geofence events.

```js
onDeviceReady: function() {
    this.receivedEvent('deviceready');

   var listener = function(data) {
     console.log("keys: " + Object.keys(data));
     console.log("values: " + Object.values(data));
   }

  window.broadcaster.addEventListener( "BeaconServiceRegionEnter", listener);

  window.requestAuthorization();
  window.initBeaconinsideSDK("YOUR_APP_TOKEN");
}
```

See also the log output for event notifications.

```bash
adb logcat
adb logcat | grep fireEvent
...
# 05-10 16:08:38.943   319   319 D CordovaWebViewImpl: >>> loadUrl(javascript:window.broadcaster.fireEvent( 'BeaconServiceRegionEnter', {"proximity":"near","rssi":-68,"uuid":"F0018B9B-7509-4C31-A905-1A27D39C003C","major":42209,"minor":12731} );)
```

### <a id="api"></a>Access the API

All data can be accessed via server-side APIs. Take a look at the [Beaconinside Developer Hub][dev-hub] for the public Manager and Analytics API reference.


## <a id="support"></a>Support

Just [drop us](mailto:support@beaconinside.com) a message if there are any issues or questions.

## License

Copyright (c) 2015-2017 Beaconinside GmbH. All rights reserved.

[dev-hub]: http://developers.beaconinside.com
[beaconinside]: https://www.beaconinside.com
[dmp]: https://dmp.beaconinside.com
