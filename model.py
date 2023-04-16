"""
Search queries used when collecting data:
    - weiqi database
    - fuseki sgf database
    - baduk database
    - go fuseki database
Papers:
    - https://ieeexplore.ieee.org/document/9253125
1. Create scraping script to get data of professional Go games in SGF format from:
    - https://homepages.cwi.nl/~aeb/go/games/games/
    - https://gobase.org/
    - https://za3k.com/ogs/
    - https://pjreddie.com/projects/jgdb/
    - http://gokifu.com/
2. Train model
3. Implement model in C++
"""

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

import requests
from bs4 import BeautifulSoup


driver = webdriver.Firefox()
data_base = "http://gokifu.com/index.php"
driver.get(data_base)
assert "GoKifu" in driver.title
elem = driver.find_element(By.NAME,)



response = requests.get(data_base)


def scrape_page():
    if (response.status_code == 200):
        soup = BeautifulSoup(response.text, 'html.parser')
        # print(response.text)
        print("</html>" in soup.prettify())
        # print ("a" in "haad")
        
        # print('</html>' in soup.get_text())


def scrape():
    pages_to_scrape = 10
    curr = 1
    while (curr <= pages_to_scrape):
        scrape_page()
        
scrape_page()
    

