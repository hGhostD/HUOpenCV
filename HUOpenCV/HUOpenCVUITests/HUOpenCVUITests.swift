//
//  HUOpenCVUITests.swift
//  HUOpenCVUITests
//
//  Created by jw.hu on 2018/7/26.
//  Copyright © 2018年 jw.hu. All rights reserved.
//

import XCTest

class HUOpenCVUITests: XCTestCase {
        
    override func setUp() {
        super.setUp()
        
        // Put setup code here. This method is called before the invocation of each test method in the class.
        
        // In UI tests it is usually best to stop immediately when a failure occurs.
        continueAfterFailure = false
        // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
        XCUIApplication().launch()

        // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        
        let app = XCUIApplication()
        let button = app.buttons["获取版本信息"]
        button.tap()
        
        let button2 = app.alerts["版本信息"].buttons["确定"]
        button2.tap()
        button.tap()
        button2.tap()
        button.tap()
        button2.tap()
        button.tap()
        button2.tap()
        
        let alert = app.alerts["版本信息"]
        

        XCTAssert(alert.exists)
    }
    
}
