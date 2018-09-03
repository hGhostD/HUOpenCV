//
//  ViewController.swift
//  HUOpenCVTool
//
//  Created by jw.hu on 2018/8/28.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        _ = dialogOKCancel(question: "确认?", text: "请选择:")

    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }

    func dialogOKCancel(question: String, text: String) -> Bool {
        let myPopup: NSAlert = NSAlert()
        myPopup.messageText = question
        myPopup.informativeText = text
        myPopup.alertStyle = .warning
        myPopup.addButton(withTitle: "好的")
        myPopup.addButton(withTitle: "取消")
        return myPopup.runModal() == NSApplication.ModalResponse.alertFirstButtonReturn
    }
}

