import requests
from bs4 import BeautifulSoup
import concurrent.futures
from tqdm import tqdm
import re

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0"
}

url = "https://www.biqg.cc/book/91562/"

session = requests.Session()

def get_soup(url):
    response = session.get(url, headers=headers)
    return BeautifulSoup(response.content, "lxml")

def get_page(link):
    chapter_url = "https://www.biqg.cc" + link["href"]
    soup = get_soup(chapter_url)
    chapter_content = soup.find(id="chaptercontent").get_text(separator="\n")
    cleaned_content = re.sub(r"\n\n\s+|　　|span|/【et】|请收藏本站：https://www.bigee.cc。笔趣阁手机版：https://m.bigee.cc |『点此报错』|『加入书签』|本章由于字数太少，暂不显示。如果你觉得本章比较重要，可以选择左下方报错章节，系统将在十秒内自动处理。或者跳过本章点击下一章继续阅读……", "", chapter_content)
    cleaned_content = link.get_text() +"\n"+ cleaned_content
    return cleaned_content

def main():
    soup = get_soup(url)
    novel_name = soup.find(class_="title").get_text()
    links = soup.find(class_="listmain").find_all("a", href=lambda href: href != "javascript:dd_show()")

    with concurrent.futures.ThreadPoolExecutor() as executor:
        cleaned_contents = list(tqdm(executor.map(get_page, links), total=len(links)))

    with open(f"{novel_name}.txt", "w", encoding="utf-8") as file:
        file.write("\n".join(cleaned_contents))

    print(f"小说《{novel_name}》爬取完成并清理文本完毕。")

if __name__ == "__main__": 
    main()

        