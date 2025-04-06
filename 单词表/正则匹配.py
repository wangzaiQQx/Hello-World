import re

def find_words(file_path, pattern):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
        
    words = re.findall(pattern, content)
    
    # 对找到的单词进行排序
    sorted_words = sorted(words)
    
    for word in sorted_words:
        print(word.strip())

file_path = './单词表/考研词汇.txt'
pattern = r'.*ea.*'  # 修改了正则表达式以匹配完整的单词
find_words(file_path, pattern)