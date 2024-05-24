import requests
from bs4 import BeautifulSoup
from concurrent.futures import ThreadPoolExecutor
from tqdm import tqdm

with open("./tcjlb.html", "r", encoding='utf-8') as file:
    soup = BeautifulSoup(file, "lxml")
links = soup.find_all("a")

session = requests.Session()
headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0"}

def get_soup(url):
    response = session.get(url, headers=headers)
    soup = BeautifulSoup(response.text, "lxml")
    return soup

def get_page(link):
    try:
        page_url = f"https://www.chatgptzw.com/{link['href']}"
        page_content = (
            get_soup(page_url)
            .find(class_="content")
            .get_text(separator="\n")
        )
        # try:
        #     page_url = page_url.replace(".html", "_2.html")
        #     page_content2 = (
        #     get_soup(page_url)
        #     .find(class_="content")
        #     .get_text(separator="\n")
        # )
        # except:
        #     page_content2 = ""
        # page_title = link.get_text()
        # page_content = f"{page_title}\n{page_content}\n{page_content2}\n"
        page_content = f"{page_content}\n"
    except Exception as e:
        print(f"Error occurred while processing {link['href']}: {e}")
        return None
    return page_content

def scrape_novel(links):
    novel_name = "天才俱乐部"

    with ThreadPoolExecutor() as executor:
        cleaned_contents = list(
            tqdm(executor.map(get_page, links), total=len(links))
        )

    with open(f"{novel_name}.txt", "w", encoding="utf-8") as file:
        file.writelines(f"{content}\n" for content in cleaned_contents if content)

scrape_novel(links)