from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import time

options = webdriver.ChromeOptions()
options.add_argument('--ignore-certificate-errors')
options.add_argument('--incognito')

driver = webdriver.Chrome(
    service=Service(ChromeDriverManager().install()),
    options=options
)

try:
    driver.get('https://baike.baidu.com/item/Python')
    time.sleep(2)
    
    print("当前页面标题:", driver.title)
    
    screenshot_path = 'baike_python.png'
    driver.save_screenshot(screenshot_path)
    print(f"已保存截图至: {screenshot_path}")
    
    try:
        summary = driver.find_element(By.CSS_SELECTOR, 'div.lemma-summary').text
        print("\nPython简介:")
        print(summary)
    except Exception as e:
        print("无法获取简介内容:", e)
    
except Exception as e:
    print("发生错误:", e)

finally:
    driver.quit()