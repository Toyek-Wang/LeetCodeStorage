/* **********版权声明**********
 Copyright @ 2021 王晓腾（自动化学院，SEU） All rights reserved.
 email: wangxiaoteng0628@163.com
  **********请尊重知识********** */

#include "pch.h"
#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

/*计算一个数是2的几次方，4是2的2次方，5是2的3次方，8是2的3次方*/
int get_2_N(int x) {
    float x_f = float(x);
    int i = 0;
    while (x_f >= 2.0) {
        x_f = x_f / 2.0;
        i++;
    }
    if (x_f > 1.0) {
        i++;
    }
    return i;
}

vector<int> twoSum(vector<int>& nums, int target) {

    int nums_length = nums.size();

    //寻找标志
    /*int flag = -1;
    for (int i = 0; i < nums_length; i++) {
        if (nums[i] > target) {
            flag = i;
            break;
        }
    }*/

    //复制该数组，并将flag之前的元素用target去减
    vector<int> nums_copy = nums;
    for (int i = 0; i < nums_length; i++) {
        nums_copy[i] = target - nums[i];
    }

    //开始搜索
    vector<int> index;
    int probe = nums_length - 1;
    for (int i = 0; i < nums_length; i++) {
        int current = nums_copy[i];
        for (int j = probe; j >= 0; j--) {
            if (current == nums[j]) {
                index = { i,j };
                return index;
            }
            else if (current > nums[j]) {
                probe = j + 1;
                break;
            }
        }
    }
    return index;
}

/*归并排序的同时要求维护对应的索引*/
void merge_sort(vector<int>& arr, vector<int>& arr_index) {
    int length = arr.size();
    int N = get_2_N(length);
    int up_bound = pow(2, N);
    for (int i = 2; i <= up_bound; i = i * 2) {//确定每一次排序的元素个数
        for (int j = 0; j < (length + i - 1) / i; j++) {//在特定待排序元素个数的情况下，确定总共有多少个小块需要排序
            //对每一个小块进行排序
            //对位于begin--end之间的元素进行归并
            int begin = 0 + j * i;
            int end = i - 1 + j * i;
            int mid = i / 2;//确定中间值
            if (begin + mid > length - 1) {//最后剩下的尾巴只有前半块，无需排序
                continue;
            }
            int kh = 0, kr = mid;//前半块指针、后半块指针
            int end_ = min(end, length - 1);//放置数组越界

            //拷贝待排序块
            vector<int> temp(arr.begin() + begin, arr.begin() + end_ + 1);
            vector<int> temp_index(arr_index.begin() + begin, arr_index.begin() + end_ + 1);
            int k = begin;//往哪一个位置放元素
            while (kh < mid && kr <= end_) {
                if (temp[kh] <= temp[kr]) {
                    arr[k] = temp[kh];
                    arr_index[k] = temp_index[kh];
                    kh++;
                    k++;
                    if (kh == mid) {//前半块放完，接下来只放后半块
                        break;
                    }
                }
                else {
                    arr[k] = temp[kr];
                    arr_index[k] = temp_index[kr];
                    kr++;
                    k++;
                    if (kr > end_ - begin) {//后半块放完，接下来只放前半块
                        for (int k_left = kh; k_left < mid; k_left++) {
                            arr[k] = temp[k_left];
                            arr_index[k] = temp_index[k_left];
                            k++;
                        }
                        break;
                    }
                }
            }
        }
    }
    //return arr;
}
int main()
{
    //给定任意数组
    vector<int> nums={ 59, 9, 47, 16, 31, 54, 0, 45, 59, 53, 97, 32, 82, 30, 94, 06, 28, 99, 18, 71 };
    //构造每个元素对应的索引数组
    vector<int> nums_index(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        nums_index[i] = i;
    }
    merge_sort(nums,nums_index);
    vector<int> index_sort=twoSum(nums, 70);
    vector<int> res = { nums_index[index_sort[0]],nums_index[index_sort[1]] };
    return 0;
    //cout << get_2_N(300);
}
