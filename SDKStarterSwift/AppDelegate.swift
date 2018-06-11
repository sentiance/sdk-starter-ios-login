//
//  AppDelegate.swift
//  SDKStarterSwift
//
//  Created by Gustavo Nascimento on 11/06/2018.
//  Copyright © 2018 Sentiance Corporation. All rights reserved.
//

import UIKit

let APPID = ""
let SECRET = ""

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

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
        let config = SENTConfig.init(appId: APPID, secret: SECRET, launchOptions: launchOptions)
        let sdk: SENTSDK = SENTSDK.sharedInstance()
        sdk.initWith(config, success: {
            self.didAuthenticationSuccess()
            self.startSentianceSDK()
        }) { issue in
            print("Issue: \(issue)");
        }
    }

    func didAuthenticationSuccess() {
        let sdk: SENTSDK = SENTSDK.sharedInstance()

        print("==== Sentiance SDK started, version: \(sdk.getVersion())");
        print("==== Sentiance platform user id for this install: \(sdk.getUserId())");

        sdk.getUserAccessToken({ (token) in
            if let uToken = token {
                print("==== Authorization token that can be used to query the HTTP API: Bearer \(uToken)")
            }
        }) {
            print("==== Something prevented to get the token ====")
        }

        let notificationName = Notification.Name("SdkAuthenticationSuccess")
        NotificationCenter.default.post(name: notificationName, object: nil)
    }

    func startSentianceSDK() {
        let sdk: SENTSDK = SENTSDK.sharedInstance()
        sdk.start({ status in
            if let uStatus = status {
                if (uStatus.startStatus == .started) {
                    print("SDK started properly")
                } else if (uStatus.startStatus == .pending) {
                    print("Something prevented the SDK to start properly (see location permission settings). Once fixed, the SDK will start automatically");
                } else {
                    print("SDK did not start");
                }
            }
        })
    }
}

