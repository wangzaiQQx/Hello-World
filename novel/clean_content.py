import re

delete_list = [
    "『点此报错』|『加入书签』",
    ".+ps.+",
    ".+！！！",
    ".+未完待续.+",
]
with open('test.txt', 'r', encoding='utf-8') as f:
    content = f.read()
    for pattern in delete_list:
        content = re.sub(pattern, "", content)
    content = re.sub("\n\n+", "\n\n", content)
with open('text.txt', 'w', encoding='utf-8') as f:
    f.write(content)
