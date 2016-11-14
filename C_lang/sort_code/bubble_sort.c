#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
void bubble_sort(int list[],int size){
    int i,j,temp;
    for(i=size-1;i>0;i--){
        for(j=0;j<i;j++){
            if(list[j]>list[j+1])
                SWAP(list[j], list[j+1],temp);
        }
    }
}
