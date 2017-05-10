package com.beaconinside.androidsdk;

import com.beaconinside.androidsdk.BeaconService;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;

public class SdkPlugin extends CordovaPlugin {

    /**
     * Executes the request and returns PluginResult.
     *
     * @param action          The action to execute.
     * @param args            JSONArry of arguments for the plugin.
     * @param callbackContext The callback context from which we were invoked.
     */
    public boolean execute(String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        if (action.equals("init")) {
            BeaconService.init(this.cordova.getActivity(), args.optString(0));
            return true;
        }
        return false;
    }

}
