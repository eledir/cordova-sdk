window.initBeaconinsideSDK = function(token) {
    cordova.exec(null, null, "BeaconinsideSDK", "init", [token]);
};
