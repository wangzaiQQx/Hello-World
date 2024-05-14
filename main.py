import logging
import requests
from bs4 import BeautifulSoup
from concurrent.futures import ThreadPoolExecutor
from tqdm import tqdm
import re

# 配置日志
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s"
)


class NovelScraper:
    HEADERS = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0"
    }
    DELETE_LIST_DEFAULT = ["『点此报错』|『加入书签』"]

    def __init__(self, url, more_delete=None):
        self.url = url
        self.more_delete = more_delete if more_delete is not None else []
        self.delete_list = self.DELETE_LIST_DEFAULT + self.more_delete
        self.session = requests.Session()
        self.headers = self.HEADERS

    def get_soup(self, url):
        """Fetches and parses HTML content from the given URL using BeautifulSoup."""
        response = self.session.get(url, headers=self.headers)
        response.raise_for_status()  # Ensure the request was successful
        return BeautifulSoup(response.text, "lxml")

    def get_novel_info(self):
        """Extracts novel name and index links from the given URL."""
        soup = self.get_soup(self.url)
        novel_name = soup.find(class_="title").text.strip()
        novel_index = soup.find(class_="listmain").find_all(
            "a", href=lambda href: href and href != "javascript:dd_show()"
        )
        return novel_name, novel_index

    def get_page(self, link):
        """Fetches and cleans the content of a novel page."""
        try:
            base_url = self.url.split("book")[0]
            page_url = f"{base_url}{link['href']}"
            page_content = (
                self.get_soup(page_url)
                .find(id="chaptercontent")
                .get_text(separator="\n")
            )
            page_title = link.get_text()
            page_content = f"{page_title}\n{page_content}"
            for item in self.delete_list:
                page_content = re.sub(rf"{item}", "", page_content)
            page_content = re.sub(r"\n+", "\n", page_content)
        except Exception as e:
            print(f"Error occurred while processing {link['href']}: {e}")
            return None
        return page_content

    def scrape_novel(self):
        """Main function to scrape and save novel content from the given URL."""
        novel_name, links = self.get_novel_info()
        logging.info(f"开始抓取小说《{novel_name}》...")

        with ThreadPoolExecutor() as executor:
            cleaned_contents = list(
                tqdm(executor.map(self.get_page, links), total=len(links))
            )

        with open(f"{novel_name}.txt", "w", encoding="utf-8") as file:
            file.writelines(f"{content}\n" for content in cleaned_contents if content)

        logging.info(f"小说《{novel_name}》抓取并清理文本完成。")
        self.session.close()  # 显式关闭session


if __name__ == "__main__":
    url = input("请输入小说链接：")
    more_delete = [
    ]  # 用户自定义需要额外删除的内容列表
    scraper = NovelScraper(url, more_delete)
    scraper.scrape_novel()
