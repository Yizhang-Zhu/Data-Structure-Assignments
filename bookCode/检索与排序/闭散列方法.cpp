template<typename Key, typename E>
void hashdict<Key, E>::hashInsert(const Key& k, const E& e){
    int home;//基槽
    int pos = home = h(k);//初始化探查序列
    for(int i = 1; EMPTYKEY != (HT[pos]).key(); i++){
        pos = (home + p(k,i)) % M;//探查
    }
    KVpair<keu, E> temp(k, e);
    HT[pos] = temp;
}