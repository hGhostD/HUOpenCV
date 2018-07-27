
import unittest
import os
from appium import webdriver
from time  import sleep


class  appiumSimpleTezt (unittest.TestCase):

	def  setUp(self):
		app = os.path.abspath('/Users/jw.hu/Library/Developer/Xcode/DerivedData/HUOpenCV-epgsxosoacdnazhjkgcptgdylwtm/Build/Products/Debug-iphoneos/HUOpenCV.app')

		self.driver = webdriver.Remote(
			command_executor = 'http://127.0.0.1:4723/wd/hub',
			desired_capabilities = {
				'app':app,
				'platformName': 'iOS',
				'platformVersion': '10.3.3',
				'deviceName': 'iPhone 6plus',
				'bundleId': 's2i.HUOpenCV',
				'udid': 'ba648eb22cb94996c31c8cface16132a4f03a598'
			}
			)

	def test_push_view(self):
		
		next_view_button = self.driver.find_element_by_accessibility_id("Get")
		next_view_button.click()

		sleep(2)

		back_view_button = self.driver.find_element_by_accessibility_id("OK")
		back_view_button.click()

	def tearDown(self):
		sleep(1)
		# self.driver.quit()

if __name__ == '__main__':
	suite = unittest.TestLoader().loadTestsFromTestCase(appiumSimpleTezt)
	unittest.TextTestRunner(verbosity=2).run(suite)
