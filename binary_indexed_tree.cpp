// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
//implemented using the above link...

class NumArray {
public:
    NumArray(vector<int> &nums) {
        this->nums = nums;
        psums.push_back(0);
        
        for(int i=0;i<nums.size();i++)
        {
            psums.push_back(0);
        }
        
        int i = 1;
        while(i<psums.size())
        {
            psums[i] = 0;
            for(int j = i+1-(i & (-i));j<=i;j++)
            {
                psums[i] += nums[j-1];
            }
            i++;
        }
    }

    void update(int i, int val) {
        int j = i+1;

        while(j<psums.size())
        {
            psums[j] += val - nums[i];
            j += (j & -j);
        }
        nums[i] = val;
    }

    int sumRange(int i, int j) {
        int sumj = 0, sumi = 0;
        int temp = j+1;
        
        while(temp > 0)
        {
            sumj += psums[temp];
            temp = temp - (temp & -temp);
        }
        
        temp = i;
        while(temp >0)
        {
            sumi += psums[temp];
            temp = temp-(temp & -temp);
        }
        
        return sumj - sumi;
    }
private:
    vector<int> psums;
    vector<int> nums;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);
