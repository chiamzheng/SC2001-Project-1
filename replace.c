

void hybridMerge(int array[], int left_index, int mid_index, int right_index){

    int arr_size = (right_index - left_index) + 1;
    if (arr_size <= S){
        insertionSort(array, left_index, right_index);
    }
    else{
        unsigned int l_size = (mid_index - left_index) + 1;
        unsigned int r_size = (right_index - mid_index);
        unsigned int l_arr[l_size], r_arr[r_size];
        
        for (int i = 0; i < l_size; i++){
            l_arr[i] = array[i + left_index];
        }
        for (int j = 0; j < r_size; j++){
            r_arr[j] = array[j + mid_index + 1];
        }
        
        int l_index = 0, r_index = 0;
        int original_index = left_index;
        
        while (l_index < l_size && r_index < r_size){
            
            if (l_arr[l_index] <= r_arr[r_index]){
                array[original_index] = l_arr[l_index];
                l_index++;
                keyCmp++;
            }
            else{
                array[original_index] = r_arr[r_index];
                r_index++;
                keyCmp++;
            }
            original_index++;
        }
        
        if (l_index < l_size){
            while (l_index < l_size){
                array[original_index] = l_arr[l_index];
                l_index++;
                original_index++;
            }
        }
        
        else{
            while (r_index < r_size){
                array[original_index] = r_arr[r_index];
                r_index++;
                original_index++;
            }
        }
    }


}

void hybridSort(int array[], int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2; //Saw online to avoid overflow when the size of our data increases
        hybridSort(array, left, mid);
        hybridSort(array, mid+1, right);

        hybridMerge(array, left, mid, right);

    }
}

//replace with the insertionSort
void insertionSort(int arr[], int start, int end){
    for (int i = start + 1; i <= end; i++) {
                for (int j = i; j > 0; j--) {
                    keyCmp++;
                    if (arr[j] < arr[j - 1])
                        swap(arr, j, j - 1);
                    else
                        break;
                }
            }
}
