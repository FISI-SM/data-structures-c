/****** OPTIMIZED BUBBLE SORT ALGORITHM FUNCTION ********/

void bubble_sort(int *arr, int n)
{
int i, j, temp, flag = 0;
    for(i=0; i<n; i++)
    {
       for(j=0; j<n–i–1; j++)
       {
          if(arr[j]>arr[j+1])
          {
             flag = 1;
             temp = arr[j+1];
             arr[j+1] = arr[j];
             arr[j] = temp;
          }
       }
      if(flag == 0) // array is sorted
         return;
   }
}
