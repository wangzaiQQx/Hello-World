# 从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删元素的值。空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行。
def delete_min(L):
    if len(L) == 0:
        print('顺序表为空')
        return
    min_index = 0
    for i in range(1, len(L)):
        if L[i] < L[min_index]:
            min_index = i
    L[min_index] = L[-1]
    L.pop()
    return L[min_index]