import requests
from bs4 import BeautifulSoup

def get_novel_content(url):
    # 发送HTTP请求
    response = requests.get(url)
    # 解码响应内容为字符串
    response.encoding = 'gbk'  # 根据HTML文档中的字符集设置
    # 创建BeautifulSoup对象
    soup = BeautifulSoup(response.text, 'html.parser')
    
    # 查找包含小说内容的元素
    content_div = soup.find('div', id='content')
    
    # 提取文本内容
    novel_text = content_div.get_text().strip()
    
    return novel_text

# 指定URL

with open("./dlzc.html", "r", encoding='utf-8') as file:
    soup = BeautifulSoup(file, "lxml")
links = soup.find_all("a")

for url in links:
    novel_text = get_novel_content(f"https://www.biqooge.com/{url['href']}")
    with open(f"斗罗杂草.txt", "a", encoding="utf-8") as file:
        file.writelines(novel_text)
