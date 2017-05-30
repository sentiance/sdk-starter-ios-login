//
//  AppDelegate.swift
//  SDKStarterSwift
//
//  Created by Muhammad Iqbal on 30/05/2016.
//  Copyright © 2016 Sentiance Corporation. All rights reserved.
//

import UIKit

let APP_ID = ""
let APP_SECRET = ""

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, SENTTransportDetectionSDKDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.

        let defaults = UserDefaults.standard
        let userIsLoggedIn = defaults.bool(forKey: "userIsLoggedIn")

        if (userIsLoggedIn) {
            // show main view controller
            let storyboard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
            let vc = storyboard.instantiateViewController(withIdentifier: "mainViewController") as! ViewController
            self.window?.rootViewController = vc

            // User has logged in, we can start the sdk from the app delegate
            self.launchSentianceSdk(launchOptions: launchOptions)
        }

        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }

    func launchSentianceSdk(launchOptions: [UIApplicationLaunchOptionsKey: Any]?) {
        let config = SENTConfig.init(appId: APP_ID, secret: APP_SECRET, launchOptions: launchOptions)
        let sdk: SENTSDK = SENTSDK.sharedInstance() as! SENTSDK
        sdk.initWith(config, success: {
            self.didAuthenticationSuccess()
            self.startSentianceSDK()
        }) { issue in
            print("Issue: \(issue)");
        }
    }

    func didAuthenticationSuccess() {
        let sdk: SENTSDK = SENTSDK.sharedInstance() as! SENTSDK

        NSLog("==== Sentiance SDK started, version: \(sdk.getVersion())");
        NSLog("==== Sentiance platform user id for this install: \(sdk.getUserId())");

        sdk.getUserAccessToken({ (token) in
            if let uToken = token {
                NSLog("==== Authorization token that can be used to query the HTTP API: Bearer \(uToken.tokenId)")
            }
        }) {
            NSLog("Could not retrieve token")
        }

        let notificationName = Notification.Name("SdkAuthenticationSuccess")
        NotificationCenter.default.post(name: notificationName, object: nil)
    }

    func startSentianceSDK() {
        let sdk: SENTSDK = SENTSDK.sharedInstance() as! SENTSDK
        sdk.start({ status in
            if let uStatus = status {
                if (uStatus.startStatus == .started) {
                    NSLog("SDK started properly")
                } else if (uStatus.startStatus == .pending) {
                    NSLog("Something prevented the SDK to start properly. Once fixed, the SDK will start automatically");
                } else {
                    NSLog("SDK did not start");
                }
            }
        })
    }
}

