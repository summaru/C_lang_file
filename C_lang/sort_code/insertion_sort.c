void insertion_sort(int list[],int size){
    int i,j,key;
    for(i=1;i<size;i++){
        key=list[i];
        for(j=i-1;j>=0&&list[j]>key;j--)
            list[j+1] = list[j];
    }
}