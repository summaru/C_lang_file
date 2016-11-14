#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(x))

void selection_sort(int list[],int size){
    int i,j,least,temp;
    for(i=0;i<size-1;i++){
        least=i;
        for(j=i+1;j<size;j++)
            if(list[j]<list[least]) least=j;

        SWAP(list[i],list[least],temp);
    }
}