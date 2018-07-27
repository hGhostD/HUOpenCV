//
//  ViewController.swift
//  HUOpenCV
//
//  Created by jw.hu on 2018/7/25.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }

    @IBAction func buttonClick() {
        let vc = UIAlertController(title: "Info", message: "\(HUOpenCVManager.openCVVersionString())", preferredStyle: .alert)
        let cancel = UIAlertAction(title: "OK", style: .cancel)
        vc.addAction(cancel)
        self.present(vc, animated: true)
    }
    
}

