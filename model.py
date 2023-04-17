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

# # from selenium import webdriver
# from selenium.webdriver.firefox.options import Options


# from selenium.webdriver.common.keys import Keys
# from selenium.webdriver.common.by import By

# import requests
# from bs4 import BeautifulSoup

# options = Options()
# options.binary_location = r'' # byte (raw) string
# driver = webdriver.Firefox(executable_path="geckodriver")

from selenium import webdriver
browser = webdriver.Chrome()
browser.get('https://www.python.org/')


# driver.get("https://www.python.org/")
# assert "GoKifu" in driver.title
# # driver.find_element(By.CSS_SELECTOR)

# response = requests.get(data_base)
# print(response.status_code)
# print(driver.title)


def assemble_game_information():
    black_player_xpath = "/html/body/div[1]/div[3]/div[2]/div[1]"
    white_player_xpath = ""
    game_result = driver.find_element(By.CLASS_NAME, 'game_result')
    game_date = driver.find_element(By.CLASS_NAME, 'game_date')
    print(game_date)
    
    
    
# assemble_game_information()
    

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
        
# scrape_page()
    

