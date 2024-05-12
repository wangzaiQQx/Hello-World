import requests
import json
from urllib.parse import quote

r = requests.get(f'https://www.bqguu.cc/user/search.html?q={quote("蛊真人")}')

try:
    for x in json.loads(r.text):
        print(x['url_list'] +"\t|  "+ x['articlename'])
except:
    print("暂无，请重新输入关键词")