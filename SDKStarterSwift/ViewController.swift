//
//  ViewController.swift
//  SDKStarterSwift
//
//  Created by Muhammad Iqbal on 30/05/2016.
//  Copyright © 2016 Sentiance Corporation. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var userIDLabel: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        let notificationName = Notification.Name("SdkAuthenticationSuccess")
        NotificationCenter.default.addObserver(self, selector: #selector(ViewController.refreshUserID), name: notificationName, object: nil)

        let defaults = UserDefaults.standard
        let userIsLoggedIn = defaults.bool(forKey: "userIsLoggedIn")
        if (!userIsLoggedIn) {
            // First time this screen is displayed, the sdk can now start
            let appDelegate = UIApplication.shared.delegate as! AppDelegate
            appDelegate.launchSentianceSdk(launchOptions: nil)
        }
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        refreshUserID()
    }

    func refreshUserID() {
        if let sdk = SENTSDK.sharedInstance() as? SENTSDK, sdk.isInitialised() == true {
            if let userID = sdk.getUserId() {
                self.userIDLabel.text = userID
            }
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

