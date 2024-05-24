bool Del_Min (SqList &L, ElemType &value){
    if (L.length == 0) return false;
    value = L.data[0];
    int pos = 0;
    for (int i = 1; i < L.length; i++)
        if (L.data[i] < L.data[pos])
            pos = i;
    L.data[pos] = L.data[L.length - 1];
    L.length--;
    return true;
}