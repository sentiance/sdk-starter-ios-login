//
//  LoginViewController.swift
//  SDKStarterSwift
//
//  Created by Gustavo Nascimento on 5/29/17.
//  Copyright © 2017 Sentiance Corporation. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func didLogin(_ sender: Any) {
        self.showMainViewController()
    }

    func showMainViewController() {
        let storyboard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
        let vc = storyboard.instantiateViewController(withIdentifier: "mainViewController") as! ViewController
        self.present(vc, animated: true) { 
            //The completion handler is called after the viewDidAppear(_:) method is called on the presented view controller.
            let defaults = UserDefaults.standard
            defaults.set(true, forKey: "userIsLoggedIn")
            defaults.synchronize()
        }
    }

}
