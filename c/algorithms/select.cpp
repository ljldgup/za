/************************************************************************
    > File Name: select.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月 2日 14:41:37
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
#include<algorithm>
using namespace std;
#define random(x) (rand()%(x))


int MAX_SIZE = 24;
int INTERVAL = 5;
int depth = 0;

void exchange(vector<int> &nums, int p, int r){
	int t = nums[r];
	nums[r] = nums[p];
	nums[p] = t;
}

int partition(vector<int> &nums, int p, int r){
	// cout<<p<<' '<< r<<"- \n";
	// for(int i = p; i <= r; i++) cout<<nums[i]<<' ';
	// cout<<endl;
	int i = p - 1;
	int j = p;
	int x = nums[r];

	for(; j < r; j++){
		if(nums[j] < x){
			i++;
			exchange(nums, i, j);
		}
	}
	i++;
	exchange(nums, i , r);
	return i;
}

int random_partition(vector<int> &nums, int p, int r){
	int t = random(r - p + 1) + p;
	exchange(nums, t, r);
	return partition(nums, p, r);
}

int random_select(vector<int> &nums, int p, int r, int k){
	// cout<<p<<' '<< r<<' '<<k<<"-- \n";
	if(r == p) return nums[r];
	
	int q = random_partition(nums, p, r);
	// cout << q<< "---\n";
	if(q == k) return nums[q];

	if(q < k) return random_select(nums, q + 1, r, k);
	else return random_select(nums, p, q - 1, k);      
}

int partion_with_value(vector<int> &nums, int p, int r, int value){

	// cout<<"enter partion_with_value"<<p<<' '<< r<<' '<<value<<endl;
	// for(int i = p; i <= r; i++ ) cout<<nums[i]<<" ";
	// cout<<endl;
	
	int left, right, v_postion;
	
	left = p;
	right = r;
	while(left < right && nums[left] < value) left++;
	if(left == right){
		// cout<<"leave partion_with_value:"<< left<<' '<<right<<endl;
		// for(int i = p; i <= r; i++ ) cout<<nums[i]<<" ";
		// cout<<"----------"<<endl;
		return r;
	} 

	while(left < right){
		//cout<<left<<' '<<right<<endl;
		while(right >= left && nums[right] >= value){
			//记录value出现位置，勇于后面移动 
			if(nums[right] == value) {
				v_postion = right;
				//cout<<right<<" v_postion "<<v_postion<<endl;
			}
			right--;
		}
		// 如果value出现在left上会导致v_postion没有赋值，所以要到等于
		if(right >= left) {
			exchange(nums, right, left);
			left++;
		}
		while(right > left && nums[left] < value) left++;
	}

	exchange(nums, left, v_postion);
	
	// cout<<"leave partion_with_value:"<< left<<' '<<right<<endl;
	// for(int i = p; i <= r; i++ ) cout<<nums[i]<<" ";
	// cout<<"----------"<<endl;
	return left;
}

//插入排序，然后返回中值
int get_middle(vector<int> &nums, int p, int r){
	for(int i = p + 1; i <= r; i++){
		for(int j = p; j < i; j++){
			if(nums[j] > nums[i]){
				int t = nums[i];
				for(int k = i; k > j; k--) nums[k] = nums[k - 1];
				nums[j] = t;
			}
			//如果没有那就没必要插入
		}
	}
	
	// for(int i = p; i <= r; i++) cout<<nums[i]<<' ';
	// cout<<endl<<nums[(r - p)/2 + p]<<endl;
	return (r - p)/2 + p;
}


int select(vector<int> &nums, int p, int r, int k){
	// if(depth++ > 20) return 0;
	// cout<<"enter select" <<endl;
	// cout<<p<<' '<< r<<' '<<k<<"-- \n";

	// if(r>p){
		// for(int i = p; i <= r; i++ ) cout<<nums[i]<<" ";
		// cout<<endl; 
	// }
	
	if(p==r) return p;
	if(k < p || k > r) return 0;

	vector<int> middle_nums;
	int right;
	int mmid;

	for(int i = p; i <= r; i += 5){
		if(i + 5 >= nums.size()) right = nums.size() - 1;
		else right = i + 4;
		int pos = get_middle(nums, i, right);
		middle_nums.push_back(nums[pos]);
	}
	
	// if(middle_nums.size() > 0){
		// for_each(middle_nums.begin(), middle_nums.end(), [=](int n) -> void{cout<<n<<" ";});
		// cout<<endl;
	// }
	
	//递归获得中位数的中位数
	mmid = select(middle_nums, 0, middle_nums.size()-1, (middle_nums.size()-1)/2);

	// cout<<"mmid"<<mmid<<endl;
	int value = middle_nums[mmid];
	int q = partion_with_value(nums, p, r, value);
	
	// cout<<q<<endl;
	// for(int i = p; i <= r; i++ ) cout<<nums[i]<<" ";
	// cout<<endl;
	
	if(q == k) return q;
	
	if(q < k) return select(nums, q + 1, r, k);
	return select(nums, p, q - 1, k);
}

int main(){
	srand(time(0));
	int length = random(MAX_SIZE) + 10;
	vector<int> numbers(length);
	//vector<int> numbers = {3,8,13,8,6,3,7,11};
	for(int i = 0; i < length; i++){
		numbers[i] = random(length * 10);
		//numbers[i] = length - i; 
	}

	for(int i = 0; i < length; i++){
		cout<<numbers[i]<<' ';
	}
	cout<<endl;
	//注意这里length = 1 的时候会使得，除数为0，进而导致127错误
	int position = random(length-1);
	//int pos = random_select(numbers, 0, length-1, position);
	int pos = select(numbers, 0, length - 1, position);
	//int pos = get_middle(numbers, 0, length - 1);
	
	//cout<<"---"<<numbers[length/2]<<endl;
	//int pos = partion_with_value(numbers, 0, numbers.size() - 1, numbers[length/2]);
	//cout<<pos<<endl;
	cout<<"number["<<pos<<"]="<< numbers[pos]<<endl;
	for(int i = 0; i < length; i++){
		cout<<numbers[i]<<' ';
	}
	cout<<endl;
	
	//排序后的效果
	sort(numbers.begin(), numbers.end());
	for(int i = 0; i < length; i++){
		cout<<numbers[i]<<' ';
	}
	cout<<endl;
	cout<<"number["<<pos<<"]="<< numbers[pos]<<endl;
}
