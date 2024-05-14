import requests
from bs4 import BeautifulSoup
from concurrent.futures import ThreadPoolExecutor
from tqdm import tqdm

class NovelScraper:
    def __init__(self, url):
        self.url = url
        self.session = requests.Session()
        self.headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0"}

    def get_soup(self, url):
        response = self.session.get(url, headers=self.headers)
        soup = BeautifulSoup(response.text, "lxml")
        return soup

    def get_novel_info(self):
        soup = self.get_soup(self.url)
        novel_name = soup.find(class_="title").text.strip()
        novel_index = soup.find(class_="listmain").find_all(
            "a", href=lambda href: href and href != "javascript:dd_show()"
        )
        return novel_name, novel_index

    def get_page(self, link):
        try:
            base_url = self.url.split("/book")[0]
            page_url = f"{base_url}{link['href']}"
            page_content = (
                self.get_soup(page_url)
                .find(id="chaptercontent")
                .get_text(separator="\n")
            )
            page_title = link.get_text()
            page_content = f"{page_title}\n{page_content}"
        except Exception as e:
            print(f"Error occurred while processing {link['href']}: {e}")
            return None
        return page_content

    def scrape_novel(self):
        novel_name, links = self.get_novel_info()

        with ThreadPoolExecutor() as executor:
            cleaned_contents = list(
                tqdm(executor.map(self.get_page, links), total=len(links))
            )

        with open(f"{novel_name}.txt", "w", encoding="utf-8") as file:
            file.writelines(f"{content}\n" for content in cleaned_contents if content)

if __name__ == "__main__":
    url = input("Enter the URL of the novel: ")
    scraper = NovelScraper(url)
    scraper.scrape_novel()

    